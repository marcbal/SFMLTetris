#include "AudioConfiguration.hpp"

using namespace std;
using namespace sf;

AudioConfiguration::AudioConfiguration()
{
    _play = false;

    loadFromFolder("res/music/");
    if(_musics.size()>0)
        musicPlayed = 0;
    else
        musicPlayed = -1;

}

AudioConfiguration::~AudioConfiguration()
{
    //dtor
}

void AudioConfiguration::addMusic(string file){
    _musics.push_back(new Music());
    if(!_musics[_musics.size()-1]->openFromFile(file.c_str()))
        _musics.pop_back();
    else
        _musics[_musics.size()-1]->setLoop(false);



}

void AudioConfiguration::loadFromFile(string file){
    clearMusics();
    addMusic(file);
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
}
bool AudioConfiguration::getPlay(){
    return _play;
}
void AudioConfiguration::setVolume(float volume){
    _volume = volume;
    int nbMusics = _musics.size();
    for(int i=0;i<nbMusics;++i)
        _musics[i]->setVolume(_volume);
}
float AudioConfiguration::getVolume(){
    return _volume;
}


