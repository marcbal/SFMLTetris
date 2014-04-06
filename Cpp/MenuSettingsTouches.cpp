#include "MenuSettingsTouches.hpp"

using namespace std;
using namespace sf;
MenuSettingsTouches::MenuSettingsTouches(sf::Vector2i window_size,char * state) :Menu(window_size,state)
{
    // création des éléments de menu

    menuElements.push_back(*(new Bouton(sf::Vector2f(50, _window_size.y-120),
                                        sf::Vector2f(200, 30),
                                        18,
                                        _state)));

    menuElements[0].setAction(Settings);
    menuElements[0].setText(L"Retour");

    menuElements.push_back(*(new Bouton(sf::Vector2f(50, _window_size.y-80),
                                        sf::Vector2f(200, 30),
                                        18,
                                        _state)));

    menuElements[1].setAction(Index);
    menuElements[1].setText(L"Menu Principal");
}

