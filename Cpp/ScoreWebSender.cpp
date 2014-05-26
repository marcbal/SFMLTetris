#include "ScoreWebSender.hpp"

ScoreWebSender::ScoreWebSender() : gameDatas() { }

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
    cout << "Envoi du record de " << rL.points << " points au serveur de score" << endl;
    sf::Thread * th = new sf::Thread(&webSendData, g);
    th->launch();

    clearData();
}





void ScoreWebSender::clearData()
{
    gameDatas.clear();
}






void webSendData(string& data)
{

    sf::Http http(SERVER_ADDR, SERVER_PORT);

    sf::Http::Request req(SERVER_QUERRY, sf::Http::Request::Method::Post);
    string key = to_string(rand_int(100000, 999999));

    key = base64_encode((unsigned char*)key.c_str(), key.size(), true);
    req.setBody("data="+base64_encode((unsigned char*)data.c_str(), data.size(), true)+"&key="+key);

    sf::Http::Response rep = http.sendRequest(req, sf::Time::Zero);
   vector<string> repData = explode(rep.getBody(), ':');

   if (rep.getStatus() == 200 && repData.size() == 2 && repData[0] == "ok")
        if (repData[1] == key)
            cout << "Le score a ete publie avec succes" << endl;
        else if(rep.getStatus() == 1001)
           cout << "Connexion impossible : score non envoye !" << endl;
        else
            cout << "Score non valide ou envoi impossible : Code HTTP " << rep.getStatus() << endl << rep.getBody() << endl;

}



