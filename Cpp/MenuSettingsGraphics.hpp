#ifndef MENUSETTINGSGRAPHICS_HPP
#define MENUSETTINGSGRAPHICS_HPP

#include "Menu.hpp"
#include "GameConfiguration.hpp"


class MenuSettingsGraphics : public Menu
{
    public:
        MenuSettingsGraphics(sf::Vector2i * window_size,char * state,GameConfiguration * gameConfig);
        virtual ~MenuSettingsGraphics();
        virtual void onEvent(sf::Event & event);
        virtual void update();
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:

        GameConfiguration * _gameConfig;
};

#endif // MENUSETTINGSGRAPHICS_HPP
