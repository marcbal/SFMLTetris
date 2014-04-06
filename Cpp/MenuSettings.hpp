#ifndef MENUSETTINGS_H
#define MENUSETTINGS_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


#include "Bouton.hpp"
#include "ScreenElement.hpp"
#include "Application.hpp"
#include "Menu.hpp"
using namespace std;
using namespace sf;



class MenuSettings : public Menu
{
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        // sf::Drawable
    public:




        MenuSettings(sf::Vector2i window_size,char *state);




};

#endif // MENUSETTINGS_H

