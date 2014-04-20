#ifndef AUDIOCONFIGURATION_H
#define AUDIOCONFIGURATION_H

#include "headers.hpp"
#include "fileManager.hpp"
#include "fn_random.hpp"

class AudioConfiguration
{
    public:
        AudioConfiguration();
        virtual ~AudioConfiguration();
        void loadFromFile(std::string file);
        void loadFromFolder(std::string folder);
        void addMusic(std::string file);
        void update();
        void setPlay(bool _state);
        bool getPlay();
        void setVolume(float volume);
        float getVolume();

    protected:
        void clearMusics();
        void changeMusic(int i);
    private:
        std::vector<sf::Music*> _musics;
        bool _play;
        float _volume;
        int musicPlayed;
};



#endif // AUDIOCONFIGURATION_H
