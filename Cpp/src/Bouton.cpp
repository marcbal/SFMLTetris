#include "Bouton.hpp"

Bouton::Bouton(sf::Vector2f pos, sf::Vector2f taille,int taillePolice,char * state,char action) :
    _mouseHover(false),
    _mouseClick(false),
    _position(pos.x, pos.y),
    _size(taille.x, taille.y),
    texte(),
    shapeDefault(taille),
    shapeHover(taille),
    shapeClick(taille)
{
    _action = action;
    _state = state;
    texte.setCharacterSize(taillePolice);

    setPosition(pos);

    setText("-");


    // format du texte
    texte.setFillColor(sf::Color::White);


    texte.setFont(*Ressources::getDefaultFont());




    // forme par défaut
    shapeDefault.setOutlineColor(sf::Color::White);
    shapeDefault.setOutlineThickness(-2);
    shapeDefault.setFillColor(sf::Color(0, 0, 0, 192));
    // forme en survol
    shapeHover.setOutlineColor(sf::Color::White);
    shapeHover.setOutlineThickness(-2);
    shapeHover.setFillColor(sf::Color(128, 128, 128));
    // forme au clic
    shapeClick.setOutlineColor(sf::Color::White);
    shapeClick.setOutlineThickness(-2);
    shapeClick.setFillColor(sf::Color(160, 160, 160));
}

Bouton::Bouton(sf::Vector2f pos, sf::Vector2f taille,int taillePolice,char * state):
    Bouton(pos,taille,taillePolice,state,0)
{}
Bouton::Bouton():
    Bouton(sf::Vector2f(0, 0),sf::Vector2f(0, 0),20,nullptr,0)
{}

Bouton::~Bouton() {}

void Bouton::setAction(char action){
    _action = action;
}

void Bouton::setPosition(sf::Vector2f pos)
{
    shapeClick.setPosition(pos);
    shapeDefault.setPosition(pos);
    shapeHover.setPosition(pos);
    _position = pos;
    updateTextPosition();
}
void Bouton::setSize(sf::Vector2f taille)
{
    shapeClick.setSize(taille);
    shapeDefault.setSize(taille);
    shapeHover.setSize(taille);
    _size = taille;
    updateTextPosition();
}
void Bouton::setText(sf::String str)
{
    texteString = str;
    texte.setString(texteString);
    updateTextPosition();
}




void Bouton::updateTextPosition()
{
    texte.setOrigin(0, 0);
    texte.setPosition(0, 0);
    texte.setOrigin((int) (texte.getGlobalBounds().left + texte.getGlobalBounds().width/2.0),
                    (int) (texte.getGlobalBounds().top + texte.getGlobalBounds().height/2.0));
    texte.setPosition((int)(_position.x+_size.x/2.0),
                      (int)(_position.y+_size.y/2.0));
}








void Bouton::onMouseMove(sf::Event & event)
{
    if (event.type != Event::MouseMoved)
        return;
    _mouseHover = pointInRect(_position,_size,Vector2f(event.mouseMove.x,event.mouseMove.y));
}




void Bouton::onMouseDown(sf::Event & event)
{

    if (event.type != Event::MouseButtonPressed
        || event.mouseButton.button != sf::Mouse::Left)
        return;
    _mouseHover = pointInRect(_position,_size,Vector2f(event.mouseButton.x,event.mouseButton.y));

    _mouseClick = _mouseHover;
}



void Bouton::onMouseUp(sf::Event & event)
{

    if (event.type != Event::MouseButtonReleased
        || event.mouseButton.button != sf::Mouse::Left)
        return;
    if (_mouseHover && _mouseClick)
        *_state=_action;

    _mouseClick = false;
    //_mouseHover = false;
}







void Bouton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(
                ((_mouseClick&&_mouseHover) ? shapeClick : ((_mouseHover) ? shapeHover : shapeDefault)),
                states);
    target.draw(texte);
}



bool Bouton::isClicked(){return _mouseClick;}
bool Bouton::isHover(){return _mouseHover;}
