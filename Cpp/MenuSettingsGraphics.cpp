#include "MenuSettingsGraphics.hpp"

MenuSettingsGraphics::MenuSettingsGraphics(sf::Vector2i * window_size,char * state,GameConfiguration * gameConfig, sf::RenderWindow * window):
    Menu(window_size, state),
    _antialias(sf::Vector2f(50, 160), sf::Vector2f(405, 30), gameConfig->getAntialiasing(), 0, 16),
    textAntialias(),
    _FPS(sf::Vector2f(50, 240), sf::Vector2f(405, 30), gameConfig->getFPS(), 5, 120),
    textFPS(),
    _BGPart(sf::Vector2f(505, 120), sf::Vector2f(405, 30), gameConfig->getBGParticules(), 0, 1000),
    textBGPart(),
    _BGSpeed(sf::Vector2f(505, 200), sf::Vector2f(405, 30), gameConfig->getBGSpeed(), -100, 100),
    textBGSpeed(),
    _BGPSize(sf::Vector2f(505, 280), sf::Vector2f(405, 30), gameConfig->getBGPartSize(), 0, 100),
    textBGPSize(),
    _activateExplosions(Vector2f(50,400), Vector2f(20,20),gameConfig->getDrawExplosions()),
    textActivateExplosions(),
    _activate3D(Vector2f(505,400), Vector2f(20,20),gameConfig->get3DMode()),
    textActivate3D()
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

    menuElements.push_back(Bouton(sf::Vector2f(50, 300), sf::Vector2f(405, 30), 18, &appliquer));
    menuElements[2].setAction(1);
    menuElements[2].setText(L"Appliquer");

    textAntialias.setCharacterSize(20);
    textAntialias.setColor(sf::Color::White);
    textAntialias.setFont(*Ressources::getDefaultFont());
    textAntialias.setPosition(50, 120);

    textFPS.setCharacterSize(20);
    textFPS.setColor(sf::Color::White);
    textFPS.setFont(*Ressources::getDefaultFont());
    textFPS.setPosition(50, 200);

    textBGPart.setCharacterSize(20);
    textBGPart.setColor(sf::Color::White);
    textBGPart.setFont(*Ressources::getDefaultFont());
    textBGPart.setPosition(505, 80);

    textBGSpeed.setCharacterSize(20);
    textBGSpeed.setColor(sf::Color::White);
    textBGSpeed.setFont(*Ressources::getDefaultFont());
    textBGSpeed.setPosition(505, 160);

    textBGPSize.setCharacterSize(20);
    textBGPSize.setColor(sf::Color::White);
    textBGPSize.setFont(*Ressources::getDefaultFont());
    textBGPSize.setPosition(505, 240);





    textActivateExplosions.setCharacterSize(16);
    textActivateExplosions.setColor(sf::Color::White);
    textActivateExplosions.setFont(*Ressources::getDefaultFont());
    textActivateExplosions.setPosition(85, 400);
    textActivateExplosions.setString("Effets d'explosion (mode 2D seulement)");


    textActivate3D.setCharacterSize(16);
    textActivate3D.setColor(sf::Color::White);
    textActivate3D.setFont(*Ressources::getDefaultFont());
    textActivate3D.setPosition(540, 400);
    textActivate3D.setString("Activer la matrice 3D");
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
    _BGPart.onEvent(event);
    _BGSpeed.onEvent(event);
    _BGPSize.onEvent(event);
    _activate3D.onEvent(event);
    _activateExplosions.onEvent(event);
    _gameConfig->setDrawExplosions(_activateExplosions.getValue());
    _gameConfig->set3DMode(_activate3D.getValue());
    _gameConfig->setFPS((unsigned int) _FPS.getValue());
    _gameConfig->setAntialiasing((unsigned int) _antialias.getValue());
    _gameConfig->setBGParticules((unsigned int) _BGPart.getValue());
    _gameConfig->setBGSpeed((int)_BGSpeed.getValue());
    _gameConfig->setBGPartSize(_BGPSize.getValue());
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
    textBGPart.setString(L"Nombre de particules : "+to_string((int)_gameConfig->getBGParticules()));
    textBGSpeed.setString(L"Vitesse des particules : "+to_string((int)_gameConfig->getBGSpeed()));
    textBGPSize.setString(L"Taille des particules : "+to_string((int)_gameConfig->getBGPartSize()));
}




void MenuSettingsGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Menu::draw(target, states);
    target.draw(_antialias, states);
    target.draw(textAntialias, states);
    target.draw(_FPS, states);
    target.draw(textFPS, states);
    target.draw(_BGPart, states);
    target.draw(textBGPart, states);
    target.draw(_BGSpeed, states);
    target.draw(textBGSpeed, states);
    target.draw(_BGPSize, states);
    target.draw(textBGPSize, states);
    target.draw(_activate3D,states);
    target.draw(textActivate3D,states);
    target.draw(textActivateExplosions,states);
    target.draw(_activateExplosions,states);
}



