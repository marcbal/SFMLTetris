#include "MenuSettingsGame.hpp"

using namespace std;
using namespace sf;
MenuSettingsGame::MenuSettingsGame(sf::Vector2i * window_size,char *state,OpenGL_Manager * oGL, GameConfiguration* gameConfig):
    Menu(window_size,state),
    _activateExplosions(Vector2f(50,160), Vector2f(20,20),gameConfig->getDrawExplosions()),
    textActivateExplosions(),
    _activateGhost(Vector2f(50,200), Vector2f(20,20),gameConfig->getDrawGhost()),
    textActivateGhost(),
    _activate3D(Vector2f(50,240), Vector2f(20,20),gameConfig->get3DMode()),
    textActivate3D(),
    _activateAutorotation(Vector2f(50,280), Vector2f(20,20),gameConfig->get3DAutorotation()),
    textActivateAutorotation(),
    _onlineScore(Vector2f(505,200), Vector2f(20,20),gameConfig->getOnlineScore()),
    textOnlineScore(),
    _enterPseudo(Vector2f(505,240),Vector2f(405,30),gameConfig->getNickName())
{
    _gameConfig = gameConfig;
    _oGL = oGL;


    titre.setString(L"Paramètres de jeu");


    menuElements.push_back(Bouton(sf::Vector2f(505, _window_size->y-70), sf::Vector2f(177, 30), 18, _state));
    menuElements[0].setAction(SETTINGS);
    menuElements[0].setText(L"Retour");

    menuElements.push_back(Bouton(sf::Vector2f(278, _window_size->y-70), sf::Vector2f(177, 30), 18, _state));
    menuElements[1].setAction(INDEX);
    menuElements[1].setText(L"Menu Principal");



    textActivateExplosions.setCharacterSize(16);
    textActivateExplosions.setColor(sf::Color::White);
    textActivateExplosions.setFont(*Ressources::getDefaultFont());
    textActivateExplosions.setPosition(85, 160);
    textActivateExplosions.setString("Effets d'explosion (mode 2D seulement)");

    textActivateGhost.setCharacterSize(16);
    textActivateGhost.setColor(sf::Color::White);
    textActivateGhost.setFont(*Ressources::getDefaultFont());
    textActivateGhost.setPosition(85, 200);
    textActivateGhost.setString(L"Afficher le fantôme du tetromino");


    textActivate3D.setCharacterSize(16);
    textActivate3D.setColor(sf::Color::White);
    textActivate3D.setFont(*Ressources::getDefaultFont());
    textActivate3D.setPosition(85, 240);
    textActivate3D.setString("Activer la matrice 3D");


    textActivateAutorotation.setCharacterSize(16);
    textActivateAutorotation.setColor(sf::Color::White);
    textActivateAutorotation.setFont(*Ressources::getDefaultFont());
    textActivateAutorotation.setPosition(85, 280);
    textActivateAutorotation.setString("Rotation automatique de la matrice 3D");


    textOnlineScore.setCharacterSize(16);
    textOnlineScore.setColor(sf::Color::White);
    textOnlineScore.setFont(*Ressources::getDefaultFont());
    textOnlineScore.setPosition(540, 200);
    textOnlineScore.setString("Publier le score en ligne");
}


void MenuSettingsGame::update(){
    _enterPseudo.update();
}

void MenuSettingsGame::onEvent(Event & event){
    _activate3D.onEvent(event);
    _activateAutorotation.onEvent(event);
    _activateExplosions.onEvent(event);
    _activateGhost.onEvent(event);
    _onlineScore.onEvent(event);
    _enterPseudo.onEvent(event);
    Menu::onEvent(event);

    _gameConfig->setDrawExplosions(_activateExplosions.getValue());
    _gameConfig->setDrawGhost(_activateGhost.getValue());
    _gameConfig->set3DAutorotation(_activateAutorotation.getValue());
    _gameConfig->set3DMode(_activate3D.getValue());
    _gameConfig->setOnlineScore(_onlineScore.getValue());
    _gameConfig->setNickName(_enterPseudo.getValue());
}

void MenuSettingsGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Menu::draw(target,states);
    target.draw(_activate3D,states);
    target.draw(_enterPseudo,states);
    target.draw(textActivate3D,states);
    target.draw(textActivateAutorotation,states);
    target.draw(_activateAutorotation,states);
    target.draw(textActivateExplosions,states);
    target.draw(_activateExplosions,states);
    target.draw(textActivateGhost,states);
    target.draw(_activateGhost,states);
    target.draw(_onlineScore,states);
    target.draw(textOnlineScore,states);
}

