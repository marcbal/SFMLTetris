#ifndef MENUINDEX_H
#define MENUINDEX_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Bouton.hpp"
#include "ScreenElement.hpp"
#include "Application.hpp"
using namespace std;
using namespace sf;

class MenuIndex : public ScreenElement
{
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        vector<Bouton> menuElements;

        sf::Vector2i _window_size;
        char *_state;
        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:




        MenuIndex(sf::Vector2i window_size,char *state);
        virtual ~MenuIndex();

        virtual void onEvent(sf::Event & event);
        void onMouseMove(sf::Event & event);
        void onMouseDown(sf::Event & event);
        void onMouseUp(sf::Event & event);


        void update();



};

#endif // MENUINDEX_H
