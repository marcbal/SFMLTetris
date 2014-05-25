#ifndef MENUSETTINGS_TOUCHES_H
#define MENUSETTINGS_TOUCHES_H


#include "headers.hpp"

#include "Bouton.hpp"
#include "ScreenElement.hpp"
#include "Application.hpp"
#include "Menu.hpp"
#include "InputKey.hpp"
#include "InputCheck.hpp"
#include "Evenement.hpp"
#include "GameConfiguration.hpp"
using namespace std;
using namespace sf;



class MenuSettingsTouches : public Menu
{
    protected:
        vector<InputKey> _inputKey;
        InputCheck _checkMouse;
        sf::Text _textMouse;
        Evenement * _evenement;
        GameConfiguration * _gameConfig;
    public:

        MenuSettingsTouches(sf::Vector2i * window_size,char *state,Evenement * evenement, GameConfiguration * gameConfig);

    virtual void onEvent(sf::Event & event);
    protected:
     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // MENUSETTINGS_TOUCHES_H


