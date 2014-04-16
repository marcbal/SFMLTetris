#include "Game.hpp"

Game::Game(sf::Vector2i * window_size, char *state) :
    matrix(window_size),
    pieceSuivante(),
    nextTetromino(),
    scoreInfos(sf::Vector2f(650, (window_size->y-150)/2.0), sf::Vector2f(200, 150), 15, nullptr),
    gameClock(),
    totalPauseTime(sf::seconds(0.0)),
    lastPauseStartingTime(sf::seconds(0.0))
{
    _window_size = window_size;
    _state = state;
    _nb_line = 0;
    _score = 0;
    _nb_manual_down = 0;

    setPause((*state != GAME));

    float next_tetromino_top = (window_size->y - (NB_NEXT_TETROMINO * 4 * CEIL_SIZE + (NB_NEXT_TETROMINO - 1) * 50))/ 2.0;

    for (int i = 0; i<NB_NEXT_TETROMINO; i++)
    {
        NextTetrominoBoard nextTB(sf::Vector2f(100, next_tetromino_top + (4 * CEIL_SIZE + 50) * i));
        nextTB.newPiece(*(new Tetromino(rand_int(0, 6), 0, sf::Vector2i(0, 0))));
        nextTetromino.push_back(nextTB);
    }





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
                    setPause(true);
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
                    _nb_manual_down += SOFT_DROP_BONUS_COEFF;
                    setTimeLastMoveDown();
                break;
                case sf::Keyboard::Up:
                    _nb_manual_down += HARD_DROP_BONUS_COEFF * matrix.HardDrop();
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
        case sf::Event::MouseMoved:
            matrix.mouseLeftRight(event);
        break;
        case sf::Event::MouseButtonPressed:
            switch(event.mouseButton.button)
            {
                case sf::Mouse::Left:
                    matrix.rotateLeft();
                break;
                case sf::Mouse::Right:
                    matrix.rotateRight();
                break;
                case sf::Mouse::Middle:
                    matrix.MoveDown();
                    _nb_manual_down += SOFT_DROP_BONUS_COEFF;
                    setTimeLastMoveDown();
                break;
                default: break;
            }
        break;
        default: break;
    }





}


bool Game::nextPiece()
{
    Tetromino p = nextTetromino[0].getPiece();

    if (!matrix.newPiece(p))
    {
        return false;
    }



    for (int i=0; i<NB_NEXT_TETROMINO; i++)
    {
        if (i < NB_NEXT_TETROMINO - 1)
        {

            Tetromino t = nextTetromino[i+1].getPiece();
            nextTetromino[i].newPiece(t);
        }
        else
            nextTetromino[i].newPiece(*(new Tetromino(rand_int(0, 6), 0, sf::Vector2i(0, 0))));
    }


    return true;
}




sf::Time Game::getGameTime()
{
    return gameClock.getElapsedTime() - totalPauseTime;
}



void Game::setPause(bool p)
{
    if (_pause && !p)
    {   // reprise du jeu

        totalPauseTime += (gameClock.getElapsedTime() - lastPauseStartingTime);

        setTimeLastMoveDown();
    }
    else if (!_pause && p)
    {   // mise en pause
        lastPauseStartingTime = gameClock.getElapsedTime();
    }
    _pause = p;
}
bool Game::getPause()
{
    return _pause;
}




void Game::restartGame()
{
    matrix.clearBoard();
    matrix.newPiece(*(new Tetromino()));
    _nb_line = _score = 0;
    gameClock.restart();
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
        {   // http://tetris.wikia.com/wiki/Scoring#Original_Nintendo_Scoring_System
            case 1: _score += 40 * (getLevel()+1); break;
            case 2: _score += 100 * (getLevel()+1); break;
            case 3: _score += 300 * (getLevel()+1); break;
            case 4: _score += 1200 * (getLevel()+1); break;
            default: break;
        }

        if (new_del_line > 0)
            _score += _nb_manual_down; // ajoute le bonus pour l'accelération

        // on tente de placer la piece suivante
        if (!nextPiece())
            restartGame();
        setTimeLastMoveDown();
        pieceSuivante = *(new Tetromino());

        _nb_manual_down = 0;

    }

    sf::Time time_diff = getGameTime()-timeLastMoveDown;
    if (time_diff.asSeconds() > exp((float) getLevel() * (- SPEED_LEVEL_COEFF)) + 0.1)
    {
        matrix.MoveDown();
        setTimeLastMoveDown();
    }


    sf::Time chrono = getGameTime();

    scoreInfos.setText("Score : "+to_string(_score)+"\n"+
                       "Lignes : "+to_string(_nb_line)+"\n"+
                       "Niveau : "+to_string(getLevel())+"\n"+
                       "Temps : "+formattedDuration(chrono)+"");


    matrix.dessinePieceCourrante();
}







int Game::getLevel()
{
    return (_score / POINTS_LEVEL);
}



void Game::setTimeLastMoveDown()
{
    timeLastMoveDown = getGameTime();
}





void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(matrix, states);
    for (int i = 0; i<NB_NEXT_TETROMINO; i++)
    {
        target.draw(nextTetromino[i], states);
    }
    target.draw(scoreInfos);
}
