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
    _screenElement[SETTINGSGRAPHIC]= new MenuSettingsGame(&_window_size,&_state,&_oGL,&_gameconfig);
	_window.setFramerateLimit(FPS_MAX);
	_window.setKeyRepeatEnabled(false);
	_window_setting.depthBits = 24;
    _window_setting.antialiasingLevel = 4;
    _window.create(VideoMode(_window_size.x, _window_size.y), L"SFMLTetris", Style::Close | Style::Titlebar | Style::Resize, _window_setting);

    sf::Image * logo = Ressources::getLogoMin();
    _window.setIcon(logo->getSize().x, logo->getSize().y, logo->getPixelsPtr());

    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.f, (WINDOW_WIDTH*((812.0 - 285.0) / _window_size.x))/float(WINDOW_HEIGHT), 1.f, 5000.f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    glViewport(285, 0, WINDOW_WIDTH*((812.0 - 285.0) / _window_size.x), WINDOW_HEIGHT);
}

Application::~Application(){
    ScoreWebSender::saveFailedUpload();

}

















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
                onResize(event);
            break;
            default:
                // gestion du redimentionnement dela fenêtre
                if (event.type == sf::Event::MouseWheelMoved)
                {
                    event.mouseWheel.x = _window.mapPixelToCoords(sf::Vector2i(event.mouseWheel.x, event.mouseWheel.y)).x;
                    event.mouseWheel.y = _window.mapPixelToCoords(sf::Vector2i(event.mouseWheel.x, event.mouseWheel.y)).y;
                }
                else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
                {
                    event.mouseButton.x = _window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)).x;
                    event.mouseButton.y = _window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)).y;
                }
                else if (event.type == sf::Event::MouseMoved)
                {
                    event.mouseMove.x = _window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)).x;
                    event.mouseMove.y = _window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)).y;
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








void Application::onResize(sf::Event &event)
{
    _resized_window_size = Vector2i(event.size.width, event.size.height);
    sf::FloatRect window_rect;
    float rapport = _window_size.x / (float)_window_size.y;
    float new_content_width, view_width, new_content_height, view_height;

    if (_resized_window_size.x / (float)_resized_window_size.y > rapport)
    {   // la fenêtre est plus large que le rapport largeur/hauteur par défaut
        new_content_width = _window_size.x * (event.size.height / (float)_window_size.y);
        view_width = _window_size.x * event.size.width / new_content_width;
        new_content_height = event.size.height;
        view_height = _window_size.y;
        window_rect = sf::FloatRect((_window_size.x - view_width)/2.0, 0,
                                    view_width, _window_size.y);
    }
    else if (_resized_window_size.x / (float) _resized_window_size.y < rapport)
    {   // la fenêtre est moins large que le rapport largeur/hauteur par défaut
        new_content_width = event.size.width;
        view_width = _window_size.x;
        new_content_height = _window_size.y * (event.size.width / (float)_window_size.x);
        view_height = _window_size.y * event.size.height / new_content_height;
        window_rect = sf::FloatRect(0, (_window_size.y - view_height)/2.0,
                                    _window_size.x, view_height);
    }
    else
    {
        new_content_width = event.size.width;
        view_width = _window_size.x;
        new_content_height = event.size.height;
        view_height = _window_size.y;
        window_rect = sf::FloatRect(0, 0, _window_size.x, _window_size.y);
        cout << "bien" << endl;
    }

    sf::View view(window_rect);
    _window.setView(view);

    glViewport((event.size.width - new_content_width)/2.0 + 285 * (new_content_width / (float)_window_size.x),
               (event.size.height - new_content_height)/2.0,
               new_content_width*((812.0 - 285.0) / _window_size.x),
               new_content_height);
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
