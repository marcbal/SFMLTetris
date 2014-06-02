#include "ScreenDebug.hpp"

ScreenDebug::ScreenDebug(sf::Vector2i* window_size):
    _debug_info_background(sf::Vector2f(0, 0)),
    _console_text_background(sf::Vector2f(0, 0))
{
    _window_size = window_size;
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
}

ScreenDebug::~ScreenDebug() {}

void ScreenDebug::setGamePtr(Game * game){ _game = game;}


void ScreenDebug::update()
{
    // récupération des messages de la console
    vector<string> console_message = Console::getLogMessages();
    for (unsigned int i=0; i<console_message.size();i++)
        _console_lines.push_back(console_message[i]);
    while (_console_lines.size()>DEBUG_NB_CHAR_HEIGHT)
        _console_lines.erase(_console_lines.begin());    // efface le premier élément et décale le reste (je viens d'apprendre ça)

    int framerate = 1 / _FPSclock.restart().asSeconds();

    string uptime = formattedDuration(_clock.getElapsedTime(), 2);




    _debug_info.setString("SFML Tetris - Par Marc Baloup et Louis Behague - http://sfmltetris.no-ip.org/\nUptime : "+
                          uptime+
                          " - FPS : "+to_string(framerate) +
                          " - Particules : "+ to_string(ExplosionManager::_nbParticules) +
                          "\nPause : " + to_string(_game->getPause()) +
                          ((!_game->getPause())?(" - Times before down  : "+to_string(((_game->timeLastMoveDown+_game->getTimeAutoMoveDown())-_game->getGameTime()).asSeconds())+""):"")+
                          L"\nIA : "+to_string(_game->_AIActualPlaying)+" avec "+to_string((int) _game->_AINbTetromino)+" tetromino connu (next : "+to_string(_game->_AIPlay)+")");

    _debug_info_background.setSize(sf::Vector2f(_debug_info.getLocalBounds().width+10, _debug_info.getLocalBounds().height+15));

    _console_text.setString(implode(_console_lines, "\n"));

    _console_text.setPosition(10, _window_size->y - (10 + _console_text.getLocalBounds().height));
    _console_text_background.setPosition(_console_text.getPosition()-sf::Vector2f(5, 5));
    _console_text_background.setSize(sf::Vector2f(_console_text.getLocalBounds().width+10, _console_text.getLocalBounds().height+15));
}






void ScreenDebug::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_debug_info_background, states);
    target.draw(_console_text_background, states);
    target.draw(_debug_info, states);
    target.draw(_console_text, states);
}
