#include "AudioConfiguration.hpp"

using namespace std;
using namespace sf;

AudioConfiguration::AudioConfiguration():
    _spectrum(1, vector<float>(512, 0.f))
{
    makeDir("configuration");
    musicPlayed=-1;
    if(!loadConfigFromFile("configuration/audio.cfg")){
        initDefault();
    }
    int conf_music_played = musicPlayed; // musicPlayed est réinitialisé dans loadFromFolder()
    loadFromFolder(_folder.c_str());

    musicPlayed = conf_music_played;

    if(_musics.size()==0 || musicPlayed >= (int)_musics.size() || musicPlayed < 0)
    {
        musicPlayed = -1;
        saveConfigurationFile();
    }
    else if (_play && musicPlayed>=0 && musicPlayed < (int)_musics.size())
    {
        _buff_actual_music.loadFromFile(_folder+musicNames[musicPlayed]);
        _musics[musicPlayed]->play();
    }
    _level = 1.f;
}

AudioConfiguration::~AudioConfiguration()
{
    clearMusics();
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

float AudioConfiguration::getAudioLevel()
{
    return _level;
}


float AudioConfiguration::_pGetAudioLevel()
{
    if (!_play || _buff_actual_music.getSampleCount() == 0 || _musics.size() == 0 || musicPlayed < 0 || musicPlayed >= (int)_musics.size())
        return 1.f;

    sf::Time timeOffset = _musics[musicPlayed]->getPlayingOffset();
    unsigned int sampleRate = _musics[musicPlayed]->getSampleRate();
    unsigned int channelCount = _musics[musicPlayed]->getChannelCount();
    if (sampleRate != _buff_actual_music.getSampleRate()
        || channelCount != _buff_actual_music.getChannelCount())
        return 1.f;

    unsigned int samplePosition = sampleRate * channelCount * timeOffset.asSeconds();

    uint32_t value = 0;
    uint32_t value2 = 0;
    for (unsigned int i = samplePosition; i<samplePosition+2000 && i<_buff_actual_music.getSampleCount(); i++)
    {
        value += abs(_buff_actual_music.getSamples()[i]);
        if (abs(_buff_actual_music.getSamples()[i]) > value2)
            value2 = abs(_buff_actual_music.getSamples()[i]);
    }
    float fval = (value / 2000.f) / 16384.f;
    if (fval > 1)
        fval = 1.f;

    return sqrt(fval);
}

vector<vector<float> > AudioConfiguration::getAudioSpectrum()
{
    return _spectrum;
}


void AudioConfiguration::_pGetAudioSpectrum()
{
    if (!_play || _buff_actual_music.getSampleCount() == 0 || _musics.size() == 0 || musicPlayed < 0 || musicPlayed >= (int)_musics.size())
    {
        _spectrum = vector<vector<float> >(1, vector<float>(512, 0.f));
        return;
    }

    sf::Time timeOffset = _musics[musicPlayed]->getPlayingOffset();
    unsigned int sampleRate = _musics[musicPlayed]->getSampleRate();
    unsigned int channelCount = _musics[musicPlayed]->getChannelCount();
    if (sampleRate != _buff_actual_music.getSampleRate()
        || channelCount != _buff_actual_music.getChannelCount())
    {
        _spectrum =  vector<vector<float> >(1, vector<float>(512, 0.f));
        return;
    }

    unsigned int samplePosition = sampleRate * channelCount * timeOffset.asSeconds();

    int log2n = 12;
    unsigned int nbAnalysedSamplePerChannel = pow(2, log2n);
    int max_val_int16 = pow(2, 14);
    if (channelCount != _spectrum.size())
    {
        _spectrum.clear();
        _spectrum = vector<vector<float> >(channelCount, vector<float>(512, 0.f));
    }
    complex<double> * a = new complex<double>[nbAnalysedSamplePerChannel];
    complex<double> * b = new complex<double>[nbAnalysedSamplePerChannel];
    for (unsigned int c=0; c<channelCount; c++)
    {

        unsigned int j = samplePosition + c;
        for (unsigned int i = 0; i<nbAnalysedSamplePerChannel && j<_buff_actual_music.getSampleCount(); i++)
        {
            a[i].imag(0);
            a[i].real((double)_buff_actual_music.getSamples()[j]/max_val_int16);
            j+=channelCount;
        }
        fft(a, b, log2n);
        for (unsigned int i=0; i<_spectrum[c].size(); i++)
        {
            _spectrum[c][i] += /* 10*log10 */sqrt((b[i].real()*b[i].real()+b[i].imag()*b[i].imag()))/(nbAnalysedSamplePerChannel/4);
            _spectrum[c][i] /= 2.f;
        }


    }

    delete[] a;
    delete[] b;

}





void AudioConfiguration::clearMusics(){
    int nbMusics = _musics.size();
    for(int i=0;i<nbMusics;++i)
    {
        _musics[i]->stop();
        delete _musics[i];
    }
    _musics.clear();
    musicPlayed = -1;
}
void AudioConfiguration::changeMusic(int i){
    if(musicPlayed == i || i >= (int)_musics.size() || i < 0)
        return;
    if (musicPlayed >= 0 && musicPlayed < (int)_musics.size())
        _musics[musicPlayed]->stop();
    musicPlayed = i;
    _buff_actual_music.loadFromFile(_folder+musicNames[musicPlayed]);
    if (_play)
        _musics[musicPlayed]->play();
}

void AudioConfiguration::update(){
    if(musicPlayed>-1 && musicPlayed < (int)_musics.size())
    {
        if(_musics[musicPlayed]->getStatus() != sf::Music::Status::Playing && _play){
            _musics[musicPlayed]->play();
        }
        else if(!_play)
            _musics[musicPlayed]->stop();
    }
    _level = _pGetAudioLevel();
    _pGetAudioSpectrum();
}


void AudioConfiguration::setPlay(bool _state){
    if (_play != _state)
    {
        _play = _state;
        saveConfigurationFile();
    }
}
bool AudioConfiguration::getPlay(){
    return _play;
}
void AudioConfiguration::setVolume(float volume){
    _volume = volume;
    for(unsigned int i=0;i<_musics.size();++i)
        _musics[i]->setVolume(_volume);

    saveConfigurationFile();
}
float AudioConfiguration::getVolume(){
    return _volume;
}


