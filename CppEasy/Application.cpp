#include "Application.hpp"

#include <iostream>

using namespace std;
using namespace sf;

Application::Application() :
    _window_size(WINDOW_WIDTH, WINDOW_HEIGHT),
    _window(),
    _game(&_window_size)
{

	_window.setFramerateLimit(FPS_MAX);
	_window.setKeyRepeatEnabled(false);
    _window.create(VideoMode(_window_size.x, _window_size.y), L"Tetris", Style::Close | Style::Titlebar);

}

Application::~Application(){

}

















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
            default:
                _game.onEvent(event);
            break;
		} //SWITCH
	}
}













void Application::update()
{
    _game.update();
}






void Application::render()
{
    _window.clear(sf::Color::White);
    _window.draw(_game);
	_window.display();
}
