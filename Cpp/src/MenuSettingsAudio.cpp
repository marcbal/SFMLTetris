#include "MenuSettingsAudio.hpp"

using namespace std;
using namespace sf;
MenuSettingsAudio::MenuSettingsAudio(Vector2i * window_size,char *state,AudioConfiguration * audio):
    Menu(window_size,state),
    _play(Vector2f(50,80), Vector2f(20,20),audio->getPlay()),
    _volume(Vector2f(50,160),Vector2f(405,24),audio->getVolume(),0,100),
    _musicSelect(Vector2f(50, 280), Vector2f(405, 30), 4, audio->getMusicList(), audio->getMusicPlayingId())
{
    _audio=audio;

    titre.setString(L"Paramètres audio");


    menuElements.push_back(Bouton(sf::Vector2f(505, _window_size->y-70), sf::Vector2f(177, 30), 18, _state));
    menuElements[0].setAction(SETTINGS);
    menuElements[0].setText(L"Retour");

    menuElements.push_back(Bouton(sf::Vector2f(278, _window_size->y-70), sf::Vector2f(177, 30), 18, _state));
    menuElements[1].setAction(INDEX);
    menuElements[1].setText(L"Menu Principal");


    textPlay.setCharacterSize(20);
    textPlay.setFillColor(sf::Color::White);
    textPlay.setFont(*Ressources::getDefaultFont());
    textPlay.setPosition(85, 76);
    textPlay.setString("Activer la musique");

    textVolume.setCharacterSize(20);
    textVolume.setFillColor(sf::Color::White);
    textVolume.setFont(*Ressources::getDefaultFont());
    textVolume.setPosition(50, 120);
    textVolume.setString("Volume de la musique : "+to_string((int) _audio->getVolume())+"%");

    textSelect.setCharacterSize(20);
    textSelect.setFillColor(sf::Color::White);
    textSelect.setFont(*Ressources::getDefaultFont());
    textSelect.setPosition(50, 240);
    textSelect.setString("Choix de la musique :");
}




void MenuSettingsAudio::onEvent(Event & event){
    _play.onEvent(event);
    _volume.onEvent(event);
    _musicSelect.onEvent(event);
    Menu::onEvent(event);
    _audio->setVolume(_volume.getValue());
    _audio->setPlay(_play.getValue());
    _audio->changeMusic(_musicSelect.getValueSelected());
    textVolume.setString("Volume de la musique : "+to_string((int) _audio->getVolume())+"%");
}

void MenuSettingsAudio::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Menu::draw(target,states);
    target.draw(_play,states);
    target.draw(_volume,states);
    target.draw(textPlay,states);
    target.draw(textVolume,states);
    target.draw(_musicSelect,states);
    target.draw(textSelect,states);
}
