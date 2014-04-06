#include "MenuIndex.hpp"

using namespace std;
using namespace sf;

MenuIndex::MenuIndex(sf::Vector2i window_size,char * state) :Menu(window_size,state)
{

    // tecture et sprite sont pour l'image du jeu
    texture.loadFromFile("res/Crystal_Clear_app_ksirtet.png");
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(75, 100));
    sprite.setScale(1.0/3,1.0/3);


    // création des éléments de menu

    int nbElement = 4;

    for (int i=0; i<nbElement; i++)
    {
        menuElements.push_back(*(new Bouton(sf::Vector2f(560, (_window_size.y-nbElement*50)/2+50*i), sf::Vector2f(300, 40),_state)));
        menuElements[i].texte.setCharacterSize(25);
    }
    menuElements[0].setAction(Game);
    menuElements[1].setAction(Rules);
    menuElements[2].setAction(Settings);
    menuElements[3].setAction(Close);

    menuElements[0].setText(L"Jouer");
    menuElements[1].setText(L"Règles");
    menuElements[2].setText(L"Paramètres");
    menuElements[3].setText(L"Quitter");
}



void MenuIndex::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    for (unsigned int i=0; i<menuElements.size(); i++)
    {
        target.draw(menuElements[i], states);
    }
}
