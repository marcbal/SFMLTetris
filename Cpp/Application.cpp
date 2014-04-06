#include "Application.hpp"
#include "MenuSettings.hpp"
#include <iostream>

using namespace std;
using namespace sf;

Application::Application() :
    _window_width(WINDOW_WIDTH),
    _window_height(WINDOW_HEIGHT),
    _window(),
    _background(sf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT), 200),
    _state(Index) // correspond à l'état d'affichage (ici, le menu au lancement du programme)
{
    _screenElement[Index]= new MenuIndex(sf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT),&_state);
    _screenElement[Game]= new MenuIndex(sf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT),&_state);
    _screenElement[Settings]= new MenuSettings(sf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT),&_state);
    _screenElement[Rules]= new MenuIndex(sf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT),&_state);
	_window.setFramerateLimit(FPS_MAX);
    _window_setting.antialiasingLevel = 4;
    _window.create(VideoMode(_window_width, _window_height), L"SFMLTetris", Style::Default, _window_setting);
}

Application::~Application(){}

















void Application::run()
{
	while (_window.isOpen())
	{
		processEvents();
        if(_state == Close) return;
		update();
		render();

	}
}













void Application::processEvents()
{
    Event event;
	while (_window.pollEvent(event))
	{

		switch(event.type)
		{
            case Event::Closed:

                _window.close();

            break;
            default:
                _screenElement[(int)_state]->onEvent(event);

                if(_state == Close){
                    _window.close();
                    return;
                }
            break;
		} //SWITCH
	}
}












void Application::update()
{

    _background.update();
    _screenElement[(int)_state]->update();
}












void Application::render()
{
	_window.clear();
	_window.draw(_background);
    _window.draw(*_screenElement[(int)_state]);
	_window.display();
}
