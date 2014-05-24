#include "InputKey.hpp"
#include <iostream>

using namespace std;
using namespace sf;

InputKey::InputKey(sf::Vector2f pos, sf::Vector2f taille,string eventName,Evenement * event){
    _mouseHover = _isActive = false;
    _pos = pos;
    _size = taille;
    _eventName = eventName;
    _event = event;

    _fond.setOutlineColor(sf::Color::White);
    _fond.setOutlineThickness(-2);
    _fond.setPosition(_pos);
    _fond.setSize(_size);
    _text.setCharacterSize(20);
    _text.setFont(*Ressources::getDefaultFont());

    updateGraphic();

}

void InputKey::onEvent(Event & event){
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
        case sf::Event::KeyReleased:
            onKeyUp(event);
        break;
        default:
        break;
    }
    updateGraphic();
}

void InputKey::onMouseDown(Event & event){

}
void InputKey::onKeyUp(Event & event){
    if(!_isActive)
        return;

    _event->addEventConf(_eventName,event.key.code);
    _isActive = false;

}

void InputKey::onMouseUp(Event & event){

        if (event.mouseButton.button != sf::Mouse::Left)
        return;
        if(_mouseHover)
        _isActive = !_isActive;
        else
        _isActive = false;
}

void InputKey::onMouseMove(Event & event){
    _mouseHover = pointInRect(_pos,_size,Vector2f(event.mouseMove.x,event.mouseMove.y));
}

void InputKey::updateGraphic(){
    if(_isActive){
        _fond.setFillColor(Color(160, 160, 160));
        _text.setColor(Color::Black);
        _text.setString("Appuyez sur une touche");
    }
    else{
        _fond.setFillColor((_mouseHover)?Color(128, 128, 128):Color(0, 0, 0, 192));
        _text.setColor(Color::White);
        _text.setString(_eventName + " : " + Evenement::keyToString(_event->getEventKey(_eventName)));
    }

    _text.setOrigin(0, 0);
    _text.setPosition(0, 0);
    _text.setOrigin((int) (_text.getGlobalBounds().left + _text.getGlobalBounds().width/2.0),
                    (int)(_text.getGlobalBounds().top + _text.getGlobalBounds().height/2.0));
    _text.setPosition((int)(_pos.x+_size.x/2.0),
                      (int)(_pos.y+_size.y/2.0));

}

void InputKey::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_fond,states);
    target.draw(_text,states);
}

void InputKey::setPosition(sf::Vector2f pos){
    _pos = pos;
}

void InputKey::setSize(sf::Vector2f taille){
    _size = taille;
}

