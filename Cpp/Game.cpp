#include "Game.hpp"

Game::Game(sf::Vector2i * window_size, char *state) :
    matrix(window_size),
    pieceSuivante(),
    gameClock()
{
    _window_size = window_size;
    _state = state;
    _nb_line = 0;
    _score = 0;

    setPause((*state != GAME));

}

Game::~Game() {}


void Game::onEvent(sf::Event & event)
{
    switch(event.type)
    {
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Escape:
                    *_state = INDEX;
                break;
                case sf::Keyboard::Left:
                    matrix.moveLeft();
                break;
                case sf::Keyboard::Right:
                    matrix.moveRight();
                break;
                case sf::Keyboard::Down:
                case sf::Keyboard::Space:
                    matrix.MoveDown();
                    setTimeLastMoveDown();
                break;
                case sf::Keyboard::Up:
                    matrix.HardDrop();
                break;
                case sf::Keyboard::Q:
                    matrix.rotateLeft();
                break;
                case sf::Keyboard::D:
                    matrix.rotateRight();
                break;
                default: break;
            }
        break;
        default:

        break;
    }





}




void Game::setPause(bool p)
{
    if (_pause && !p)
    {   // reprise du jeu
        setTimeLastMoveDown();
    }
    _pause = p;
}
bool Game::getPause()
{
    return _pause;
}




void Game::update()
{
    matrix.effacePieceCourrante();

    if (getPause())
        setPause(false);


    if (!matrix.pieceIsActive())
    {   // passage à la pièce suivante
        int new_del_line = matrix.fullLinesClear();
        _nb_line += new_del_line;
        switch (new_del_line)
        {
            case 1: _score+=40; break;
            case 2: _score+=100; break;
            case 3: _score+=300; break;
            case 4: _score+=1200; break;
            default: break;
        }
        // on tente de placer la piece suivante
        if (!matrix.newPiece(pieceSuivante))
        {   // le jeu est fini, on recommence
            matrix.clearBoard();
            matrix.newPiece(*(new Tetromino()));
            _nb_line = _score = 0;
            gameClock.restart();
        }
        setTimeLastMoveDown();
        pieceSuivante = *(new Tetromino());
        cout << "Lignes=" << _nb_line << " ; Score=" << _score << " ; Niveau=" << getLevel() << endl;
    }

    sf::Time time_diff = gameClock.getElapsedTime()-timeLastMoveDown;
    if (time_diff.asSeconds() > exp((float) getLevel()*-0.3))
    {
        matrix.MoveDown();
        setTimeLastMoveDown();
    }



    matrix.dessinePieceCourrante();
}







int Game::getLevel()
{
    return (_score / POINTS_LEVEL);
}



void Game::setTimeLastMoveDown()
{
    timeLastMoveDown = gameClock.getElapsedTime();
}





void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(matrix, states);
}
