#ifndef INPUT_RANGE_HPP
#define INPUT_RANGE_HPP


#include "headers.hpp"
#include "Collision.hpp"

using namespace std;
using namespace sf;

class InputRange : public Drawable
{
    protected:

        bool _mouseHover;
        bool _mouseClick;

        sf::Vector2f _position;
        sf::Vector2f _size;

        sf::Vector2i _positionMouse;


        sf::RectangleShape cursorDefault;

        sf::RectangleShape leftPart;
        sf::RectangleShape rightPart;

        float valMin;
        float val;
        float valMax;

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void majGraphique();
        virtual void onMouseMove(sf::Event & event);
        virtual void onMouseDown(sf::Event & event);
        virtual void onMouseUp(sf::Event & event);
        virtual void updateVal();

    public:
        virtual void onEvent(sf::Event & event);
        InputRange(sf::Vector2f pos, sf::Vector2f taille,float _val,float _min,float _max);
//        InputRange(sf::Vector2f pos, sf::Vector2f taille,float val,float _max);
//        InputRange(sf::Vector2f pos, sf::Vector2f taille,float _max);
//        InputRange(sf::Vector2f pos, sf::Vector2f taille);
//        virtual ~Bouton();

        virtual void setPosition(sf::Vector2f pos);
        virtual void setSize(sf::Vector2f taille);
        virtual float getValue();

};



#endif // INPUT_RANGE_HPP

