#include "MenuSettingsGraphic.hpp"

using namespace std;
using namespace sf;
MenuSettingsGraphic::MenuSettingsGraphic(sf::Vector2i * window_size,char *state,OpenGL_Manager * oGL, GameConfiguration* gameConfig):
    Menu(window_size,state),
    _activateExplosions(Vector2f(_window_size->x/2-250,80), Vector2f(20,20),gameConfig->getDrawExplosions()),
    textActivateExplosions(),
    _activateGhost(Vector2f(_window_size->x/2-250,120), Vector2f(20,20),gameConfig->getDrawGhost()),
    textActivateGhost(),
    _activate3D(Vector2f(_window_size->x/2-250,160), Vector2f(20,20),gameConfig->get3DMode()),
    textActivate3D(),
    _activateAutorotation(Vector2f(_window_size->x/2-250,200), Vector2f(20,20),gameConfig->get3DAutorotation()),
    _inclinaison(Vector2f(_window_size->x/2-250,290),Vector2f(500,24),gameConfig->get3DInclinaison(),0,360),
    textInclinaison()
{
    _gameConfig = gameConfig;
    _oGL = oGL;

    menuElements.push_back(Bouton(sf::Vector2f(50, _window_size->y-120),
                                        sf::Vector2f(200, 30),
                                        18,
                                        _state));

    menuElements[0].setAction(SETTINGS);
    menuElements[0].setText("Retour");

    menuElements.push_back(Bouton(sf::Vector2f(50, _window_size->y-80),
                                        sf::Vector2f(200, 30),
                                        18,
                                        _state));

    menuElements[1].setAction(INDEX);
    menuElements[1].setText("Menu Principal");

    textActivateExplosions.setCharacterSize(20);
    textActivateExplosions.setColor(sf::Color::White);
    textActivateExplosions.setFont(*Ressources::getDefaultFont());
    textActivateExplosions.setPosition(_window_size->x/2-210, 80);
    textActivateExplosions.setString("Effets d'explosion");

    textActivateGhost.setCharacterSize(20);
    textActivateGhost.setColor(sf::Color::White);
    textActivateGhost.setFont(*Ressources::getDefaultFont());
    textActivateGhost.setPosition(_window_size->x/2-210, 120);
    textActivateGhost.setString(L"Afficher le fantôme du tetromino");


    textActivate3D.setCharacterSize(20);
    textActivate3D.setColor(sf::Color::White);
    textActivate3D.setFont(*Ressources::getDefaultFont());
    textActivate3D.setPosition(_window_size->x/2-210, 160);
    textActivate3D.setString("Activer la 3D");


    textActivateAutorotation.setCharacterSize(20);
    textActivateAutorotation.setColor(sf::Color::White);
    textActivateAutorotation.setFont(*Ressources::getDefaultFont());
    textActivateAutorotation.setPosition(_window_size->x/2-210, 200);
    textActivateAutorotation.setString("Rotation automatique de la matrice 3D");

    textInclinaison.setCharacterSize(20);
    textInclinaison.setColor(sf::Color::White);
    textInclinaison.setFont(*Ressources::getDefaultFont());
    textInclinaison.setPosition(_window_size->x/2-250, 250);
    textInclinaison.setString("Inclinaison de la matrice 3D :");
}




void MenuSettingsGraphic::onEvent(Event & event){
    _activate3D.onEvent(event);
    _inclinaison.onEvent(event);
    _activateAutorotation.onEvent(event);
    _activateExplosions.onEvent(event);
    _activateGhost.onEvent(event);
    Menu::onEvent(event);

    _gameConfig->setDrawExplosions(_activateExplosions.getValue());
    _gameConfig->setDrawGhost(_activateGhost.getValue());

    _gameConfig->set3DInclinaison(_inclinaison.getValue());

    _gameConfig->set3DAutorotation(_activateAutorotation.getValue());
    /* _oGL->...(_activateAutorotation.getValue()) */

    _gameConfig->set3DMode(_activate3D.getValue());
}

void MenuSettingsGraphic::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Menu::draw(target,states);
    target.draw(_activate3D,states);
    target.draw(textActivate3D,states);
    target.draw(_inclinaison,states);
    target.draw(textInclinaison,states);
    target.draw(textActivateAutorotation,states);
    target.draw(_activateAutorotation,states);
    target.draw(textActivateExplosions,states);
    target.draw(_activateExplosions,states);
    target.draw(textActivateGhost,states);
    target.draw(_activateGhost,states);
}

