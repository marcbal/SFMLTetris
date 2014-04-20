#include "Evenement.hpp"

#include <iostream>

using namespace sf;
using namespace std;



const std::string Evenement::KeyName[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
								 "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
								 "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "echap",
								 "CTRL Gauche", "Shift Gauche", "Alt Gauche", "System Gauche",
								 "CTRL Droit", "Shift Droit", "Alt Droit", "System Droit", "Menu",
								 "[", "]", ";", ",", ".", "'", "/", "\\", "~", "=", "-", "Espace",
								 "Entree", "Retour arrière", "Tabulation", "Page suiv.", "Page prec.",
								 "Fin", "Home", "Insert", "Suppr", "+", "-", "*", "/", "Gauche", "Droite", "Haut",
								 "Bas", "0 Numpad", "1 Numpad", "2 Numpad", "3 Numpad", "4 Numpad", "5 Numpad", "6 Numpad", "7 Numpad", "8 Numpad", "9  Numpad",
								 "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause"};

Evenement::Evenement(){
    addEventConf("Gauche",Keyboard::Left);
    addEventConf("Droite",Keyboard::Right);
    addEventConf("Pause",Keyboard::Escape);
    addEventConf("Descente Rapide",Keyboard::Down);
    addEventConf("Descente Instantanee",Keyboard::Up);
    addEventConf("Rotation Gauche",Keyboard::Q);
    addEventConf("Rotation Droite",Keyboard::D);
}


void Evenement::addEventConf(string str,Keyboard::Key key)
{
    _eventconf[str] = key;    //On crée ou met à jour la touche associée à un événement 'str'. Cette touche sera maintenant 'key'
}

bool Evenement::getEventState(std::string str)
{
    return  _eventconf.find(str)!=_eventconf.end() && sf::Keyboard::isKeyPressed(_eventconf[str]); //Si la touche n'est pas trouvée on renvoit FALSE
}

Keyboard::Key Evenement::getEventKey(string str){
    if(_eventconf.find(str)!=_eventconf.end())
        return _eventconf[str];
    else
        return Keyboard::Key::Unknown;
}

string Evenement::keyToString(Keyboard::Key key){
    if(key<0||key>=Keyboard::Key::KeyCount)
        return "Touche inconnu";

    return KeyName[key];
}

