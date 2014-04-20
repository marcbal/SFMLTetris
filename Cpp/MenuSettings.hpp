#ifndef MENUSETTINGS_H
#define MENUSETTINGS_H


#include "headers.hpp"
#include "Bouton.hpp"
#include "ScreenElement.hpp"
#include "Application.hpp"
#include "Menu.hpp"
using namespace std;
using namespace sf;



class MenuSettings : public Menu
{
    public:
        MenuSettings(sf::Vector2i * window_size,char *state);

};

#endif // MENUSETTINGS_H

