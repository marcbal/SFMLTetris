#include "MenuSettings.hpp"

using namespace std;
using namespace sf;
MenuSettings::MenuSettings(sf::Vector2i * window_size,char * state) :Menu(window_size,state)
{
    // création des éléments de menu

    titre.setString(L"Paramètres");

    int nbElement = 4;

    for (int i=0; i<nbElement; i++)
    {
        menuElements.push_back(Bouton(sf::Vector2f(_window_size->x/2 - 250,
                                                         (_window_size->y-nbElement*50)/2+50*i),
                                            sf::Vector2f(500, 40),25,_state));
    }
    menuElements[0].setAction(SETTINGSTOUCHES);
    menuElements[0].setText(L"Clavier et souris");
    menuElements[1].setAction(SETTINGSAUDIO);
    menuElements[1].setText(L"Musiques");
    menuElements[2].setAction(SETTINGSGRAPHIC);
    menuElements[2].setText(L"Paramètres de jeu");
    menuElements[3].setAction(INDEX);
    menuElements[3].setText(L"Retour");
}
