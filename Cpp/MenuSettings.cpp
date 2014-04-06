#include "MenuSettings.hpp"

using namespace std;
using namespace sf;
MenuSettings::MenuSettings(sf::Vector2i window_size,char * state) :Menu(window_size,state)
{
    // création des éléments de menu

    int nbElement = 1;

    for (int i=0; i<nbElement; i++)
    {
        menuElements.push_back(*(new Bouton(sf::Vector2f(_window_size.x/2 - 250, (_window_size.y-nbElement*50)/2+50*i), sf::Vector2f(500, 40),_state)));
        menuElements[i].texte.setCharacterSize(25);
    }
    menuElements[0].setAction(Index);
    menuElements[0].setText(L"Retour");
}
