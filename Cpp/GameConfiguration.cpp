#include "GameConfiguration.hpp"

const string GameConfiguration::_config_file("configuration/game.cfg");


GameConfiguration::GameConfiguration()
{
    if (!loadFromFile())
        initDefault();


    saveConfigurationFile();
}

GameConfiguration::~GameConfiguration()
{
    //dtor
}

// getters / setters
bool GameConfiguration::getDrawExplosions(){return _drawExplosions;}
bool GameConfiguration::getDrawGhost(){return _drawGhost;}
bool GameConfiguration::get3DMode(){return _3DMode;}
bool GameConfiguration::get3DAutorotation(){return _3DAutorotation;}
float GameConfiguration::get3DInclinaison(){return _3DInclinaison;}
string GameConfiguration::getNickName(){return _nickname;}
bool GameConfiguration::getUseMouse(){return _useMouse;}

void GameConfiguration::setDrawExplosions(bool b){
    if (_drawExplosions != b)
    {
        _drawExplosions = b;
        saveConfigurationFile();
    }
}
void GameConfiguration::setDrawGhost(bool b){
    if (_drawGhost != b)
    {
        _drawGhost = b;
        saveConfigurationFile();
    }
}
void GameConfiguration::set3DMode(bool b){
    if (_3DMode != b)
    {
        _3DMode = b;
        saveConfigurationFile();
    }
}
void GameConfiguration::set3DAutorotation(bool b){
    if (_3DAutorotation != b)
    {
        _3DAutorotation = b;
        saveConfigurationFile();
    }
}
void GameConfiguration::set3DInclinaison(float f){
    if (_3DInclinaison != f)
    {
        _3DInclinaison = f;
        saveConfigurationFile();
    }
}
void GameConfiguration::setNickName(string s){
    if (_nickname != s)
    {
        _nickname = s;
        saveConfigurationFile();
    }
}
void GameConfiguration::setUseMouse(bool b){
    if (_useMouse != b)
    {
        _useMouse = b;
        saveConfigurationFile();
    }
}







bool GameConfiguration::loadFromFile()
{
    ifstream saveFile(_config_file.c_str(), ios::in);

    bool ghost, explosion, mode3d, autorotation, inclinaison, nickname, mouse;
    ghost = explosion = mode3d = autorotation = inclinaison = nickname = mouse = false;

    if(!saveFile)
        return false;

    string line;
    vector<string> words;
    while(getline(saveFile, line)){
        words = explode(line,':');
        if(words.size()!=2){
            cout << "Erreur de format de la ligne : " << line << " dans le fichier " << _config_file << endl;
            continue;
        }


        /*if(words[0]=="music_search_path"){
            _folder=words[1];
            folder = true;
        }*/
        if(words[0]=="ghost"){
            _drawGhost=string_to_int(words[1]) != 0;
            ghost = true;
        }
        else if(words[0]=="explosion"){
            _drawExplosions=string_to_int(words[1]) != 0;
            explosion = true;
        }
        else if(words[0]=="use_mouse"){
            _useMouse=string_to_int(words[1]) != 0;
            mouse = true;
        }
        else if(words[0]=="3D"){
            _3DMode=string_to_int(words[1]) != 0;
            mode3d = true;
        }
        else if(words[0]=="3D_autorotation"){
            _3DAutorotation=string_to_int(words[1]) != 0;
            autorotation = true;
        }
        else if(words[0]=="3D_inclinaison"){
            _3DInclinaison=string_to_float(words[1]);
            inclinaison = true;
        }
        else if(words[0]=="nickname"){
            _nickname=words[1];
            nickname = true;
        }
        else{
            cout << "Erreur de format de la ligne : " << line << " dans le fichier " << _config_file << endl;
        }
    }



    saveFile.close();

    if(ghost&&explosion&&mode3d&&autorotation&&inclinaison&&nickname&&mouse)
    return true;

    return false;
}
bool GameConfiguration::saveConfigurationFile()
{
    ofstream saveFile(_config_file.c_str(), ios::out | ios::trunc);
    if(!saveFile)
        return false;

    saveFile << "ghost:"<<_drawGhost<<endl;
    saveFile << "explosion:"<<_drawExplosions<<endl;
    saveFile << "use_mouse:"<<_useMouse<<endl;
    saveFile << "3D:"<<_3DMode<<endl;
    saveFile << "3D_autorotation:"<<_3DAutorotation<<endl;
    saveFile << "3D_inclinaison:"<<_3DInclinaison<<endl;
    saveFile << "nickname:"<<_nickname<<endl;

    saveFile.close();

    return true;
}
void GameConfiguration::initDefault()
{
    _drawGhost = true;
    _drawExplosions = true;
    _3DMode = false;
    _3DAutorotation = false;
    _useMouse = false;
    _3DInclinaison = 20.f;
    _nickname = "?";
}




