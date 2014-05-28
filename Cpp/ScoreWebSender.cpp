#include "ScoreWebSender.hpp"

ScoreWebSender::ScoreWebSender() : gameDatas() {
    initSavedDataUpload();
}

ScoreWebSender::~ScoreWebSender(){ }



void ScoreWebSender::addDataInfoNextPiece(int score,        // nouveau score obtenu
                                  int scoreDiff,            // différence avec l'ancien score
                                  int nbTetromino,          // nombre de tetromino posé
                                  sf::Time time,            // horloge actuelle
                                  int delLines,             // nombre de lignes détruites depuis le début
                                  int newDelLines,          // nombre de ligne détruite à ce moment
                                  int nbManualDown,         // compteur d'accélération de descente
                                  Tetromino tetrominoPlace)
{
    ScoreWebSenderDataSample line;
    line.score = score;
    line.scoreDiff = scoreDiff;
    line.nbTetromino = nbTetromino;
    line.timeMilliseconds = (int) (time.asSeconds()*1000);
    line.nbDelLines = delLines;
    line.nbDelLinesDiff = newDelLines;
    line.nbManualDown = nbManualDown;

    line.tetrominoTypeAndOrientation =
                ((byte) tetrominoPlace.getTypePiece() << 4) |
                ((byte) tetrominoPlace.getOrientation() & 0x0F);
    line.tetrominoPositionX = tetrominoPlace.getPosition().x;
    line.tetrominoPositionY = tetrominoPlace.getPosition().y;


    gameDatas.push_back(line);
}


void ScoreWebSender::addDataToFinishGame(RecordLine rL)
{
    if (rL.points == 0)
    {
        clearData();
        return;
    }

    ostringstream oss;
    // << taille des données initiales : 1 octet
    oss << (unsigned char) sizeof(RecordLine);

    // << données initiales : x octets


    rL.lines_u = convert_endianness(rL.lines_u, BINARY_NETWORK_BIG_ENDIAN);
    rL.points_u = convert_endianness(rL.points_u, BINARY_NETWORK_BIG_ENDIAN);
    rL.tetrominos_u = convert_endianness(rL.tetrominos_u, BINARY_NETWORK_BIG_ENDIAN);
    rL.time_u = convert_endianness(rL.time_u, BINARY_NETWORK_BIG_ENDIAN);

    for (size_t i=0; i<sizeof(RecordLine); i++)
        oss << (char) rL.b[i];

    // << nombre de ligne de données du déroulement de jeu
    // << taille d'une ligne de donnée
    _4bytes gameDataSize;
    gameDataSize.i = gameDatas.size();
    gameDataSize = convert_endianness(gameDataSize , BINARY_NETWORK_BIG_ENDIAN);
    oss << gameDataSize.b[0] << gameDataSize.b[1] <<
        gameDataSize.b[2] << gameDataSize.b[3] <<
        (char) sizeof(ScoreWebSenderDataSample);

    for (size_t i=0; i<gameDatas.size(); i++)
    {
        ScoreWebSenderDataSample dL = gameDatas[i];
        dL.u.nbDelLines = convert_endianness(dL.u.nbDelLines, BINARY_NETWORK_BIG_ENDIAN);
        dL.u.nbDelLinesDiff = convert_endianness(dL.u.nbDelLinesDiff, BINARY_NETWORK_BIG_ENDIAN);
        dL.u.nbManualDown = convert_endianness(dL.u.nbManualDown, BINARY_NETWORK_BIG_ENDIAN);
        dL.u.nbTetromino = convert_endianness(dL.u.nbTetromino, BINARY_NETWORK_BIG_ENDIAN);
        dL.u.score = convert_endianness(dL.u.score, BINARY_NETWORK_BIG_ENDIAN);
        dL.u.scoreDiff = convert_endianness(dL.u.scoreDiff, BINARY_NETWORK_BIG_ENDIAN);
        dL.u.timeMilliseconds = convert_endianness(dL.u.timeMilliseconds, BINARY_NETWORK_BIG_ENDIAN);



        for (size_t j=0; j<sizeof(ScoreWebSenderDataSample); j++)
            oss << (char) dL.b[j];

    }


    string g = oss.str();
    rL.points_u = convert_endianness(rL.points_u, BINARY_NETWORK_BIG_ENDIAN);
    cout << "Envoi du record de " << rL.points << " points au serveur de score ..." << endl;
    sf::Thread * th = new sf::Thread(&webSendNewData, g);
    ScoreWebSender::_uploadThreads.push_back(th);
    ScoreWebSender::_uploadData.push_back("");
    th->launch();

    clearData();
}





void ScoreWebSender::clearData()
{
    gameDatas.clear();
}




void webSendOldData(string& data)
{
    webSendData(data, true);
}
void webSendNewData(string& data)
{
    webSendData(data, false);
}

void webSendData(string& data, bool alreadyPostData)
{
    int upload_id = ScoreWebSender::_uploadThreadsNumberActiv;
    ScoreWebSender::_uploadThreadsNumberActiv++;
    srand(time(NULL));
    string key;
    if (alreadyPostData)
        key = explode(data, '&')[1].substr(4);
    else
    {
        key = to_string(rand_int(10000000, 99999999));
        key = base64_encode((unsigned char*)key.c_str(), key.size(), true);
    }
    sf::Http::Request req(SERVER_QUERRY, sf::Http::Request::Method::Post);
    string body = (alreadyPostData) ?
                    data :
                    "data="+base64_encode((unsigned char*)data.c_str(), data.size(), true)+"&key="+key;
    req.setBody(body);
    ScoreWebSender::_uploadData[upload_id] = body;

    bool send_ok = false;
    do
    {
        sf::Http http(SERVER_ADDR, SERVER_PORT);

        sf::Http::Response rep = http.sendRequest(req, sf::Time::Zero);
        vector<string> repData = explode(rep.getBody(), ':');

        if (rep.getStatus() == 200 && repData.size() == 2 && repData[0] == "ok" && repData[1] == key)
        {
            cout << upload_id << " : Le score a ete publie avec succes" << endl;
            send_ok = true;
        }
        else if(rep.getStatus() == 1000)
            cout << upload_id << " : Reponse du serveur invalide : score potentiellement non envoye !" << endl;
        else if(rep.getStatus() == 1001)
            cout << upload_id << " : Connexion impossible : score non envoye !" << endl;
        else
        {
            cout << upload_id << " : Score non valide ou envoi impossible : Code HTTP " << rep.getStatus() << endl
                << rep.getBody() << endl
                << key << endl;
            send_ok = (rep.getStatus() == 200);
        }

        if (!send_ok) sf::sleep(sf::seconds(10.f));
    } while (!send_ok);
    ScoreWebSender::_uploadData[upload_id] = "";


    ScoreWebSender::_uploadThreadsNumberActiv--;
}




vector<sf::Thread*> ScoreWebSender::_uploadThreads = vector<sf::Thread*>();
vector<string> ScoreWebSender::_uploadData = vector<string>();

int ScoreWebSender::_uploadThreadsNumberActiv = 0;



void ScoreWebSender::saveFailedUpload()
{
    if (_uploadThreadsNumberActiv == 0)
        return;
    cout << "Sauvegarde des uploads non effectues (" <<
        _uploadThreadsNumberActiv << " restants) ..." << endl;
    for (unsigned int i=0; i<_uploadThreads.size(); i++)
    {
        _uploadThreads[i]->terminate();
    }

    ofstream file("save/upload.bin", ios::out | ios::trunc);

    if (!file.is_open())
    {
        cout << "Sauvegarde impossible" << endl;
        return;
    }

    for (unsigned int i=0; i<_uploadData.size(); i++)
    {
        if (_uploadData[i] == "")
            continue;

        file << _uploadData[i] << "\n";
        _uploadData[i] = "";
    }

    file.close();

}





void ScoreWebSender::initSavedDataUpload()
{
    ifstream file("save/upload.bin", ios::in);

    if(!file.is_open())
        return;
    string line;
    while(getline(file, line))
    {
        if (line == "")
            continue;
        vector<string> data = explode(line, '&');
        if (data.size() != 2)
            continue;

        sf::Thread * th = new sf::Thread(&webSendOldData, line);
        ScoreWebSender::_uploadThreads.push_back(th);
        ScoreWebSender::_uploadData.push_back("");
        th->launch();

    }
    file.close();

    // effacement du fichier
    ofstream fileerase("save/upload.bin", ios::out | ios::trunc);
    fileerase.close();

}



