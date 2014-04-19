#ifndef _MENU_SETTINGS_AUDIO_HPP_
#define _MENU_SETTINGS_AUDIO_HPP_
#include "Menu.hpp"
#include "AudioConfiguration.hpp"
#include "Application.hpp"
#include "InputCheck.hpp"
#include "InputRange.hpp"
#include <SFML/Graphics.hpp>


class MenuSettingsAudio : public Menu{

private :
    AudioConfiguration * _audio;
    InputCheck _play;
    InputRange _volume;
public :
    MenuSettingsAudio(sf::Vector2i * window_size,char *state,AudioConfiguration * audio);
    virtual void onEvent(sf::Event & event);
protected:
     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // _MENU_SETTINGS_AUDIO_HPP_
