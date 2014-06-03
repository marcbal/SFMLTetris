#include "MenuSettingsTouches.hpp"

using namespace std;
using namespace sf;
MenuSettingsTouches::MenuSettingsTouches(sf::Vector2i * window_size,char * state,Evenement * evenement, GameConfiguration * gameConfig) :
    Menu(window_size,state),
    _checkMouse(Vector2f(80,78), Vector2f(20,20),gameConfig->getUseMouse()),
    _textMouse()
{
    // création des éléments de menu

    titre.setString("Clavier et souris");

    _evenement = evenement;
    _gameConfig = gameConfig;
    _inputKey.push_back(InputKey(Vector2f(50,265),Vector2f(405,35),"Ecran Debug",_evenement));
    _inputKey.push_back(InputKey(Vector2f(50,310),Vector2f(405,35),"Activation IA",_evenement));
    _inputKey.push_back(InputKey(Vector2f(50,355),Vector2f(405,35),"IA P. Dellacherie",_evenement));
    _inputKey.push_back(InputKey(Vector2f(50,400),Vector2f(405,35),"IA fait maison",_evenement));


    _inputKey.push_back(InputKey(Vector2f(505,40),Vector2f(405,35),"Gauche",_evenement));
    _inputKey.push_back(InputKey(Vector2f(505,85),Vector2f(405,35),"Droite",_evenement));
    _inputKey.push_back(InputKey(Vector2f(505,130),Vector2f(405,35),"Rotation Gauche",_evenement));
    _inputKey.push_back(InputKey(Vector2f(505,175),Vector2f(405,35),"Rotation Droite",_evenement));
    _inputKey.push_back(InputKey(Vector2f(505,220),Vector2f(405,35),"Descente Rapide",_evenement));
    _inputKey.push_back(InputKey(Vector2f(505,265),Vector2f(405,35),"Descente Instantanee",_evenement));
    _inputKey.push_back(InputKey(Vector2f(505,310),Vector2f(405,35),"Recommencer",_evenement));
    _inputKey.push_back(InputKey(Vector2f(505,355),Vector2f(405,35),"Pause",_evenement));
    _inputKey.push_back(InputKey(Vector2f(505,400),Vector2f(405,35),"Hold Piece",_evenement));


    menuElements.push_back(Bouton(sf::Vector2f(505, _window_size->y-70), sf::Vector2f(177, 30), 18, _state));
    menuElements[0].setAction(SETTINGS);
    menuElements[0].setText(L"Retour");

    menuElements.push_back(Bouton(sf::Vector2f(278, _window_size->y-70), sf::Vector2f(177, 30), 18, _state));
    menuElements[1].setAction(INDEX);
    menuElements[1].setText(L"Menu Principal");



    _textMouse.setCharacterSize(18);
    _textMouse.setColor(sf::Color::White);
    _textMouse.setFont(*Ressources::getDefaultFont());
    _textMouse.setPosition(115, 75);
    _textMouse.setString(L"Utiliser la souris (Mode 2D)\nClique gauche :\n     rotation gauche\nClique droite :\n     rotation droite\nClique du milieu :\n     descente rapide\nMouvement souris :\n     Déplacer tétromino");

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
    for(unsigned int i=0;i<_inputKey.size();++i)
        target.draw(_inputKey[i],states);
    target.draw(_checkMouse, states);
    target.draw(_textMouse, states);
}
