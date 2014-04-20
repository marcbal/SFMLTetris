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
    _fond.setOutlineThickness(2);
    _fond.setPosition(_pos);
    _fond.setSize(_size);
    _text.setCharacterSize(20);
    sf::Font * menuFont = new sf::Font();
    menuFont->loadFromFile("res/LiberationMono-Regular.ttf");
    _text.setFont(*menuFont);

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

}

void InputKey::onMouseDown(Event & event){

}
void InputKey::onKeyUp(Event & event){
    if(!_isActive)
        return;

    _event->addEventConf(_eventName,event.key.code);
    _isActive = false;

    updateGraphic();
}

void InputKey::onMouseUp(Event & event){

        if (event.mouseButton.button != sf::Mouse::Left)
        return;
        if(_mouseHover)
        _isActive = !_isActive;
        else
        _isActive = false;
        updateGraphic();
}

void InputKey::onMouseMove(Event & event){
    _mouseHover = pointInRect(_pos,_size,Vector2f(event.mouseMove.x,event.mouseMove.y));
}

void InputKey::updateGraphic(){
    if(_isActive){
        _fond.setFillColor(Color(180,180,180));
        _text.setColor(Color::Black);
        _text.setString(L"Appuyer sur une touche");
    }
    else{
        _fond.setFillColor(Color(50,50,50));
        _text.setColor(Color::White);
        _text.setString(_eventName + " : " + Evenement::keyToString(_event->getEventKey(_eventName)));
    }

    _text.setOrigin(0, 0);
    _text.setPosition(0, 0);
    _text.setOrigin(_text.getGlobalBounds().left + _text.getGlobalBounds().width/2.0,
                    _text.getGlobalBounds().top + _text.getGlobalBounds().height/2.0);
    _text.setPosition(_pos.x+_size.x/2.0,
                      _pos.y+_size.y/2.0);

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

