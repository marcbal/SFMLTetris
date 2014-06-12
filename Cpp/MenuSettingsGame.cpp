#include "MenuSettingsGame.hpp"

using namespace std;
using namespace sf;


MenuSettingsGame::MenuSettingsGame(sf::Vector2i * window_size,char *state,OpenGL_Manager * oGL, GameConfiguration* gameConfig):
    Menu(window_size,state),
    _activateGhost(Vector2f(50,140), Vector2f(20,20),gameConfig->getDrawGhost()),
    textActivateGhost(),
    _activateAutorotation(Vector2f(50,180), Vector2f(20,20),gameConfig->get3DAutorotation()),
    textActivateAutorotation(),
    _onlineScore(Vector2f(50,220), Vector2f(20,20),gameConfig->getOnlineScore()),
    textOnlineScore(),
    _enterPseudo(Vector2f(50,260),Vector2f(405,30),gameConfig->getNickName()),
    _gameMode(Vector2f(505, 115), Vector2f(405, 40), 8, {"Mode normal", "Mode Dark Tetris", "Mode Rythms in matrix"}, gameConfig->getGameMode())
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



    textActivateGhost.setCharacterSize(16);
    textActivateGhost.setColor(sf::Color::White);
    textActivateGhost.setFont(*Ressources::getDefaultFont());
    textActivateGhost.setPosition(85, 140);
    textActivateGhost.setString(L"Afficher le fantôme du tetromino");




    textActivateAutorotation.setCharacterSize(16);
    textActivateAutorotation.setColor(sf::Color::White);
    textActivateAutorotation.setFont(*Ressources::getDefaultFont());
    textActivateAutorotation.setPosition(85, 180);
    textActivateAutorotation.setString("Rotation automatique de la matrice 3D");


    textOnlineScore.setCharacterSize(16);
    textOnlineScore.setColor(sf::Color::White);
    textOnlineScore.setFont(*Ressources::getDefaultFont());
    textOnlineScore.setPosition(85, 220);
    textOnlineScore.setString("Publier le score en ligne");
}


void MenuSettingsGame::update(){
    _enterPseudo.update();
}

void MenuSettingsGame::onEvent(Event & event){
    _activateAutorotation.onEvent(event);
    _activateGhost.onEvent(event);
    _onlineScore.onEvent(event);
    _enterPseudo.onEvent(event);
    _gameMode.onEvent(event);
    Menu::onEvent(event);

    _gameConfig->setDrawGhost(_activateGhost.getValue());
    _gameConfig->set3DAutorotation(_activateAutorotation.getValue());
    _gameConfig->setOnlineScore(_onlineScore.getValue());
    _gameConfig->setNickName(_enterPseudo.getValue());
    _gameConfig->setGameMode(_gameMode.getValueSelected());
}

void MenuSettingsGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Menu::draw(target,states);
    target.draw(_enterPseudo,states);
    target.draw(textActivateAutorotation,states);
    target.draw(_activateAutorotation,states);
    target.draw(textActivateGhost,states);
    target.draw(_activateGhost,states);
    target.draw(_onlineScore,states);
    target.draw(textOnlineScore,states);
    target.draw(_gameMode, states);
}

