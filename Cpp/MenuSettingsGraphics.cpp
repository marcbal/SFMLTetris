#include "MenuSettingsGraphics.hpp"

MenuSettingsGraphics::MenuSettingsGraphics(sf::Vector2i * window_size,char * state,GameConfiguration * gameConfig, sf::RenderWindow * window):
    Menu(window_size, state),
    _antialias(sf::Vector2f(50, 250), sf::Vector2f(405, 30), gameConfig->getAntialiasing(), 0, 32),
    textAntialias(),
    _FPS(sf::Vector2f(505, 250), sf::Vector2f(405, 30), gameConfig->getFPS(), 5, 120),
    textFPS()
{
    _gameConfig = gameConfig;
    _window = window;
    appliquer = 0;
    titre.setString(L"Paramètres graphiques");


    menuElements.push_back(Bouton(sf::Vector2f(505, _window_size->y-70), sf::Vector2f(177, 30), 18, _state));
    menuElements[0].setAction(SETTINGS);
    menuElements[0].setText(L"Retour");

    menuElements.push_back(Bouton(sf::Vector2f(278, _window_size->y-70), sf::Vector2f(177, 30), 18, _state));
    menuElements[1].setAction(INDEX);
    menuElements[1].setText(L"Menu Principal");

    menuElements.push_back(Bouton(sf::Vector2f(278, _window_size->y-110), sf::Vector2f(404, 30), 18, &appliquer));
    menuElements[2].setAction(1);
    menuElements[2].setText(L"Appliquer");

    textAntialias.setCharacterSize(20);
    textAntialias.setColor(sf::Color::White);
    textAntialias.setFont(*Ressources::getDefaultFont());
    textAntialias.setPosition(50, 210);

    textFPS.setCharacterSize(20);
    textFPS.setColor(sf::Color::White);
    textFPS.setFont(*Ressources::getDefaultFont());
    textFPS.setPosition(505, 210);
}

MenuSettingsGraphics::~MenuSettingsGraphics()
{
    //dtor
}



void MenuSettingsGraphics::onEvent(sf::Event & event)
{
    Menu::onEvent(event);
    _antialias.onEvent(event);
    _FPS.onEvent(event);
    _gameConfig->setFPS((unsigned int) _FPS.getValue());
    _gameConfig->setAntialiasing((unsigned int) _antialias.getValue());
}

void MenuSettingsGraphics::update()
{
    Menu::update();
    if (appliquer == 1)
    {
        _gameConfig->applyGraphicsSettings(*_window, *_window_size);
        appliquer = 0;
    }
    textFPS.setString("Images par seconde : "+to_string((int)_gameConfig->getFPS()));
    textAntialias.setString("Antialiasing : "+to_string((int)_gameConfig->getAntialiasing()));
}




void MenuSettingsGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Menu::draw(target, states);
    target.draw(_antialias, states);
    target.draw(textAntialias, states);
    target.draw(_FPS, states);
    target.draw(textFPS, states);
}



