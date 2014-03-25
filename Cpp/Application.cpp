#include "Application.h"
#include "fn_time.h"

Application::Application() :
    _window_width(1280),
    _window_height(720),
    _window()
{

	frame_time = 1.0/frame_per_sec_max;

    _window_setting.antialiasingLevel = 8;
    _window.create(VideoMode(_window_width, _window_height), L"SFMLTetris", Style::Default, _window_setting);


}

Application::~Application(){}





void Application::run()
{
    // les variables de type sf::Time et les autres calcul sur le temps servent à calculer les performances du jeu.
    sf::Time t1 = _app_clock.getElapsedTime(), t2, t_diff;
	double santee = 1.0;
	// santee correspond aux FPS courant / FPS max (dans le cas où FPS courant < FPS max)
	// ou au temps de calcul de la frame sur la durée maximale disponible (1 seconde / FPS max)
	// lag : l'inverse de la santée : correspond à la hauteur d'une barre sur un lagomètre
	while (_window.isOpen())
	{

		processEvents();
		update();
		render();




		t2 = _app_clock.getElapsedTime();
		t_diff = t2 - t1;

		santee = (frame_time/t_diff.asSeconds());
		frame_per_sec = (santee > 1.0)?frame_per_sec_max:frame_per_sec_max*santee;

        // pause du programme pour respecter le nombre de FPS max;
		pause(frame_time - t_diff.asSeconds());

		t1 = _app_clock.getElapsedTime();

	}
}




void Application::processEvents()
{
    sf::Event event;
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
