#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Application
{
    private:
        int _window_width;
        int _window_height;

        sf::RenderWindow _window;
        sf::ContextSettings _window_setting;


        float frame_per_sec; // frame par seconde, relevé en temps réel
        float frame_time;   // durée d'une frame en seconde (calculé dans le constructeur comme étant l'inverse des FPS)
        static const int frame_per_sec_max = 120;  // frame par seconde max pour éviter de faire 100 % de processeur constament


        sf::Clock _app_clock;





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
