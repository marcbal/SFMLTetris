#include "MenuSettingsTouches.hpp"

using namespace std;
using namespace sf;
MenuSettingsTouches::MenuSettingsTouches(sf::Vector2i * window_size,char * state,Evenement * evenement, GameConfiguration * gameConfig) :
    Menu(window_size,state),
    _checkMouse(Vector2f(40,100), Vector2f(20,20),gameConfig->getUseMouse()),
    _textMouse()
{
    // création des éléments de menu
    _evenement = evenement;
    _gameConfig = gameConfig;
    _inputKey.push_back(InputKey(Vector2f(500,100),Vector2f(400,40),"Gauche",_evenement));
    _inputKey.push_back(InputKey(Vector2f(500,150),Vector2f(400,40),"Droite",_evenement));
    _inputKey.push_back(InputKey(Vector2f(500,200),Vector2f(400,40),"Rotation Gauche",_evenement));
    _inputKey.push_back(InputKey(Vector2f(500,250),Vector2f(400,40),"Rotation Droite",_evenement));
    _inputKey.push_back(InputKey(Vector2f(500,300),Vector2f(400,40),"Descente Rapide",_evenement));
    _inputKey.push_back(InputKey(Vector2f(500,350),Vector2f(400,40),"Descente Instantanee",_evenement));
    _inputKey.push_back(InputKey(Vector2f(500,400),Vector2f(400,40),"Pause",_evenement));

    menuElements.push_back(Bouton(sf::Vector2f(50, _window_size->y-120),
                                        sf::Vector2f(200, 30),
                                        18,
                                        _state));

    menuElements[0].setAction(SETTINGS);
    menuElements[0].setText(L"Retour");

    menuElements.push_back(Bouton(sf::Vector2f(50, _window_size->y-80),
                                        sf::Vector2f(200, 30),
                                        18,
                                        _state));

    menuElements[1].setAction(INDEX);
    menuElements[1].setText(L"Menu Principal");



    _textMouse.setCharacterSize(20);
    _textMouse.setColor(sf::Color::White);
    _textMouse.setFont(*Ressources::getDefaultFont());
    _textMouse.setPosition(80, 100);
    _textMouse.setString(L"Utiliser la souris\nClique gauche :\n     rotation gauche\nClique droite :\n     rotation droite\nClique du milieu :\n     descente rapide\nMouvement souris :\n     Déplacer tétromino");

}

void MenuSettingsTouches::onEvent(Event & event){
    int nbButton = _inputKey.size();
    for(int i=0;i<nbButton;++i)
        _inputKey[i].onEvent(event);

    Menu::onEvent(event);
    _checkMouse.onEvent(event);
    _gameConfig->setUseMouse(_checkMouse.getValue());
}


void MenuSettingsTouches::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Menu::draw(target,states);
    for(int i=0;i<_inputKey.size();++i)
        target.draw(_inputKey[i],states);
    target.draw(_checkMouse, states);
    target.draw(_textMouse, states);
}
