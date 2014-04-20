#ifndef MENUSETTINGS_TOUCHES_H
#define MENUSETTINGS_TOUCHES_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>


#include "Bouton.hpp"
#include "ScreenElement.hpp"
#include "Application.hpp"
#include "Menu.hpp"
#include "InputKey.hpp"
#include "Evenement.hpp"
using namespace std;
using namespace sf;



class MenuSettingsTouches : public Menu
{
    protected:
        vector<InputKey> _inputKey;
        Evenement * _evenement;
    public:

        MenuSettingsTouches(sf::Vector2i * window_size,char *state,Evenement * evenement);

    virtual void onEvent(sf::Event & event);
    protected:
     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // MENUSETTINGS_TOUCHES_H


