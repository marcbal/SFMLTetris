#ifndef BOUTON_HPP
#define BOUTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include "Collision.hpp"
using namespace std;
using namespace sf;

class Bouton : public sf::Drawable
{
    private:
        bool _mouseHover;
        bool _mouseClick;

        sf::Vector2f _position;
        sf::Vector2f _size;

        sf::String texteString;


        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    public:
        // public pour facilier l'édition du shape
        sf::RectangleShape shapeDefault;
        sf::RectangleShape shapeHover;
        sf::RectangleShape shapeClick;


        sf::Text texte;




        Bouton(sf::Vector2f pos, sf::Vector2f taille);
        virtual ~Bouton();

        void setPosition(sf::Vector2f pos);
        void setSize(sf::Vector2f taille);
        void setText(sf::String str);


        void onMouseMove(sf::Event & event);
        void onMouseDown(sf::Event & event);
        void onMouseUp(sf::Event & event);



    protected:

        void updateTextPosition();
};



#endif // BOUTON_HPP
