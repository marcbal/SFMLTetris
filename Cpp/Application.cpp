#include "Application.h"
#include "fn_time.h"
#include <iostream>

Application::Application() :
    _window_width(1280),
    _window_height(720),
    _window()
{
	_window.setFramerateLimit(FPS_MAX);
    _window_setting.antialiasingLevel = 8;
    _window.create(VideoMode(_window_width, _window_height), L"SFMLTetris", Style::Default, _window_setting);
}

Application::~Application(){}





void Application::run()
{
	while (_window.isOpen())
	{
		processEvents();
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

            case Event::KeyReleased:
            case Event::KeyPressed:
                _event.onKeyboard(event);
            break;

            default:
            break;
		} //SWITCH
	}
}



void Application::update()
{
}


void Application::render()
{
	_window.clear();
	_window.display();
}
