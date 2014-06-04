#include "InputText.hpp"
#include <iostream>
using namespace std;
using namespace sf;

InputText::InputText(sf::Vector2f pos, sf::Vector2f taille,sf::String val){
    _mouseHover = false;
    _affCursor = false;
    _active = false;
    _pos = pos;
    _size = taille;
    _val = val;
    _cursorPosition = _val.size();
    textArea.setOutlineColor(sf::Color::White);
    textArea.setOutlineThickness(-2);
    textArea.setFillColor(Color(0, 0, 0, 192));
    textArea.setOutlineColor(sf::Color::White);

    textCursor.setFillColor(sf::Color::White);
    textCursor.setSize(Vector2f(1,20));

    _text.setCharacterSize(20);
    _text.setColor(sf::Color::White);
    _text.setFont(*Ressources::getDefaultFont());
    _text.setPosition(_pos);
    _text.setString(_val);


    updateGraphic();
}

void InputText::onKeyPressed(sf::Event & event){
    if(!_active)
        return;

    switch(event.key.code){
        case Keyboard::Left:
            if(_cursorPosition > 0)
            _cursorPosition--;
        break;
        case Keyboard::Right:
            if(_cursorPosition < _val.size())
            _cursorPosition ++;
        break;
        default:
        break;

    }

    _cursorClocker.restart();
    _affCursor = true;
}

void InputText::onEvent(Event & event){
    switch(event.type)
    {
        case sf::Event::MouseMoved:
            onMouseMove(event);
        break;
        case sf::Event::MouseButtonReleased:
            onMouseUp(event);
        break;
        case sf::Event::TextEntered:
            onTextEntered(event);
        break;
        case sf::Event::KeyPressed:
            onKeyPressed(event);
        break;
        default:
        break;
    }
    updateGraphic();
}

void InputText::onMouseUp(Event & event){
    if (event.mouseButton.button != sf::Mouse::Left)
        return;
    _active = _mouseHover;
    if(_active){
        if(_val.size()==0){
            _cursorPosition=0;
            return;
        }
        int relative = event.mouseButton.x - _text.getPosition().x +_text.getGlobalBounds().width/2;
        if(relative>0)
        _cursorPosition = relative/(_text.getGlobalBounds().width/_val.size());
        else
        _cursorPosition = 0;

        if(_cursorPosition>_val.size())
            _cursorPosition = _val.size();

        _cursorClocker.restart();
        _affCursor = true;
    }
}

void InputText::update(){
    if(_active && _cursorClocker.getElapsedTime().asSeconds()>0.5){
        _affCursor = !_affCursor;
        _cursorClocker.restart();
    }
}

void InputText::onMouseMove(Event & event){
    _mouseHover = pointInRect(_pos,_size,Vector2f(event.mouseMove.x,event.mouseMove.y));
}

void InputText::onTextEntered(Event & event){

    if(!_active)
        return;
    if(event.text.unicode > 31 && event.text.unicode < 127 && _val.size()<29){
        if(_cursorPosition != _val.size())
            _val = _val.substr(0,_cursorPosition)+event.text.unicode+_val.substr(_cursorPosition,_val.size()-1);
        else
            _val += event.text.unicode;
        _cursorPosition ++;

    }

    else if(event.text.unicode == 8 && _cursorPosition>0){
        if(_cursorPosition != _val.size())
            _val =  _val.substr(0,_cursorPosition-1)+_val.substr(_cursorPosition,_val.size()-1);
        else
             _val = _val.substr(0,_val.size()-1);

        _cursorPosition --;
    }
    else if(event.text.unicode == 127 && _cursorPosition<_val.size()){
        if(_cursorPosition != 0)
            _val =  _val.substr(0,_cursorPosition)+_val.substr(_cursorPosition+1,_val.size()-1);
        else
             _val = _val.substr(1,_val.size()-1);
    }

    _cursorClocker.restart();
    _affCursor = true;

}

void InputText::updateTextPosition()
{
    _text.setOrigin(0, 0);
    _text.setPosition(0, 0);
    _text.setOrigin((int) (_text.getGlobalBounds().left + _text.getGlobalBounds().width/2.0),
                    (int) (_text.getGlobalBounds().top + _text.getGlobalBounds().height/2.0));
    _text.setPosition((int)(_pos.x+_size.x/2.0),
                      (int)(_pos.y+_size.y/2.0));
}


void InputText::updateGraphic(){
    textArea.setSize(_size);
    textArea.setPosition(_pos);
    if(_mouseHover && !_active)
    textArea.setFillColor(Color(128,128,128));
    else
    textArea.setFillColor(Color(0,0,0,192));




    _text.setString(_val);
    updateTextPosition();
    Vector2f cursorPosition;
    cursorPosition.x =(_text.getPosition().x-_text.getGlobalBounds().width/2);
    if(_val.size()>0)
    cursorPosition.x +=(_cursorPosition*_text.getGlobalBounds().width/_val.size());
    else
    cursorPosition.x += _text.getGlobalBounds().width;

    cursorPosition.y = textArea.getPosition().y-10+textArea.getGlobalBounds().height/2;

    textCursor.setPosition(cursorPosition);
}

void InputText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(textArea,states);
    target.draw(_text);
    if(_affCursor&&_active)
    target.draw(textCursor);
}

void InputText::setPosition(sf::Vector2f pos){
    _pos = pos;
    updateGraphic();
}

void InputText::setSize(sf::Vector2f taille){
    _size = taille;
    updateGraphic();
}

String InputText::getValue(){
    return _val;
}

