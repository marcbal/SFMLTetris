#include "Evenement.hpp"

#include <iostream>

using namespace sf;
using namespace std;



void Evenement::addEventConf(string str,Keyboard::Key key)
{
    _eventconf[str] = key;    //On crée ou met à jour la touche associée à un événement 'str'. Cette touche sera maintenant 'key'
}

bool Evenement::getEventState(std::string str)
{
    return  _eventconf.find(str)!=_eventconf.end() && sf::Keyboard::isKeyPressed(_eventconf[str]); //Si la touche n'est pas trouvée on renvoit FALSE
}
