#include "MenuSettings.hpp"

using namespace std;
using namespace sf;
MenuSettings::MenuSettings(sf::Vector2i * window_size,char * state) :Menu(window_size,state)
{
    // création des éléments de menu

    titre.setString(L"Paramètres");

    menuElements.push_back(Bouton(sf::Vector2f(50, 200), sf::Vector2f(405, 40), 25, _state));
    menuElements[0].setAction(SETTINGSTOUCHES);
    menuElements[0].setText(L"Clavier et souris");
    menuElements.push_back(Bouton(sf::Vector2f(50, 260), sf::Vector2f(405, 40), 25, _state));
    menuElements[1].setAction(SETTINGSAUDIO);
    menuElements[1].setText(L"Paramètres audio");
    menuElements.push_back(Bouton(sf::Vector2f(505, 200), sf::Vector2f(405, 40), 25, _state));
    menuElements[2].setAction(SETTINGSGAME);
    menuElements[2].setText(L"Paramètres de jeu");
    menuElements.push_back(Bouton(sf::Vector2f(505, 260), sf::Vector2f(405, 40), 25, _state));
    menuElements[3].setAction(SETTINGSGRAPHIC);
    menuElements[3].setText(L"Paramètres graphiques");

    menuElements.push_back(Bouton(sf::Vector2f(278, _window_size->y-70), sf::Vector2f(404, 30), 18, _state));
    menuElements[4].setAction(INDEX);
    menuElements[4].setText(L"Retour");
}
