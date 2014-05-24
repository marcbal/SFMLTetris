#ifndef _MENU_SETTINGS_GRAPHIC_HPP_
#define _MENU_SETTINGS_GRAPHIC_HPP_

#include "headers.hpp"
#include "Menu.hpp"
#include "AudioConfiguration.hpp"
#include "Application.hpp"
#include "InputCheck.hpp"
#include "InputRange.hpp"
#include "OpenGL_Manager.hpp"

class MenuSettingsGraphic : public Menu{

private :
    OpenGL_Manager * _oGL;
    InputCheck _activate3D;
    InputRange _inclinaison;
public :
    MenuSettingsGraphic(sf::Vector2i * window_size,char *state,OpenGL_Manager * oGL);
    virtual void onEvent(sf::Event & event);
protected:
     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // _MENU_SETTINGS_GRAPHIC_HPP_

