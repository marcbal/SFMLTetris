#include "Game.hpp"




Game::Game(sf::Vector2i * window_size, char *state,Evenement * evenement) :
    matrix(window_size),
    pieceSuivante(),
    nextTetromino(),
    scoreInfos(sf::Vector2f(650, (window_size->y-150)/2.0+100), sf::Vector2f(225, 150), 17, nullptr),
    scoreInfosBefore(sf::Vector2f(650, (window_size->y-150)/2.0-100), sf::Vector2f(225, 150), 17, nullptr),
    gameClock(),
    totalPauseTime(sf::seconds(0.0)),
    lastPauseStartingTime(sf::seconds(0.0))
{
    _evenement = evenement;
    _window_size = window_size;
    _state = state;
    _nb_line = 0;
    _score = 0;
    _nb_manual_down = 0;
    _nb_tetromino = 1;

    setPause((*state != GAME));

    float next_tetromino_top = (window_size->y - (NB_NEXT_TETROMINO * 4 * CEIL_SIZE + (NB_NEXT_TETROMINO - 1) * 50))/ 2.0;

    for (int i = 0; i<NB_NEXT_TETROMINO; i++)
    {
        NextTetrominoBoard nextTB(sf::Vector2f(100, next_tetromino_top + (4 * CEIL_SIZE + 50) * i));
        nextTB.newPiece(*(new Tetromino(rand_int(0, 6), 0, sf::Vector2i(0, 0))));
        nextTetromino.push_back(nextTB);
    }



    scoreInfosBefore.setText(L"Partie précédente :  \nScore : -\nLignes : -\nNiveau : -\nTetrominos : -\nTemps : -");


}

Game::~Game() {}


void Game::onEvent(sf::Event & event)
{
    switch(event.type)
    {
        case sf::Event::KeyPressed:
            if(event.key.code == _evenement->getEventKey("Pause")){
                    setPause(true);
                    *_state = INDEX;
            }

            if(event.key.code == _evenement->getEventKey("Gauche")){
                    matrix.moveLeft();
            }

            if(event.key.code == _evenement->getEventKey("Droite")){
                    matrix.moveRight();
            }

            if(event.key.code == _evenement->getEventKey("Descente Rapide")){
                    matrix.MoveDown();
                    _nb_manual_down += SOFT_DROP_BONUS_COEFF;
                    setTimeLastMoveDown();
            }
            if(event.key.code == _evenement->getEventKey("Descente Instantanee")){
                    _nb_manual_down += HARD_DROP_BONUS_COEFF * matrix.HardDrop();
            }

            if(event.key.code == _evenement->getEventKey("Rotation Gauche"))
            {
                    matrix.rotateLeft();
            }
            if(event.key.code == _evenement->getEventKey("Rotation Droite"))
            {
                    matrix.rotateRight();
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


    _nb_tetromino++;
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
    scoreInfosBefore.setText(L"Partie précédente :  \nScore : "+ to_string(_score) +"\n"+
                             "Lignes : "+to_string(_nb_line)+"\n"+
                             "Niveau : "+to_string(getLevel())+"\n"+
                             "Tetrominos : "+to_string(_nb_tetromino)+"\n"+
                             "Temps : "+formattedDuration(getGameTime(), 1));


    _nb_line = _score = 0;
    _nb_tetromino = 1;
    gameClock.restart();
    totalPauseTime = sf::Time::Zero;
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
    if (time_diff > getTimeAutoMoveDown())
    {
        matrix.MoveDown();
        setTimeLastMoveDown();
    }



    scoreInfos.setText("Partie en cours :    \nScore : "+to_string(_score)+"\n"+
                       "Lignes : "+to_string(_nb_line)+"\n"+
                       "Niveau : "+to_string(getLevel())+"\n"+
                       "Tetrominos : "+to_string(_nb_tetromino)+"\n"+
                       "Temps : "+formattedDuration(getGameTime(), 1)+"");


    matrix.dessinePieceCourrante();
}







int Game::getLevel()
{
    return (_score / POINTS_LEVEL);
}



void Game::setTimeLastMoveDown()
{
    sf::Time t = timeLastMoveDown + getTimeAutoMoveDown();
    if (t > getGameTime())
        t = getGameTime();
    timeLastMoveDown = t;
}


sf::Time Game::getTimeAutoMoveDown()
{
    return sf::seconds(exp((float) getLevel() * (- SPEED_LEVEL_COEFF)) + 0.1);
}


void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(matrix, states);
    for (int i = 0; i<NB_NEXT_TETROMINO; i++)
    {
        target.draw(nextTetromino[i], states);
    }
    target.draw(scoreInfos);
    target.draw(scoreInfosBefore);
}
