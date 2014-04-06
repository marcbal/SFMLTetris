#ifndef MENUSETTINGS_TOUCHES_H
#define MENUSETTINGS_TOUCHES_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


#include "Bouton.hpp"
#include "ScreenElement.hpp"
#include "Application.hpp"
#include "Menu.hpp"
using namespace std;
using namespace sf;



class MenuSettingsTouches : public Menu
{
    public:

        MenuSettingsTouches(sf::Vector2i window_size,char *state);

};

#endif // MENUSETTINGS_TOUCHES_H


