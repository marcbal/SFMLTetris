#include "InputCheck.hpp"
#include <iostream>
using namespace std;
using namespace sf;

InputCheck::InputCheck(sf::Vector2f pos, sf::Vector2f taille,bool val){
    _mouseHover = _mouseClick = false;
    _pos = pos;
    _size = taille;
    _val = val;

    checkCase.setOutlineColor(sf::Color::White);
    checkCase.setOutlineThickness(2);

    updateGraphic();
}

void InputCheck::onEvent(Event & event){
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

void InputCheck::onMouseDown(Event & event){

}

void InputCheck::onMouseUp(Event & event){

        if (event.mouseButton.button != sf::Mouse::Left)
        return;

        if(_mouseHover){
        _val = !_val;
        updateGraphic();
        }
}

void InputCheck::onMouseMove(Event & event){
    _mouseHover = pointInRect(_pos,_size,Vector2f(event.mouseMove.x,event.mouseMove.y));
}

void InputCheck::updateGraphic(){
    if(_val)
    checkCase.setFillColor(Color(220,220,220));
    else
    checkCase.setFillColor(Color(50,50,50));

    checkCase.setSize(_size);
    checkCase.setPosition(_pos);
}

void InputCheck::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(checkCase,states);
}

void InputCheck::setPosition(sf::Vector2f pos){
    _pos = pos;
}

void InputCheck::setSize(sf::Vector2f taille){
    _size = taille;
}

bool InputCheck::getValue(){
    return _val;
}
