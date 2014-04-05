#ifndef _EVENEMENT_HPP_
#define _EVENEMENT_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Evenement
{

protected:

    typedef  std::map<std::string,sf::Keyboard::Key> EventConf;

    /* ########################     Eventconf    ########################

            EventConf sert à associer une touche et un événement sous forme de string.
    */
    EventConf _eventconf;

public:

    /* ########################   addEventConf   ########################

        Fonction permettant d'ajouter un événement.

        Exemple :

        01      addKeyconf("saut",sf::Keyboard::Space);

        Cette ligne ajouteras l'événement saut et l'associeras à la barre espace.

        À noter que pour changer la touche associé à un événement, il suffit de le ré-ajouter.

        Exemple :

        01      addKeyconf("saut",sf::Keyboard::Escape);

        Cette ligne, si elle est éxecutée après celle vue plus haut,
        changera la touche associée à l'événement saut par la touche échappement.
    */
    void addEventConf(std::string str,sf::Keyboard::Key key);



    /* ########################   getEventState  ########################

        Fonction permettant de savoir si la touche associé à un événement est enfoncé ou non.

        Elle renverra :
            TRUE pour Enfoncé
            FALSE pour Relâché

        Exemple :

        01      addEventConf("saut",sf::Keyboard::Escape);
        02          //...
        03      if(getEventState("saut"){
        04          // code du saut
        05      }
    */
    bool getEventState(std::string str);


};
#endif // _EVENEMENT_HPP_
