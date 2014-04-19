#ifndef APPLICATION_H
#define APPLICATION_H

#define FPS_MAX 60
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Evenement.hpp"
#include "Background.hpp"
#include "Bouton.hpp"
#include "MenuIndex.hpp"
#include "MenuSettings.hpp"
#include "MenuSettingsTouches.hpp"
#include "MenuSettingsAudio.hpp"
#include "Game.hpp"
#include "AudioConfiguration.hpp"

#define INDEX 0
#define GAME 1
#define SETTINGS 2
#define CLOSE 3
#define SETTINGSTOUCHES 4
#define SETTINGSAUDIO 5
#define SCORE 6


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

        Evenement _event;

        Background _background;

        char _state;

        ScreenElement * _screenElement[7];

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
