#include "AudioConfiguration.hpp"

using namespace std;
using namespace sf;

AudioConfiguration::AudioConfiguration()
{
    makeDir("configuration");
    musicPlayed=-1;
    if(!loadConfigFromFile("configuration/audio.cfg")){
        initDefault();
    }
    int conf_music_played = musicPlayed; // musicPlayed est réinitialisé dans loadFromFolder()
    loadFromFolder(_folder.c_str());

    musicPlayed = conf_music_played;

    if(_musics.size()==0 || musicPlayed >= _musics.size() || musicPlayed < 0)
    {
        musicPlayed = -1;
        saveConfigurationFile();
    }
    else
    {
        _musics[musicPlayed]->play();
    }

}

AudioConfiguration::~AudioConfiguration()
{
    //dtor
}

void AudioConfiguration::initDefault(){
    _play = false;
    _folder="res/music/";
    musicPlayed=-1;
    _volume=100;
    Console::out(L"La configuration audio a été réinitialisée");
}




vector<string> AudioConfiguration::getMusicList()
{
    return musicNames;
}
int AudioConfiguration::getMusicPlayingId()
{
    return musicPlayed;
}




void AudioConfiguration::addMusic(string file){
    _musics.push_back(new Music());
    vector<string> fileE = explode(file, '/');
    musicNames.push_back(fileE[fileE.size()-1]);
    if(!_musics[_musics.size()-1]->openFromFile(file.c_str()))
    {
        _musics.pop_back();
        musicNames.pop_back();
    }
    else{
        _musics[_musics.size()-1]->setLoop(true);
        _musics[_musics.size()-1]->setVolume(_volume);
    }



}

bool AudioConfiguration::saveConfigurationFile(){
     ofstream saveFile("configuration/audio.cfg", ios::out | ios::trunc);
     if(!saveFile)
        return false;

     saveFile << "music_search_path:"<<_folder<<endl;
     saveFile << "play_music:"<<_play<<endl;
     saveFile << "volume:"<<_volume<<endl;
     saveFile << "music_playing_id:"<<musicPlayed<<endl;

     saveFile.close();

     return true;
}

bool AudioConfiguration::loadConfigFromFile(string file){

        ifstream saveFile(file.c_str(), ios::in);

        bool folder,play,volume, musicid;
        folder = play = volume = musicid = false;

        if(!saveFile)
            return false;

        string line;
        vector<string> words;
        while(getline(saveFile, line)){
            words = explode(line,':');
            if(words.size()!=2){
                Console::out("Erreur de format dans le fichier \"" + file + "\"");
                continue;
            }
            if(words[0]=="music_search_path"){
                _folder=words[1];
                folder = true;
            }
            else if (words[0] == "play_music"){
                _play=string_to_int(words[1])!=0;
                play = true;
            }
            else if (words[0] == "music_playing_id"){
                musicPlayed=string_to_int(words[1]);
                musicid = true;
            }
            else if(words[0] == "volume"){
                _volume = string_to_float(words[1]);
                volume = true;
            }
            else{
                Console::out("Erreur de format dans le fichier \"" + file + "\"");
            }
        }



        saveFile.close();

        if(volume&&play&&folder&&musicid)
            return true;

        return false;
}

void AudioConfiguration::loadFromFolder(string folder){
    clearMusics();
    vector<string> files = listOfFiles(folder);
    int nbFiles = files.size();

    for(int i=0;i<nbFiles;++i){
            if(regex_match(files[i],regex("(.*).(ogg|wav|wave|flac|aiff|au)"))){
                addMusic(folder+files[i]);
            }
    }

}



void AudioConfiguration::clearMusics(){
    int nbMusics = _musics.size();
    for(int i=0;i<nbMusics;++i)
        delete _musics[i];
    _musics.clear();
    musicPlayed = -1;
}
void AudioConfiguration::changeMusic(int i){
    if(musicPlayed == i || i >= _musics.size() || i < 0)
        return;
    if (musicPlayed >= 0 && musicPlayed < _musics.size())
        _musics[musicPlayed]->stop();
    musicPlayed = i;
    _musics[musicPlayed]->play();
}

void AudioConfiguration::update(){
    if(musicPlayed>-1 && musicPlayed < _musics.size())
    {
        if(_musics[musicPlayed]->getStatus() != sf::Music::Status::Playing && _play){
            _musics[musicPlayed]->play();
        }
        else if(!_play)
            _musics[musicPlayed]->stop();
    }
}


void AudioConfiguration::setPlay(bool _state){
     _play = _state;
     saveConfigurationFile();
}
bool AudioConfiguration::getPlay(){
    return _play;
}
void AudioConfiguration::setVolume(float volume){
    _volume = volume;
    for(int i=0;i<_musics.size();++i)
        _musics[i]->setVolume(_volume);

    saveConfigurationFile();
}
float AudioConfiguration::getVolume(){
    return _volume;
}


