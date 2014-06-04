#include "MenuIndex.hpp"

using namespace std;
using namespace sf;

MenuIndex::MenuIndex(sf::Vector2i * window_size,char * state) :
    Menu(window_size,state),
    lien(sf::Text(), "http://sfmltetris.no-ip.org/")
{

    // tecture et sprite sont pour l'image du jeu
    texture.loadFromImage(*Ressources::getLogo(),sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)Ressources::getLogo()->getSize()));
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(110, 60));
    sprite.setScale(1.0/5,1.0/5);

    titre.setString("SFML Tetris");
    titre.setCharacterSize(70);
    titre.setPosition(360, 120);
    titre.setStyle(sf::Text::Bold);


    // création des éléments de menu

    menuElements.push_back(Bouton(sf::Vector2f(50, 330), sf::Vector2f(405, 40),25,_state));
    menuElements[0].setAction(GAME);
    menuElements[0].setText(L"Jouer");
    menuElements.push_back(Bouton(sf::Vector2f(50, 390), sf::Vector2f(405, 40),25,_state));
    menuElements[1].setAction(SCORE);
    menuElements[1].setText(L"Scores");
    menuElements.push_back(Bouton(sf::Vector2f(505, 330), sf::Vector2f(405, 40),25,_state));
    menuElements[2].setAction(SETTINGS);
    menuElements[2].setText(L"Paramètres");
    menuElements.push_back(Bouton(sf::Vector2f(505, 390), sf::Vector2f(405, 40),25,_state));
    menuElements[3].setAction(CLOSE);
    menuElements[3].setText(L"Quitter");


    lien.getText().setCharacterSize(30);
    lien.getText().setFont(*Ressources::getDefaultFont());
    lien.getText().setPosition(364, 460);
    lien.getText().setString("Site internet");
}


void MenuIndex::onEvent(sf::Event & event)
{
    Menu::onEvent(event);
    lien.onEvent(event);
}



void MenuIndex::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Menu::draw(target, states);
    target.draw(sprite, states);
    target.draw(lien, states);
    for (unsigned int i=0; i<menuElements.size(); i++)
    {
        target.draw(menuElements[i], states);
    }
}
