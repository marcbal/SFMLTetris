#include "Bouton.hpp"

Bouton::Bouton(sf::Vector2f pos, sf::Vector2f taille) :
    shapeDefault(taille),
    shapeClick(taille),
    shapeHover(taille),
    texte(),
    texteString("default"),
    _mouseHover(false),
    _mouseClick(false)
{
    shapeClick.setPosition(pos);
    shapeDefault.setPosition(pos);
    shapeHover.setPosition(pos);

    texte.setCharacterSize(15);
    texte.setString(texteString);
}

Bouton::~Bouton() {}



void Bouton::setPosition(sf::Vector2f pos)
{
    shapeClick.setPosition(pos);
    shapeDefault.setPosition(pos);
    shapeHover.setPosition(pos);
}
void Bouton::setSize(sf::Vector2f taille)
{
    shapeClick.setSize(taille);
    shapeDefault.setSize(taille);
    shapeHover.setSize(taille);
}
void Bouton::setText(sf::String str)
{
    texteString = str;
}





void Bouton::update()
{
    // placement du texte;
    sf::Vector2f bouton_size = shapeDefault.getSize();
    sf::Vector2f bouton_pos = shapeDefault.getPosition();
    texte.setPosition(bouton_pos.x+(bouton_size.x-texte.getGlobalBounds().width)/2.0,
                      bouton_pos.y+(bouton_size.y-texte.getGlobalBounds().height)/2.0);

}






void Bouton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(
                ((_mouseClick) ? shapeClick : ((_mouseHover) ? shapeHover : shapeDefault)),
                states);
    target.draw(texte);
}

