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
    checkCase.setOutlineThickness(-2);
    checkCase.setFillColor(Color(0, 0, 0, 192));
    checkedRectangle.setFillColor(sf::Color::White);

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
    updateGraphic();
}

void InputCheck::onMouseDown(Event & event){
    if (event.mouseButton.button != sf::Mouse::Left)
        return;
    _mouseClick = _mouseHover;
}

void InputCheck::onMouseUp(Event & event){

    if (event.mouseButton.button != sf::Mouse::Left)
        return;
    ;

    if(_mouseHover && _mouseClick){
        _val = !_val;
    }
    _mouseClick = false;
}

void InputCheck::onMouseMove(Event & event){
    _mouseHover = pointInRect(_pos,_size,Vector2f(event.mouseMove.x,event.mouseMove.y));
}

void InputCheck::updateGraphic(){

    checkCase.setSize(_size);
    checkCase.setPosition(_pos);
    checkCase.setFillColor((_mouseClick)?Color(160, 160, 160):((_mouseHover)?Color(128, 128, 128):Color(0, 0, 0)));

    checkedRectangle.setSize(sf::Vector2f(((_size.x-4)-2*(int)((_size.x-4)/4)), ((_size.y-4)-2*(int)((_size.y-4)/4))));
    checkedRectangle.setPosition(_pos+sf::Vector2f((int)((_size.x-4)/4 + 2), (int)((_size.y-4)/4 + 2)));
}

void InputCheck::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(checkCase,states);
    if (_val)
        target.draw(checkedRectangle, states);
}

void InputCheck::setPosition(sf::Vector2f pos){
    _pos = pos;
    updateGraphic();
}

void InputCheck::setSize(sf::Vector2f taille){
    _size = taille;
    updateGraphic();
}

bool InputCheck::getValue(){
    return _val;
}
