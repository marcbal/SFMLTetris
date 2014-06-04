#include "AudioConfiguration.hpp"

using namespace std;
using namespace sf;

AudioConfiguration::AudioConfiguration()
{
    makeDir("configuration");
    if(!loadFromFile("configuration/audio.cfg")){
        initDefault();
    }



    loadFromFolder(_folder.c_str());


    if(_musics.size()>0)
        musicPlayed = 0;
    else
        musicPlayed = -1;

}

AudioConfiguration::~AudioConfiguration()
{
    //dtor
}

void AudioConfiguration::initDefault(){
    _play = false;
    _folder="res/music/";
    _volume=100;
    Console::out(L"La configuration audio a été réinitialisée");
}

void AudioConfiguration::addMusic(string file){
    _musics.push_back(new Music());
    if(!_musics[_musics.size()-1]->openFromFile(file.c_str()))
        _musics.pop_back();
    else{
        _musics[_musics.size()-1]->setLoop(false);
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

     saveFile.close();

     return true;
}

bool AudioConfiguration::loadFromFile(string file){

        ifstream saveFile(file.c_str(), ios::in);

        bool folder,play,volume;
        folder = play = volume = false;

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
            else if(words[0] == "volume"){
                _volume = string_to_float(words[1]);
                volume = true;
            }
            else{
                Console::out("Erreur de format dans le fichier \"" + file + "\"");
            }
        }



        saveFile.close();

        if(volume&&play&&folder)
        return true;

        return false;
}

void AudioConfiguration::loadFromFolder(string folder){
    clearMusics();
    vector<string> files = listOfFiles(folder);
    int nbFiles = files.size();

    for(int i=0;i<nbFiles;++i){
            if(regex_match(files[i],regex("(.*).ogg"))){
                addMusic(folder+files[i]);
            }
    }

}



void AudioConfiguration::clearMusics(){
    int nbMusics = _musics.size();
    for(int i=0;i<nbMusics;++i)
        delete _musics[i];
    _musics.clear();
}
void AudioConfiguration::changeMusic(int i){
    if(musicPlayed==i)
        return;

    if(musicPlayed>-1)
        _musics[musicPlayed]->stop();
    musicPlayed = i;
    _musics[musicPlayed]->play();
}

void AudioConfiguration::update(){
    if(musicPlayed>-1)
    {
        if(_musics[musicPlayed]->getStatus() != sf::Music::Status::Playing && _play){
            changeMusic(rand_without(0,_musics.size()-1,musicPlayed));
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
    int nbMusics = _musics.size();
    for(int i=0;i<nbMusics;++i)
        _musics[i]->setVolume(_volume);

    saveConfigurationFile();
}
float AudioConfiguration::getVolume(){
    return _volume;
}


