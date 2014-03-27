#include "Evenement.hpp"
#include <iostream>
using namespace sf;
using namespace std;


void Evenement::onKeyboard(const sf::Event & event)
{
    for (KeyStates::iterator it = _keystates.begin(); it != _keystates.end(); it++) //Parcourt tout les éléments contenus dans _keystates...
    {
        if (event.key.code == it->first)    //Lorsque l'événement passé en paramètre correspond à celui parcourru dans _keystates...
        {
            it->second = (event.type == sf::Event::KeyPressed); //Alors on met à jour son statut en fonction de l'appuis ou du relachement de la touche.

            break; //Instruction permettant d'arrêter la recherche de la touche si celle-ci a été trouvée. (On sort de la boucle for).
        }
    }

}

void Evenement::addKeyconf(string str,Keyboard::Key key)
{
    _keyconf[str] = key;    //On crée ou met à jour la touche associée à un événement 'str'. Cette touche sera maintenant 'key'
    _keystates[_keyconf[str]] = false; //On déclare son statut dans le tableau _keystates et on l'initialise à FALSE.
}

bool Evenement::getKeyState(std::string str)
{
    return  _keystates[_keyconf[str]] //Renvoit du statut de la touche liée à l'événement str.
            && _keyconf.find(str)!=_keyconf.end(); //Si la touche n'est pas trouvée on renvoit FALSE
}
