#ifndef BOUTON_HPP
#define BOUTON_HPP


#include "headers.hpp"
#include "Collision.hpp"
#include "Ressources.hpp"
using namespace std;
using namespace sf;

class Bouton : public sf::Drawable
{
    protected:
        bool _mouseHover;
        bool _mouseClick;

        sf::Vector2f _position;
        sf::Vector2f _size;

        sf::String texteString;
        sf::Text texte;
        sf::RectangleShape shapeDefault;
        sf::RectangleShape shapeHover;
        sf::RectangleShape shapeClick;

        char * _state;
        char _action;

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    public:








        Bouton(sf::Vector2f pos, sf::Vector2f taille,int taillePolice,char * _state,char action);
        Bouton(sf::Vector2f pos, sf::Vector2f taille,int taillePolice,char * _state);
        virtual ~Bouton();

        virtual void setPosition(sf::Vector2f pos);
        virtual void setSize(sf::Vector2f taille);
        virtual void setText(sf::String str);
        virtual void setAction(char action);


        virtual void onMouseMove(sf::Event & event);
        virtual void onMouseDown(sf::Event & event);
        virtual void onMouseUp(sf::Event & event);

        bool isClicked();
        bool isHover();


    protected:

        void updateTextPosition();
};



#endif // BOUTON_HPP
