#include "MenuSettingsGraphics.hpp"

MenuSettingsGraphics::MenuSettingsGraphics(sf::Vector2i * window_size,char * state,GameConfiguration * gameConfig):
    Menu(window_size, state)
{

    titre.setString(L"Paramètres graphiques");


    menuElements.push_back(Bouton(sf::Vector2f(505, _window_size->y-70), sf::Vector2f(177, 30), 18, _state));
    menuElements[0].setAction(SETTINGS);
    menuElements[0].setText(L"Retour");

    menuElements.push_back(Bouton(sf::Vector2f(278, _window_size->y-70), sf::Vector2f(177, 30), 18, _state));
    menuElements[1].setAction(INDEX);
    menuElements[1].setText(L"Menu Principal");


}

MenuSettingsGraphics::~MenuSettingsGraphics()
{
    //dtor
}



void MenuSettingsGraphics::onEvent(sf::Event & event)
{
    Menu::onEvent(event);
}

void MenuSettingsGraphics::update()
{
    Menu::update();
}


void MenuSettingsGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Menu::draw(target, states);
}



