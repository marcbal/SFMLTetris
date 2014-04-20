#include "MenuSettingsAudio.hpp"

using namespace std;
using namespace sf;
MenuSettingsAudio::MenuSettingsAudio(Vector2i * window_size,char *state,AudioConfiguration * audio):
    Menu(window_size,state),
    _volume(Vector2f(_window_size->x/2-150,200),Vector2f(300,20),100,0,100),
    _play(Vector2f(_window_size->x/2-7,260), Vector2f(15,15),true)
{
    _audio=audio;

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




void MenuSettingsAudio::onEvent(Event & event){
    _play.onEvent(event);
    _volume.onEvent(event);
    Menu::onEvent(event);
    _audio->setVolume(_volume.getValue());
    _audio->setPlay(_play.getValue());
}

void MenuSettingsAudio::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Menu::draw(target,states);
    target.draw(_play,states);
    target.draw(_volume,states);
}
