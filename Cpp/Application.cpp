#include "Application.hpp"

#include <iostream>

using namespace std;
using namespace sf;

Application::Application() :
    _window_size(WINDOW_WIDTH, WINDOW_HEIGHT),
    _window(),
    _background(_window_size, 200),
    _gameconfig(),
    _oGL(&_gameconfig),
    _state(INDEX), // correspond à l'état d'affichage (ici, le menu au lancement du programme)
    _scores()
{

    _resized_window_size = _window_size;

    _screenElement[INDEX]= new MenuIndex(&_window_size,&_state);
    _screenElement[GAME]= new Game(&_window_size,&_state,&_event,&_scores,&_oGL,&_gameconfig);
    _screenElement[SCORE]= new ScreenScore(&_window_size,&_state,&_scores);
    _screenElement[SETTINGS]= new MenuSettings(&_window_size,&_state);
    _screenElement[SETTINGSTOUCHES]= new MenuSettingsTouches(&_window_size,&_state,&_event,&_gameconfig);
    _screenElement[SETTINGSAUDIO]= new MenuSettingsAudio(&_window_size,&_state,&_audio);
    _screenElement[SETTINGSGRAPHIC]= new MenuSettingsGraphic(&_window_size,&_state,&_oGL,&_gameconfig);
	_window.setFramerateLimit(FPS_MAX);
	_window.setKeyRepeatEnabled(false);
	_window_setting.depthBits = 24;
    _window_setting.antialiasingLevel = 4;
    _window.create(VideoMode(_window_size.x, _window_size.y), L"SFMLTetris", Style::Close | Style::Titlebar | Style::Resize, _window_setting);


    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, WINDOW_WIDTH/float(WINDOW_HEIGHT), 1.f, 5000.f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

}

Application::~Application(){}

















void Application::run()
{
	while (_window.isOpen())
	{
        _window.clear();
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
            case Event::Resized:
                _resized_window_size = Vector2i(event.size.width, event.size.height);
                glViewport(0, 0, event.size.width, event.size.height);
            break;
            default:
                // gestion du redimentionnement dela fenêtre
                if (event.type == sf::Event::MouseWheelMoved)
                {
                    event.mouseWheel.x *= _window_size.x / (float) _resized_window_size.x;
                    event.mouseWheel.y *= _window_size.y / (float) _resized_window_size.y;
                }
                else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
                {
                    event.mouseButton.x *= _window_size.x / (float) _resized_window_size.x;
                    event.mouseButton.y *= _window_size.y / (float) _resized_window_size.y;
                }
                else if (event.type == sf::Event::MouseMoved)
                {
                    event.mouseMove.x *= _window_size.x / (float) _resized_window_size.x;
                    event.mouseMove.y *= _window_size.y / (float) _resized_window_size.y;
                }
                // -----------------------------------------

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
    _audio.update();
}






void Application::render()
{
    _window.pushGLStates();
	_window.draw(_background);

    _window.draw(*_screenElement[(int)_state]);
    _window.popGLStates();
	_window.display();
}
