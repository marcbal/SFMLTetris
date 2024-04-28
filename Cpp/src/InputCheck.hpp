#ifndef InputCheck_HPP
#define InputCheck_HPP


#include "headers.hpp"
#include "Collision.hpp"
#include "Ressources.hpp"

class InputCheck : public sf::Drawable
{
    protected:

    bool _mouseHover;
    bool _mouseClick;

    sf::Vector2f _pos;
    sf::Vector2f _size;

    bool _val;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void onMouseMove(sf::Event & event);
    virtual void onMouseDown(sf::Event & event);
    virtual void onMouseUp(sf::Event & event);

    sf::RectangleShape checkCase;
    sf::RectangleShape checkedRectangle;

    virtual void updateGraphic();

    public :

    InputCheck(sf::Vector2f pos, sf::Vector2f taille,bool val);

    virtual void onEvent(sf::Event & event);
    virtual void setPosition(sf::Vector2f pos);
    virtual void setSize(sf::Vector2f taille);
    virtual bool getValue();
};

#endif // InputCheck_HPP
