#ifndef MENUSETTINGSGRAPHICS_HPP
#define MENUSETTINGSGRAPHICS_HPP

#include "Menu.hpp"
#include "GameConfiguration.hpp"
#include "InputRange.hpp"
#include "InputCheck.hpp"
#include "Bouton.hpp"


class MenuSettingsGraphics : public Menu
{
    public:
        MenuSettingsGraphics(sf::Vector2i * window_size,char * state,GameConfiguration * gameConfig, sf::RenderWindow * window);
        virtual ~MenuSettingsGraphics();
        virtual void onEvent(sf::Event & event);
        virtual void update();
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:

        GameConfiguration * _gameConfig;


        InputRange _antialias;
        sf::Text textAntialias;
        InputRange _FPS;
        sf::Text textFPS;
        InputRange _BGPart;
        sf::Text textBGPart;
        InputRange _BGSpeed;
        sf::Text textBGSpeed;
        InputRange _BGPSize;
        sf::Text textBGPSize;


        InputCheck _activateExplosions;
        sf::Text textActivateExplosions;
        InputCheck _activate3D;
        sf::Text textActivate3D;

        sf::RenderWindow * _window;
        char appliquer;
};

#endif // MENUSETTINGSGRAPHICS_HPP
