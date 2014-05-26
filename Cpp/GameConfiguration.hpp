#ifndef GAMECONFIGURATION_H
#define GAMECONFIGURATION_H

#include "headers.hpp"
#include "fn_string.hpp"

using namespace std;
using namespace sf;

class GameConfiguration
{
    public:
        GameConfiguration();
        virtual ~GameConfiguration();

        bool getDrawExplosions();
        void setDrawExplosions(bool b);
        bool getDrawGhost();
        void setDrawGhost(bool b);
        bool get3DMode();
        void set3DMode(bool b);
        bool get3DAutorotation();
        void set3DAutorotation(bool b);
        float get3DInclinaison();
        void set3DInclinaison(float b);
        string getNickName();
        void setNickName(string s);
        bool getUseMouse();
        void setUseMouse(bool b);
        bool getOnlineScore();
        void setOnlineScore(bool b);





    protected:
        bool loadFromFile();
        bool saveConfigurationFile();
        void initDefault();
    private:
        bool _drawGhost;
        bool _drawExplosions;
        bool _3DMode;
        bool _3DAutorotation;
        bool _useMouse;
        bool _onlineScore;
        float _3DInclinaison;
        string _nickname;


        static const string _config_file;
};

#endif // GAMECONFIGURATION_H