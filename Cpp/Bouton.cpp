#include "Bouton.hpp"

Bouton::Bouton(sf::Vector2f pos, sf::Vector2f taille) :
    _mouseHover(false),
    _mouseClick(false),
    shapeDefault(taille),
    shapeHover(taille),
    shapeClick(taille),
    texte()

{
    setPosition(pos);

    setText("default");
    update();
}

Bouton::~Bouton() {}



void Bouton::setPosition(sf::Vector2f pos)
{
    shapeClick.setPosition(pos);
    shapeDefault.setPosition(pos);
    shapeHover.setPosition(pos);
    update();
}
void Bouton::setSize(sf::Vector2f taille)
{
    shapeClick.setSize(taille);
    shapeDefault.setSize(taille);
    shapeHover.setSize(taille);
    update();
}
void Bouton::setText(sf::String str)
{
    texteString = str;
    texte.setString(texteString);
    update();
}





void Bouton::update()
{
    // placement du texte;
    sf::Vector2f bouton_size = shapeDefault.getSize();
    sf::Vector2f bouton_pos = shapeDefault.getPosition();
    texte.setPosition(0, 0);
    texte.setOrigin(texte.getGlobalBounds().left + texte.getGlobalBounds().width/2.0,
                    texte.getGlobalBounds().top + texte.getGlobalBounds().height/2.0);
    texte.setPosition(bouton_pos.x+bouton_size.x/2.0,
                      bouton_pos.y+bouton_size.y/2.0);

}






void Bouton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(
                ((_mouseClick) ? shapeClick : ((_mouseHover) ? shapeHover : shapeDefault)),
                states);
    target.draw(texte);
}

