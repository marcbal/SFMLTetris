#include "InputRange.hpp"
#include "Bouton.hpp"

using namespace std;
using namespace sf;

InputRange::InputRange(sf::Vector2f pos, sf::Vector2f taille,float _val,float _min,float _max)
{
    _mouseHover=false;
    _mouseClick=false;

    _position=pos;
    _size=taille;

    cursorDefault.setOutlineColor(Color::White);
    cursorDefault.setOutlineThickness(-2);
    cursorDefault.setSize(Vector2f(14,taille.y+20));
//    cursorHover;
//    cursorClick;

    rightPart.setFillColor(Color(0, 0, 0, 192));
    rightPart.setOutlineColor(Color::White);
    rightPart.setOutlineThickness(-2);
    leftPart.setFillColor(Color(160, 160, 160));
    leftPart.setOutlineColor(Color::White);
    leftPart.setOutlineThickness(-2);

    valMin=_min;
    val=_val;
    valMax=_max;

    majGraphique();


}

void InputRange::setPosition(sf::Vector2f pos)
{
    _position = pos;
}
void InputRange::setSize(sf::Vector2f taille)
{
    _size = taille;
}


void InputRange::majGraphique()
{
    float middle = ((val-valMin)/(valMax-valMin))*_size.x + _position.x;

    leftPart.setPosition(_position);
    leftPart.setSize(Vector2f(middle-_position.x,_size.y));

    rightPart.setPosition(Vector2f(middle,_position.y));
    rightPart.setSize(Vector2f(_size.x-(middle-_position.x),_size.y));

    cursorDefault.setPosition(Vector2f(middle-7,_position.y-10));

    cursorDefault.setFillColor((_mouseClick)?Color(160, 160, 160):((_mouseHover)?Color(128, 128, 128):Color(0, 0, 0)));
}

void InputRange::onMouseMove(sf::Event & event)
{
    _mouseHover = pointInRect(_position,_size,Vector2f(event.mouseMove.x,event.mouseMove.y))
                || pointInRect(cursorDefault.getPosition(),cursorDefault.getSize(),Vector2f(event.mouseMove.x,event.mouseMove.y));
    _positionMouse = Vector2i(event.mouseMove.x,event.mouseMove.y);
    if(_mouseClick)
        updateVal();
    else
        majGraphique();
}

void InputRange::updateVal(){

    if(_positionMouse.x <= _position.x){
        val = valMin;
        majGraphique();
        return;
    }

    if(_positionMouse.x >= _position.x + _size.x){
        val = valMax;
        majGraphique();
        return;
    }

    val=((_positionMouse.x-_position.x)/_size.x)*(valMax-valMin)+valMin;

    majGraphique();
}

void InputRange::onMouseDown(sf::Event & event)
{
    if (event.type != Event::MouseButtonPressed
            || event.mouseButton.button != sf::Mouse::Left)
        return;

    _mouseClick = _mouseHover;

    if(_mouseHover)
        updateVal();

}
void InputRange::onMouseUp(sf::Event & event)
{
    if (event.type != Event::MouseButtonReleased
            || event.mouseButton.button != sf::Mouse::Left)
        return;

    _mouseClick = false;

    majGraphique();
}


void InputRange::onEvent(sf::Event & event){
    switch(event.type)
    {
        case sf::Event::MouseMoved:
            onMouseMove(event);
        break;
        case sf::Event::MouseButtonPressed:
            onMouseDown(event);
        break;
        case sf::Event::MouseButtonReleased:
            onMouseUp(event);
        break;
        default:
        break;
    }

}

float InputRange::getValue(){
    return val;
}

void InputRange::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(leftPart,states);
    target.draw(rightPart,states);
    target.draw(cursorDefault,states);
}


