#include "ScreenDebug.hpp"

ScreenDebug::ScreenDebug(sf::Vector2i* window_size, GameConfiguration * gameConfig, AudioConfiguration * audio):
    _debug_info_background(sf::Vector2f(0, 0)),
    _audio_indicator(sf::Vector2f(100, 10)),
    _audio_indicator_border(sf::Vector2f(100, 10)),
    _console_text_background(sf::Vector2f(0, 0)),
    spectrum(128),
    spectrum2(128)
{
    _window_size = window_size;
    _audio = audio;
    _gameConfig = gameConfig;
    _debug_info.setCharacterSize(DEBUG_CHAR_SIZE);
    _debug_info.setColor(sf::Color::White);
    _debug_info.setFont(*Ressources::getDefaultFont());
    _debug_info.setPosition(10, 10);

    _debug_info_background.setFillColor(sf::Color(0, 0, 0, 192));
    _debug_info_background.setPosition(5, 5);

    _console_text.setCharacterSize(DEBUG_CHAR_SIZE);
    _console_text.setColor(sf::Color::White);
    _console_text.setFont(*Ressources::getDefaultFont());

    _console_text_background.setFillColor(sf::Color(0, 0, 0, 192));


    _audio_indicator.setPosition(_window_size->x - 112, 12);
    _audio_indicator.setFillColor(sf::Color(160, 160, 160));
    _audio_indicator_border.setPosition(_window_size->x - 112, 12);
    _audio_indicator_border.setOutlineColor(sf::Color::White);
    _audio_indicator_border.setOutlineThickness(2);


    for (unsigned int i=0; i<spectrum.size(); i++)
    {
        spectrum[i].setFillColor(sf::Color(255,0,0,64));
        spectrum[i].setSize(sf::Vector2f(3, 1));
        spectrum[i].setPosition(sf::Vector2f(2+i*5, _window_size->y - spectrum[i].getSize().y - 2));
    }
    for (unsigned int i=0; i<spectrum2.size(); i++)
    {
        spectrum2[i].setFillColor(sf::Color(0,0,255,64));
        spectrum2[i].setSize(sf::Vector2f(3, 1));
        spectrum2[i].setPosition(sf::Vector2f(2+i*5, _window_size->y - spectrum[i].getSize().y - 2));
    }

}

ScreenDebug::~ScreenDebug() {}

void ScreenDebug::setGamePtr(Game * game){ _game = game;}


void ScreenDebug::update()
{
    // récupération des messages de la console
    vector<sf::String> console_message = Console::getLogMessages();
    for (unsigned int i=0; i<console_message.size();i++)
        _console_lines.push_back(console_message[i]);
    while (_console_lines.size()>DEBUG_NB_CHAR_HEIGHT)
        _console_lines.erase(_console_lines.begin());    // efface le premier élément et décale le reste (je viens d'apprendre ça)

    vector<vector<float> > spectrum_data = _audio->getAudioSpectrum();

    for (unsigned int i=0; i<spectrum.size() && i<spectrum_data[0].size(); i++)
    {
        float size_y = spectrum_data[0][i]*500;
        spectrum[i].setSize(sf::Vector2f(3, size_y));
        spectrum[i].setPosition(sf::Vector2f(2+i*5, _window_size->y - size_y - 2));
    }
    if (spectrum_data.size() > 1)
        for (unsigned int i=0; i<spectrum2.size() && i<spectrum_data[1].size(); i++)
        {
            float size_y = spectrum_data[1][i]*500;
            spectrum2[i].setSize(sf::Vector2f(3, size_y));
            spectrum2[i].setPosition(sf::Vector2f(2+i*5, _window_size->y - size_y - 2));
        }


    int framerate = 1 / _FPSclock.restart().asSeconds();

    string uptime = formattedDuration(_clock.getElapsedTime(), 2);




    _debug_info.setString("SFML Tetris "+string(VERSION)+" - Par Marc Baloup et Louis Behague - http://sfmltetris.pandacube.fr/\nUptime : "+
                          uptime+
                          " - FPS : "+to_string(framerate) +
                          " - Particules : "+ to_string(ExplosionManager::_nbParticules) +
                          "\nJeu : " + ((_game->getPause())?"En pause":"En cours ...") +
                          ((!_game->getPause() && !_game->_AIActualPlaying)?(" - Auto descente piece : "+to_string(((_game->timeLastMoveDown+_game->getTimeAutoMoveDown())-_game->getGameTime()).asSeconds())+""):"")+
                          " - IA : "+to_string(_game->_AIActualPlaying)+" avec "+to_string((int) _game->_AINbTetromino)+" tetromino connu (next : "+to_string(_game->_AIPlay)+")"+
                          "\nAudio : "+to_string(_audio->getPlay())+
                          " - Volume : "+to_string(_audio->getVolume())+
                          " - Musique : "+((_audio->getPlay())?(_audio->getMusicList()[_audio->getMusicPlayingId()]):"aucun"));

    _debug_info_background.setSize(sf::Vector2f(_debug_info.getLocalBounds().width+10, _debug_info.getLocalBounds().height+15));

    _console_text.setString(implode(_console_lines, L"\n"));

    _console_text.setPosition(10, _window_size->y - (10 + _console_text.getLocalBounds().height));
    _console_text_background.setPosition(_console_text.getPosition()-sf::Vector2f(5, 5));
    _console_text_background.setSize(sf::Vector2f(_console_text.getLocalBounds().width+10, _console_text.getLocalBounds().height+15));

    _audio_indicator.setSize(sf::Vector2f(100*_audio->getAudioLevel(), 10));
}






void ScreenDebug::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned int i=0; i<spectrum.size(); i++)
        target.draw(spectrum[i], states);
    for (unsigned int i=0; i<spectrum2.size(); i++)
        target.draw(spectrum2[i], states);
    target.draw(_debug_info_background, states);
    target.draw(_console_text_background, states);
    target.draw(_debug_info, states);
    target.draw(_console_text, states);
    target.draw(_audio_indicator_border, states);
    target.draw(_audio_indicator, states);
}
