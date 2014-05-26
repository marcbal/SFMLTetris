#ifndef _MENU_SETTINGS_GRAPHIC_HPP_
#define _MENU_SETTINGS_GRAPHIC_HPP_

#include "headers.hpp"
#include "Menu.hpp"
#include "GameConfiguration.hpp"

#include "Application.hpp"
#include "InputCheck.hpp"
#include "InputRange.hpp"
#include "InputText.hpp"
#include "OpenGL_Manager.hpp"
#include "Ressources.hpp"
#include "Game.hpp"

class MenuSettingsGame : public Menu{

private :
    OpenGL_Manager * _oGL;
    GameConfiguration * _gameConfig;
    InputCheck _activateExplosions;
    sf::Text textActivateExplosions;
    InputCheck _activateGhost;
    sf::Text textActivateGhost;
    InputCheck _activate3D;
    sf::Text textActivate3D;
    InputCheck _activateAutorotation;
    sf::Text textActivateAutorotation;
    InputCheck _onlineScore;
    sf::Text textOnlineScore;

    InputText _enterPseudo;
public :
    MenuSettingsGame(sf::Vector2i * window_size,char *state,OpenGL_Manager * oGL, GameConfiguration* gameConfig);
    virtual void onEvent(sf::Event & event);
    virtual void update();
protected:
     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // _MENU_SETTINGS_GRAPHIC_HPP_

