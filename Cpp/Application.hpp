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
#include "Game.hpp"
#include "AudioConfiguration.hpp"
#include "Scores.hpp"

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
