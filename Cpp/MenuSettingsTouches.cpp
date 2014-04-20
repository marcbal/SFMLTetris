#include "MenuSettingsTouches.hpp"

using namespace std;
using namespace sf;
MenuSettingsTouches::MenuSettingsTouches(sf::Vector2i * window_size,char * state,Evenement * evenement) :Menu(window_size,state)
{
    // création des éléments de menu
    _evenement = evenement;
    _inputKey.push_back(InputKey(Vector2f(400,100),Vector2f(400,40),"Gauche",_evenement));
    _inputKey.push_back(InputKey(Vector2f(400,150),Vector2f(400,40),"Droite",_evenement));
    _inputKey.push_back(InputKey(Vector2f(400,200),Vector2f(400,40),"Rotation Gauche",_evenement));
    _inputKey.push_back(InputKey(Vector2f(400,250),Vector2f(400,40),"Rotation Droite",_evenement));
    _inputKey.push_back(InputKey(Vector2f(400,300),Vector2f(400,40),"Descente Rapide",_evenement));
    _inputKey.push_back(InputKey(Vector2f(400,350),Vector2f(400,40),"Descente Instantanee",_evenement));
    _inputKey.push_back(InputKey(Vector2f(400,400),Vector2f(400,40),"Pause",_evenement));

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

}

void MenuSettingsTouches::onEvent(Event & event){
    int nbButton = _inputKey.size();
    for(int i=0;i<nbButton;++i)
        _inputKey[i].onEvent(event);

    Menu::onEvent(event);

}


void MenuSettingsTouches::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Menu::draw(target,states);
    int nbButton = _inputKey.size();
    for(int i=0;i<nbButton;++i)
        target.draw(_inputKey[i],states);
}
