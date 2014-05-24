#include "Application.hpp"

#include <iostream>

using namespace std;
using namespace sf;

Application::Application() :
    _window_size(WINDOW_WIDTH, WINDOW_HEIGHT),
    _window(),
    _background(_window_size, 200),
    _state(INDEX), // correspond à l'état d'affichage (ici, le menu au lancement du programme)
    _scores()
{
    _screenElement[INDEX]= new MenuIndex(&_window_size,&_state);
    _screenElement[GAME]= new Game(&_window_size,&_state,&_event,&_scores,&_oGL);
    _screenElement[SCORE]= new ScreenScore(&_window_size,&_state,&_scores);
    _screenElement[SETTINGS]= new MenuSettings(&_window_size,&_state);
    _screenElement[SETTINGSTOUCHES]= new MenuSettingsTouches(&_window_size,&_state,&_event);
    _screenElement[SETTINGSAUDIO]= new MenuSettingsAudio(&_window_size,&_state,&_audio);
    _screenElement[SETTINGSGRAPHIC]= new MenuSettingsGraphic(&_window_size,&_state,&_oGL);
	_window.setFramerateLimit(FPS_MAX);
	_window.setKeyRepeatEnabled(false);
	_window_setting.depthBits = 24;
    _window_setting.antialiasingLevel = 4;
    _window.create(VideoMode(_window_size.x, _window_size.y), L"SFMLTetris", Style::Close | Style::Titlebar, _window_setting);
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, WINDOW_WIDTH/float(WINDOW_HEIGHT), 1.f, 5000.f);

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
    _audio.update();
}









void test(float t);


void Application::render()
{
    _window.pushGLStates();
	_window.draw(_background);

    _window.draw(*_screenElement[(int)_state]);
    _window.popGLStates();
	_window.display();
}

void test(float t){

        // Clear color and depth buffer
        glClear(GL_DEPTH_BUFFER_BIT);

        // Apply some transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -200.f);
        glRotatef(t * 50, 1.f, 0.f, 0.f);
        glRotatef(t * 30, 0.f, 1.f, 0.f);
        glRotatef(t * 90, 0.f, 0.f, 1.f);


        // Draw a cube
        glBegin(GL_QUADS);
            glColor3f( 1.0, 0.0, 0.0 );
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f( 50.f,  50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);

            glColor3f( 0.0, 1.0, 0.0 );
            glVertex3f(-50.f, -50.f, 50.f);
            glVertex3f(-50.f,  50.f, 50.f);
            glVertex3f( 50.f,  50.f, 50.f);
            glVertex3f( 50.f, -50.f, 50.f);

            glColor3f( 1.0, 1.0, 0.0 );
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f(-50.f,  50.f,  50.f);
            glVertex3f(-50.f, -50.f,  50.f);

            glColor3f( 0.0, 0.0, 1.0 );
            glVertex3f(50.f, -50.f, -50.f);
            glVertex3f(50.f,  50.f, -50.f);
            glVertex3f(50.f,  50.f,  50.f);
            glVertex3f(50.f, -50.f,  50.f);

            glColor3f( 1.0, 0.0, 1.0 );
            glVertex3f(-50.f, -50.f,  50.f);
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f,  50.f);
            glColor3f( 0.0, 1.0, 1.0 );
            glVertex3f(-50.f, 50.f,  50.f);
            glVertex3f(-50.f, 50.f, -50.f);
            glVertex3f( 50.f, 50.f, -50.f);
            glVertex3f( 50.f, 50.f,  50.f);
        glEnd();

}
