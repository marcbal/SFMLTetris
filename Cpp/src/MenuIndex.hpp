#ifndef MENUINDEX_H
#define MENUINDEX_H


#include "headers.hpp"
#include "Bouton.hpp"
#include "BoutonLink.hpp"
#include "ScreenElement.hpp"
#include "Application.hpp"
#include "Menu.hpp"
using namespace std;
using namespace sf;



class MenuIndex : public Menu
{
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        BoutonLink lien;
        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:



        virtual void onEvent(sf::Event & event);

        MenuIndex(sf::Vector2i * window_size,char *state);





};

#endif // MENUINDEX_H
