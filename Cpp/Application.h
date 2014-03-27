#ifndef APPLICATION_H
#define APPLICATION_H

#define FPS_MAX 120

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Evenement.hpp"

using namespace std;
using namespace sf;

class Application
{
    private:
        int _window_width;
        int _window_height;

        sf::RenderWindow _window;
        sf::ContextSettings _window_setting;

        sf::Clock _app_clock;

        Evenement _event;





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
