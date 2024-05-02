#include "Evenement.hpp"

#include <iostream>

using namespace sf;
using namespace std;



const std::string Evenement::KeyName[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
								 "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
								 "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Echap",
								 "Ctrl Gauche", "Shift Gauche", "Alt Gauche", "System Gauche",
								 "Ctrl Droit", "Shift Droit", "Alt Droit", "System Droit", "Menu",
								 "[", "]", ";", ",", ".", "'", "/", "\\", "~", "=", "-", "Espace",
								 "Entree", "Retour arriere", "Tabulation", "Page suiv.", "Page prec.",
								 "Fin", "Debut", "Insert", "Suppr", "+ Numpad", "- Numpad", "* Numpad", "/ Numpad", "Gauche", "Droite", "Haut",
								 "Bas", "0 Numpad", "1 Numpad", "2 Numpad", "3 Numpad", "4 Numpad", "5 Numpad", "6 Numpad", "7 Numpad", "8 Numpad", "9  Numpad",
								 "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause"};

Evenement::Evenement(){
    makeDir(getGameDataPath());
    initDefault();
    /* on charge d'abord la configuration par défaut avant de l'écraser par celle présente
    dans le fichier (évite les problèmes de touches non configurés à cause du fichier modifié à la main) */
    if(!loadFromFile(getGameDataPath("keyboard.cfg")))
    {
        Console::err("Erreur de chargement du fichier de configuration des touches.");
        Console::out("La configuration des touches a été réinitialisée.");
        saveConfigurationFile();
    }
}

void Evenement::initDefault(){
    addEventConf("Gauche",Keyboard::Left);
    addEventConf("Droite",Keyboard::Right);
    addEventConf("Rotation Gauche",Keyboard::Q);
    addEventConf("Rotation Droite",Keyboard::D);
    addEventConf("Descente Rapide",Keyboard::Down);
    addEventConf("Descente Instantanee",Keyboard::Up);
    addEventConf("Pause",Keyboard::Escape);
    addEventConf("Recommencer",Keyboard::Return);
    addEventConf("Hold Piece",Keyboard::Space);
    addEventConf("Ecran Debug",Keyboard::F3);
    addEventConf("Activation IA",Keyboard::F8);
    addEventConf("IA P. Dellacherie",Keyboard::F9);
    addEventConf("IA fait maison",Keyboard::F10);
}

bool Evenement::loadFromFile(string file){

        ifstream saveFile(file.c_str(), ios::in);

        if(!saveFile)
            return false;

        string line;
        vector<string> words;

        while(getline(saveFile, line)){
            words = explode(line,':');
            if(words.size()!=2)
                return false;

            addEventConf(words[0], (sf::Keyboard::Key)string_to_int(words[1]));
        }



        saveFile.close();

        return true;
}

bool Evenement::saveConfigurationFile(){
     ofstream saveFile(getGameDataPath("keyboard.cfg"), ios::out | ios::trunc);

     if(!saveFile)
        return false;

    for(EventConf::iterator it=_eventconf.begin() ; it!=_eventconf.end() ; ++it)
    {
        saveFile << it->first << ':' << it->second << endl;;
    }

     saveFile.close();

     return true;
}

void Evenement::addEventConf(string str,Keyboard::Key key)
{
    if(_eventconf.find(str)==_eventconf.end() || _eventconf[str] != key)
    {   // cette condition réduit le nombre d'écriture dans le fichier
        _eventconf[str] = key;    //On crée ou met à jour la touche associée à un événement 'str'. Cette touche sera maintenant 'key'
        saveConfigurationFile();
    }
}

bool Evenement::getEventState(std::string str)
{
    return  _eventconf.find(str)!=_eventconf.end() && sf::Keyboard::isKeyPressed(_eventconf[str]); //Si la touche n'est pas trouvée on renvoit FALSE
}

Keyboard::Key Evenement::getEventKey(string str){
    if(_eventconf.find(str)!=_eventconf.end())
        return _eventconf[str];
    else
    {
        Console::err(L"L'évènement demandé \"" + str + L"\" n'a pas été trouvé dans le gestionnaire d'évènement", __FILE__, __LINE__);
        return Keyboard::Key::Unknown;
    }
}

string Evenement::keyToString(Keyboard::Key key){
    if(key<0||key>=Keyboard::Key::KeyCount)
        return "Touche inconnu";

    return KeyName[key];
}

