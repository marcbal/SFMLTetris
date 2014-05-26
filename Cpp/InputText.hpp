#ifndef InputText_HPP
#define InputText_HPP

#include "headers.hpp"
#include "Collision.hpp"
#include "Ressources.hpp"

class InputText : public sf::Drawable
{
    protected:

    bool _mouseHover;
    bool _active;
    bool _affCursor;

    sf::Vector2f _pos;
    sf::Vector2f _size;


    std::string _val;
    sf::Text _text;

    sf::Clock _cursorClocker;


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void onMouseMove(sf::Event & event);
    virtual void onMouseUp(sf::Event & event);
    virtual void onTextEntered(sf::Event & event);
    virtual void updateTextPosition();
    sf::RectangleShape textArea;
    sf::RectangleShape textCursor;

    virtual void updateGraphic();

    public :

    InputText(sf::Vector2f pos, sf::Vector2f taille,sf::String val);
    virtual void update();
    virtual void onEvent(sf::Event & event);
    virtual void setPosition(sf::Vector2f pos);
    virtual void setSize(sf::Vector2f taille);
    virtual sf::String getValue();
};

#endif // InputText_HPP

