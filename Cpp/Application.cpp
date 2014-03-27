#include "Application.h"
#include "fn_time.h"

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

		if (event.type == sf::Event::Closed)
			_window.close();
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
