#include "Game.hpp"




Game::Game(sf::Vector2i * window_size) :
    matrix(window_size),
    nextTetromino(sf::Vector2f(0, 30)),
    textTetrominoBoard(),
    holdedTetromino(sf::Vector2f(0, 70 + 2*CEIL_SIZE)),
    hasHoldedTetromino(false),
    canHoldTetromino(false),
    _replay(0),
    gameClock()
{
    _window_size = window_size;
    _score = 0;
    _window_size = window_size;


    sf::Text t1;
    t1.setCharacterSize(15);
    t1.setColor(sf::Color::Black);
    sf::Font * f = new sf::Font;
    f->loadFromFile("police.ttf");

    t1.setFont(*f);
    t1.setString("Hold :");
    t1.setPosition(5, 45 + 2*CEIL_SIZE);
    textTetrominoBoard.push_back(t1);

    nextTetromino.newPiece(*(new Tetromino(0, 0, sf::Vector2i(0, 0))));
    sf::Text t;
    t.setCharacterSize(15);
    t.setColor(sf::Color::Black);
    t.setFont(*f);
    t.setString("Next :");
    t.setPosition(5, 5);
    textTetrominoBoard.push_back(t);



    restartGame();


    scoreInfosBefore.setCharacterSize(15);
    scoreInfosBefore.setColor(sf::Color::Black);
    scoreInfosBefore.setFont(*f);
    scoreInfosBefore.setPosition(350, 150);
    scoreInfosBefore.setString(L"Partie précédente :  \nScore : -\nLignes : -\nNiveau : -\nTetrominos : -\nTemps : -");




    scoreInfos.setCharacterSize(15);
    scoreInfos.setColor(sf::Color::Black);
    scoreInfos.setFont(*f);
    scoreInfos.setPosition(350, 10);


    commandes.setCharacterSize(13);
    commandes.setColor(sf::Color::Black);
    commandes.setFont(*f);
    commandes.setPosition(350, 300);
    commandes.setString((wstring)L"Commandes :\n"+
                        L"Gauche et droite : Déplacements\n"+
                        L"Q et D : rotation\n"
                        L"Haut : Hard Drop\n"+
                        L"Bas : Descendre d'une case\n"+
                        L"Espace : Bloquer une pièce (Hold)\n"+
                        L"Entrée : Recommencer");
}

Game::~Game() {}


void Game::onEvent(sf::Event & event)
{





    switch(event.type)
    {
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Left){
                if (matrix.moveLeft())
                    initTimeoutOnMove();
            }

            if(event.key.code == sf::Keyboard::Right){
                if(matrix.moveRight())
                    initTimeoutOnMove();
            }

            if(event.key.code == sf::Keyboard::Down){
                matrix.MoveDown();
                _nb_manual_down += SOFT_DROP_BONUS_COEFF;
                setTimeLastMoveDown();
            }
            if(event.key.code == sf::Keyboard::Up){
                _nb_manual_down += HARD_DROP_BONUS_COEFF * matrix.HardDrop();
            }

            if(event.key.code == sf::Keyboard::Q)
            {
                if(matrix.rotateLeft())
                    initTimeoutOnMove();
            }
            if(event.key.code == sf::Keyboard::D)
            {
                if(matrix.rotateRight())
                    initTimeoutOnMove();
            }
            if(event.key.code == sf::Keyboard::Space)
            {
                if(holdTetromino())
                    setTimeLastMoveDown();
            }
            if(event.key.code == sf::Keyboard::Return)
                _replay = 1;

        break;
        default: break;
    }





}


bool Game::nextPiece(bool cancelCountTetromino = false)
{
    Tetromino p = nextTetromino.getPiece();

    if (!matrix.newPiece(p))
    {
        return false;
    }


    canHoldTetromino = true;



    nextTetromino.newPiece(*(new Tetromino(rand_int(0, 6), 0, sf::Vector2i(0, 0))));


    if (!cancelCountTetromino) _nb_tetromino++;
    return true;
}




sf::Time Game::getGameTime()
{
    return gameClock.getElapsedTime();
}




void Game::restartGame()
{
    matrix.clearBoard();


    matrix.newPiece(*(new Tetromino(rand_int(0, 6), 0)));
    if (_score > 0)
        scoreInfosBefore.setString(L"Partie précédente :  \nScore : "+ to_string(_score, " ") +"\n"+
                                 "Lignes : "+to_string(_nb_line, " ")+"\n"+
                                 "Niveau : "+to_string(getLevel(), " ")+"\n"+
                                 "Tetrominos : "+to_string(_nb_tetromino, " ")+"\n"+
                                 "Temps : "+formattedDuration(getGameTime(), 1));


    nextTetromino.newPiece(*(new Tetromino(rand_int(0, 6), 0, sf::Vector2i(0, 0))));



    _nb_line = _score = 0;
    _nb_tetromino = 1;
    gameClock.restart();

    holdedTetromino.clearPiece();
    hasHoldedTetromino = false;
    canHoldTetromino = true;
    setTimeLastMoveDown();

}





bool Game::holdTetromino()
{
    if (!canHoldTetromino)
        return false;

    if (!hasHoldedTetromino)
    {
        Tetromino t(matrix.getPieceCourrante().getTypePiece(), 0, sf::Vector2i(INIT_POS_X, INIT_POS_Y));
        if (!nextPiece(true))
            return false;
        holdedTetromino.newPiece(t);
        hasHoldedTetromino = true;
    }
    else
    {
        Tetromino t(matrix.getPieceCourrante().getTypePiece(), 0, sf::Vector2i(INIT_POS_X, INIT_POS_Y));
        Tetromino th = holdedTetromino.getPiece();
        if (!matrix.newPiece(th))
            return false;
        holdedTetromino.newPiece(t);
    }


    canHoldTetromino = false;
    return true;
}




void Game::update()
{
    if (_replay == 1)
    {
        restartGame();
        _replay = 0;
    }



    matrix.effacePieceCourrante();



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

        if (_score > 1999999999)
            _score = 1999999999;

        // on tente de placer la piece suivante
        if (!nextPiece())
            restartGame();
        setTimeLastMoveDown();

        _nb_manual_down = 0;

    }

    sf::Time time_diff = getGameTime()-timeLastMoveDown;
    if (time_diff > getTimeAutoMoveDown())
    {
        matrix.MoveDown();
        setTimeLastMoveDown();
    }



    scoreInfos.setString("Partie en cours :    \nScore : "+to_string(_score, " ")+"\n"+
                       "Lignes : "+to_string(_nb_line, " ")+"\n"+
                       "Niveau : "+to_string(getLevel(), " ")+"\n"+
                       "Tetrominos : "+to_string(_nb_tetromino, " ")+"\n"+
                       "Temps : "+formattedDuration(getGameTime(), 1)+"");


    matrix.dessinePieceCourrante(false);

    matrix.updateGraphics(0);

}







int Game::getLevel()
{
    return (int)(sqrt(_score)/LEVEL_COEFF);
}



void Game::setTimeLastMoveDown()
{
    sf::Time t = timeLastMoveDown + getTimeAutoMoveDown();
    if (t > getGameTime())
        t = getGameTime();
    timeLastMoveDown = t;
}

void Game::initTimeoutOnMove()
{
    if (!matrix.MoveDownCheck())
        setTimeLastMoveDown();
}


sf::Time Game::getTimeAutoMoveDown()
{
    return sf::seconds(exp((float) getLevel() * (- SPEED_LEVEL_COEFF)) + 0.1);
}


void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(matrix, states);
        target.draw(nextTetromino, states);
    for (unsigned int i = 0; i<textTetrominoBoard.size(); i++)
        target.draw(textTetrominoBoard[i], states);
    target.draw(holdedTetromino, states);
    target.draw(scoreInfos, states);
    target.draw(scoreInfosBefore, states);
    target.draw(commandes, states);
}
