#ifndef APPLICATION_H
#define APPLICATION_H


#include "headers.hpp"

#include "Game.hpp"

using namespace std;
using namespace sf;

class Application
{
    private:
        sf::Vector2i _window_size;
        sf::RenderWindow _window;
        sf::ContextSettings _window_setting;

        sf::Clock _app_clock;
        sf::Clock clock;

        Game _game;

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
