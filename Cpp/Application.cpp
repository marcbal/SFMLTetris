#include "Application.hpp"
#include <iostream>

using namespace std;
using namespace sf;

Application::Application() :
    _window_width(WINDOW_WIDTH),
    _window_height(WINDOW_HEIGHT),
    _window(),
    _background(sf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT), 200),
    _state(Index), // correspond à l'état d'affichage (ici, le menu au lancement du programme)
    _menu(sf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT))
{
	_window.setFramerateLimit(FPS_MAX);
    _window_setting.antialiasingLevel = 4;
    _window.create(VideoMode(_window_width, _window_height), L"SFMLTetris", Style::Default, _window_setting);

    _event.addEventConf("pause",sf::Keyboard::Space);

}

Application::~Application(){}

















void Application::run()
{
	while (_window.isOpen())
	{
		processEvents();
		if(!_event.getEventState("pause"))
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
            /*
            case Event::KeyReleased:
            case Event::KeyPressed:
            break;
            */
            case Event::MouseMoved:
                switch(_state){
                    case Index:
                        _menu.onMouseMove(event);
                    break;
                    case Game:
                    break;
                    case Settings:
                    break;
                    default:
                    break;
                }
            break;

            case sf::Event::MouseButtonPressed:
                switch(_state){
                    case Index:
                        _menu.onMouseDown(event);
                    break;
                    case Game:
                    break;
                    case Settings:
                    break;
                    default:
                    break;
                }
            break;


            case sf::Event::MouseButtonReleased:
                switch(_state){
                    case Index:
                        _menu.onMouseUp(event);
                    break;
                    case Game:
                    break;
                    case Settings:
                    break;
                    default:
                    break;
                }
            break;

            default:
            break;
		} //SWITCH
	}
}












void Application::update()
{
    _background.update();

	if (_state == Index)
        _menu.update();
    else if (_state == Game)
        { }
    else if (_state == Settings)
        { }
}












void Application::render()
{
	_window.clear();
	_window.draw(_background);

	if (_state == Index)
        _window.draw(_menu);
    else if (_state == Game)
        { }
    else if (_state == Settings)
        { }

	_window.display();
}
