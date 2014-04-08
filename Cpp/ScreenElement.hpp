#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class ScreenElement : public sf::Drawable
{
    protected:

        sf::Vector2i _window_size;

        //sf::Drawable
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:
        virtual void onEvent(sf::Event & event);


        virtual void update();



};


#endif // _SCREEN_HPP_
