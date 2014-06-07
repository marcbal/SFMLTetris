#include "GameConfiguration.hpp"

const string GameConfiguration::_config_file("configuration/game.cfg");


GameConfiguration::GameConfiguration()
{
    changeAntialias = false;
    changeFPS = false;
    makeDir("configuration");
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
sf::Vector3f GameConfiguration::get3DInclinaison(){return _3DInclinaison;}
string GameConfiguration::getNickName(){return _nickname;}
bool GameConfiguration::getUseMouse(){return _useMouse;}
bool GameConfiguration::getOnlineScore(){return _onlineScore;}
unsigned int GameConfiguration::getFPS(){return _graphicsFPS;}
unsigned int GameConfiguration::getAntialiasing(){return _graphicsAntialiasing;}
unsigned int GameConfiguration::getBGParticules(){return _BGParticules;}
float GameConfiguration::getBGSpeed(){return _BGSpeed;}
float GameConfiguration::getBGPartSize(){return _BGPartSize;}

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
void GameConfiguration::set3DInclinaison(sf::Vector3f f){
    if (_3DInclinaison != f)
    {
        _3DInclinaison = f;
        saveConfigurationFile();
    }
}
void GameConfiguration::setNickName(string s){
    if (s == "") s == " ";
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
void GameConfiguration::setOnlineScore(bool b){
    if (_onlineScore != b)
    {
        _onlineScore = b;
        saveConfigurationFile();
    }
}

void GameConfiguration::setFPS(unsigned int i){
    if (_graphicsFPS != i)
    {
        changeFPS = true;
        _graphicsFPS = i;
        saveConfigurationFile();
    }
}

void GameConfiguration::setAntialiasing(unsigned int i){
    if (_graphicsAntialiasing != i)
    {
        changeAntialias = true;
        _graphicsAntialiasing = i;
        saveConfigurationFile();
    }
}

void GameConfiguration::setBGParticules(unsigned int i){
    if (_BGParticules != i)
    {
        _BGParticules = i;
        saveConfigurationFile();
    }
}

void GameConfiguration::setBGSpeed(float f){
    if (_BGSpeed != f)
    {
        _BGSpeed = f;
        saveConfigurationFile();
    }
}

void GameConfiguration::setBGPartSize(float f){
    if (_BGPartSize != f)
    {
        _BGPartSize = f;
        saveConfigurationFile();
    }
}







bool GameConfiguration::loadFromFile()
{
    ifstream saveFile(_config_file.c_str(), ios::in);

    bool ghost, explosion, mode3d, autorotation, inclinaison, nickname, mouse, online, fps, antialias, bgpart, bgspeed, bgpsize;
    ghost = explosion = mode3d = autorotation = inclinaison = nickname = mouse = online = fps = antialias = bgpart = bgspeed = bgpsize = false;

    if(!saveFile)
        return false;

    string line;
    vector<string> words;
    while(getline(saveFile, line)){
        words = explode(line,':');
        if(words.size()!=2){
            Console::out("Erreur de format dans le fichier \"" + _config_file + "\"");
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
        else if(words[0]=="publish_online"){
            _onlineScore=string_to_int(words[1]) != 0;
            online = true;
        }
        else if(words[0]=="graphics_antialiasing"){
            _graphicsAntialiasing=string_to_int(words[1]);
            antialias = true;
        }
        else if(words[0]=="graphics_FPS"){
            _graphicsFPS=string_to_int(words[1]);
            fps = true;
        }
        else if(words[0]=="BG_speed"){
            _BGSpeed=string_to_float(words[1]);
            bgspeed = true;
        }
        else if(words[0]=="BG_particules_size"){
            _BGPartSize=string_to_float(words[1]);
            bgpsize = true;
        }
        else if(words[0]=="BG_particules"){
            _BGParticules=string_to_int(words[1]);
            bgpart = true;
        }
        else if(words[0]=="3D_inclinaison"){
            vector<string> axes = explode(words[1], ';');
            if (axes.size() == 3)
            {
                _3DInclinaison.x=string_to_float(axes[0]);
                _3DInclinaison.y=string_to_float(axes[1]);
                _3DInclinaison.z=string_to_float(axes[2]);
                inclinaison = true;
            }
            else inclinaison = false;
        }
        else if(words[0]=="nickname"){
            _nickname=words[1];
            nickname = true;
        }
        else{
            Console::out("Erreur de format dans le fichier \"" + _config_file + "\"");
        }
    }



    saveFile.close();

    if(ghost&&explosion&&mode3d&&autorotation&&inclinaison&&nickname&&mouse&&fps&&antialias&&bgspeed&&bgpart&&bgpsize)
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
    saveFile << "publish_online:"<<_onlineScore<<endl;
    saveFile << "3D:"<<_3DMode<<endl;
    saveFile << "3D_autorotation:"<<_3DAutorotation<<endl;
    saveFile << "3D_inclinaison:"<<_3DInclinaison.x<<";"<<_3DInclinaison.y<<";"<<_3DInclinaison.z<<endl;
    saveFile << "nickname:"<<_nickname<<endl;
    saveFile << "graphics_antialiasing:"<<_graphicsAntialiasing<<endl;
    saveFile << "graphics_FPS:"<<_graphicsFPS<<endl;
    saveFile << "BG_speed:"<<_BGSpeed<<endl;
    saveFile << "BG_particules:"<<_BGParticules<<endl;
    saveFile << "BG_particules_size:"<<_BGPartSize<<endl;

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
    _onlineScore = true;
    _3DInclinaison = sf::Vector3f(0, 0, 0);
    _nickname = "Pseudo";
    _graphicsAntialiasing = 0;
    _graphicsFPS = FPS_MAX;
    _BGSpeed = 42;
    _BGParticules = 100;
    _BGPartSize = 10;
    Console::out(L"La configuration du jeu a été réinitialisée");
}






void GameConfiguration::applyGraphicsSettings(sf::RenderWindow & window, sf::Vector2i window_size)
{
    if (changeFPS)
    {
        window.setFramerateLimit(getFPS());
        changeFPS = false;
    }
    if (changeAntialias)
    {
        sf::ContextSettings s = window.getSettings();
        s.antialiasingLevel = _graphicsAntialiasing;
        window.create(sf::VideoMode(window_size.x, window_size.y), L"SFML Tetris", Style::Close | Style::Titlebar | Style::Resize, s);
        changeAntialias = false;
    }
}



