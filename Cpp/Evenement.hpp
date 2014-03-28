#ifndef _EVENEMENT_HPP_
#define _EVENEMENT_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Evenement
{

protected:

    typedef  std::map<std::string,sf::Keyboard::Key> KeyConf;

    /* ########################     _keyconf    ########################

        _keyconf sert à associer une touche et un événement sous forme de string.
    */
    KeyConf _keyconf;



    typedef  std::map<sf::Keyboard::Key,bool> KeyStates;

    /* ########################   _keyStates   ########################

        _keyStates sert à garder en mémoire le statut d'une touche.
    */
    KeyStates _keystates;




public:



    /* ########################   onKeyboard   ########################

        Fonction à appeler à chaque appuis d'une touche sur le clavier.

        Elle sert à tenir à jour l'objet des différents statuts des touches.

        Elle prend un argument :
            event qui est l'événement lié à cette appuis de touche.
    */
    void onKeyboard(const sf::Event & event);



    /* ########################   addKeyconf   ########################

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
    void addKeyconf(std::string str,sf::Keyboard::Key key);



    /* ########################   getKeyState  ########################

        Fonction permettant de savoir si la touche associé à un événement est enfoncé ou non.

        Elle renverra :
            TRUE pour Enfoncé
            FALSE pour Relâché

        Exemple :

        01      addKeyconf("saut",sf::Keyboard::Escape);
        02          //...
        03      if(getKeyState("saut"){
        04          // code du saut
        05      }
    */
    bool getKeyState(std::string str);


};
#endif // _EVENEMENT_HPP_
