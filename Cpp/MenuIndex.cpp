#include "MenuIndex.hpp"

MenuIndex::MenuIndex(sf::Vector2i window_size) :
    texture(),
    sprite(),
    menuElements()
{
    _window_size = window_size;


    // tecture et sprite sont pour l'image du jeu
    texture.loadFromFile("res/Crystal_Clear_app_ksirtet.png");
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(75, 100));
    sprite.setScale(1.0/3,1.0/3);


    // création des éléments de menu
    menuElements.clear();
    int nbElement = 4;

    sf::Font * menuFont = new sf::Font();
    menuFont->loadFromFile("res/LiberationMono-Regular.ttf");
    for (int i=0; i<nbElement; i++)
    {
        menuElements.push_back(*(new Bouton(sf::Vector2f(560, (_window_size.y-nbElement*50)/2+50*i), sf::Vector2f(300, 40))));


        menuElements[i].texte.setFont(*menuFont);
        menuElements[i].texte.setCharacterSize(25);
        menuElements[i].texte.setColor(sf::Color::White);
        menuElements[i].shapeDefault.setOutlineColor(sf::Color::White);
        menuElements[i].shapeDefault.setOutlineThickness(-2);
        menuElements[i].shapeDefault.setFillColor(sf::Color::Black);
        // ajouter les couleurs et mise en forme pour le survol et le click
    }

    menuElements[0].setText("Jouer");
    menuElements[1].setText("Règles");
    menuElements[2].setText("Paramètres");
    menuElements[3].setText("Quitter");
}

MenuIndex::~MenuIndex() {}


void MenuIndex::update()
{
    for (int i=0; i<menuElements.size(); i++)
    {
        menuElements[i].update();
    }
}


void MenuIndex::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    for (int i=0; i<menuElements.size(); i++)
    {
        target.draw(menuElements[i], states);
    }
}
