#ifndef MENUINDEX_H
#define MENUINDEX_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Bouton.hpp"

using namespace std;
using namespace sf;

class MenuIndex : public sf::Drawable
{
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        vector<Bouton> menuElements;

        sf::Vector2i _window_size;

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:




        MenuIndex(sf::Vector2i window_size);
        virtual ~MenuIndex();


        void onMouseMove(sf::Event & event);
        void onMouseDown(sf::Event & event);
        void onMouseUp(sf::Event & event);


        void update();



};

#endif // MENUINDEX_H
