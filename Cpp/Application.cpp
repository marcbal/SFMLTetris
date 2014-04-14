#include "Application.hpp"

#include <iostream>

using namespace std;
using namespace sf;

Application::Application() :
    _window_size(WINDOW_WIDTH, WINDOW_HEIGHT),
    _window(),
    _background(_window_size, 200),
    _state(INDEX) // correspond à l'état d'affichage (ici, le menu au lancement du programme)
{
    _screenElement[INDEX]= new MenuIndex(&_window_size,&_state);
    _screenElement[GAME]= new Game(&_window_size,&_state);
    _screenElement[SCORE]= new MenuIndex(&_window_size,&_state);
    _screenElement[SETTINGS]= new MenuSettings(&_window_size,&_state);
    _screenElement[SETTINGSTOUCHES]= new MenuSettingsTouches(&_window_size,&_state);
	_window.setFramerateLimit(FPS_MAX);
	_window.setKeyRepeatEnabled(false);
    _window_setting.antialiasingLevel = 4;
    _window.create(VideoMode(_window_size.x, _window_size.y), L"SFMLTetris", Style::Close | Style::Titlebar, _window_setting);
}

Application::~Application(){}

















void Application::run()
{
	while (_window.isOpen())
	{
		processEvents();
        if(_state == CLOSE) return;
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

                if(_state == CLOSE){
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
