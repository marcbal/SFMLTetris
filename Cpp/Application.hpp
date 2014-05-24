#ifndef APPLICATION_H
#define APPLICATION_H


#include "headers.hpp"

#include "Evenement.hpp"
#include "Background.hpp"
#include "Bouton.hpp"
#include "MenuIndex.hpp"
#include "MenuSettings.hpp"
#include "MenuSettingsTouches.hpp"
#include "MenuSettingsAudio.hpp"
#include "MenuSettingsGraphic.hpp"
#include "Game.hpp"
#include "AudioConfiguration.hpp"
#include "Scores.hpp"
#include "ScreenScore.hpp"
#include "OpenGL_Manager.hpp"

using namespace std;
using namespace sf;

class Application
{
    private:
        sf::Vector2i _window_size;
        AudioConfiguration _audio;
        sf::RenderWindow _window;
        sf::ContextSettings _window_setting;

        sf::Clock _app_clock;
        sf::Clock clock;

        Evenement _event;

        Background _background;

        OpenGL_Manager _oGL;

        char _state;

        ScreenElement * _screenElement[8];

        GameConfiguration _gameconfig;

        Scores _scores;

    public:
        Application();
        virtual ~Application();
        void run();


    protected:

        void processEvents();
        void update();
        void render();

};




#endif // APPLICATION_H
