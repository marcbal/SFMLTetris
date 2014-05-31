#include "Game.hpp"




Game::Game(sf::Vector2i * window_size, char *state,Evenement * evenement, Scores * scores, OpenGL_Manager * oGL, GameConfiguration* gameConfig) :
    Menu(window_size, state),
    matrix(window_size,oGL),
    nextTetromino(),
    textTetrominoBoard(),
    holdedTetromino(sf::Vector2f(0, 0)),
    hasHoldedTetromino(false),
    canHoldTetromino(false),
    scoreInfos(sf::Vector2f(0, 0), sf::Vector2f(0, 0), 17, nullptr),
    scoreInfosBefore(sf::Vector2f(0, 0), sf::Vector2f(0, 0), 17, nullptr),
    _replay(0),
    gameClock(),
    totalPauseTime(sf::Time::Zero),
    lastPauseStartingTime(sf::Time::Zero),
    _explosions(window_size),
    _scoreSender(),
    tetrominoRand()
{
    _score = 0;
    _AIPlay = false;
    _AIActualPlaying = false;
    _AINbTetromino = 2;
    _gameConfig = gameConfig;
    _evenement = evenement;
    _scores = scores;
    _window_size = window_size;
    _state = state;
    _oGL = oGL;



    int whiteSpaceBorder = (_window_size->y - (4 * (2 * CEIL_SIZE + 30))) / 8;
    int next_tetromino_top = 3 * whiteSpaceBorder + 2 * CEIL_SIZE + 30;

    holdedTetromino = *(new NextTetrominoBoard(sf::Vector2f(window_size->x - (whiteSpaceBorder + 4*CEIL_SIZE), whiteSpaceBorder + 30)));
    sf::Text t1;
    t1.setCharacterSize(15);
    t1.setColor(sf::Color::White);
    t1.setFont(*Ressources::getDefaultFont());
    t1.setString("Hold :");
    t1.setPosition(window_size->x - (whiteSpaceBorder + 4*CEIL_SIZE), whiteSpaceBorder);
    textTetrominoBoard.push_back(t1);

    for (int i = 0; i<NB_NEXT_TETROMINO; i++)
    {
        NextTetrominoBoard nextTB(sf::Vector2f(window_size->x - (whiteSpaceBorder + 4*CEIL_SIZE), next_tetromino_top + (2 * CEIL_SIZE + 30 + 2 * whiteSpaceBorder) * i + 30));
        nextTB.newPiece(*(new Tetromino(0, 0, sf::Vector2i(0, 0))));
        nextTetromino.push_back(nextTB);
        sf::Text t;
        t.setCharacterSize(15);
        t.setColor(sf::Color::White);
        t.setFont(*Ressources::getDefaultFont());
        t.setString("Next " + to_string(i+1) + " :");
        t.setPosition(window_size->x - (whiteSpaceBorder + 4*CEIL_SIZE), next_tetromino_top + (2 * CEIL_SIZE + 30 + 2 * whiteSpaceBorder) * i);
        textTetrominoBoard.push_back(t);
    }
    int boutonHeight = 40;
    int scoreInfosWidth = 225;
    int scoreInfosHeight = 150;

    scoreInfos.setSize(sf::Vector2f(scoreInfosWidth, scoreInfosHeight));
    scoreInfosBefore.setSize(sf::Vector2f(scoreInfosWidth, scoreInfosHeight));

    int whiteSpaceScoreInfo = (_window_size->y - (2 * scoreInfosHeight + 2 * boutonHeight + 2 * whiteSpaceBorder)) / 3;

    // sers pour le réglage des viewports :
    //int tetrisBoardRightLimit = window_size->x - (2 * whiteSpaceBorder + 4 * CEIL_SIZE);
    //int tetrisBoardLeftLimit = 2 * whiteSpaceBorder + scoreInfosWidth;
    //cout << window_size->x << " " << tetrisBoardLeftLimit << " " << tetrisBoardRightLimit << endl;

    scoreInfosBefore.setPosition(sf::Vector2f(whiteSpaceBorder, _window_size->y - (whiteSpaceBorder + scoreInfosHeight)));
    scoreInfos.setPosition(sf::Vector2f(whiteSpaceBorder, whiteSpaceBorder + 2 * whiteSpaceScoreInfo + 2 * boutonHeight));

    menuElements.push_back(Bouton(sf::Vector2f(whiteSpaceBorder, whiteSpaceBorder),
                                        sf::Vector2f(scoreInfosWidth, boutonHeight),
                                        18,
                                        _state));
    menuElements[0].setAction(INDEX);
    menuElements[0].setText("Pause");


    menuElements.push_back(Bouton(sf::Vector2f(whiteSpaceBorder, whiteSpaceBorder + whiteSpaceScoreInfo + boutonHeight),
                                        sf::Vector2f(scoreInfosWidth, boutonHeight),
                                        18,
                                        &_replay));   // à changer
    menuElements[1].setAction(1);    // à changer
    menuElements[1].setText("Rejouer");




    restartGame();

    setPause((*state != GAME));




    scoreInfosBefore.setText(L"Partie précédente :  \nScore : -\nLignes : -\nNiveau : -\nTetrominos : -\nTemps : -");





}

Game::~Game() {}


void Game::onEvent(sf::Event & event)
{
    Menu::onEvent(event);

    // le jeu ignore le clique si il a été effectué sur un bouton
    if (event.type == sf::Event::MouseButtonPressed)
        for (unsigned int i=0; i<menuElements.size(); i++)
            if (menuElements[i].isHover() || menuElements[i].isClicked())
                return;
    if (event.type == sf::Event::MouseButtonReleased && *_state != GAME)
    {
        setPause(true);
        return;
    }


    switch(event.type)
    {
        case sf::Event::KeyPressed:
            if (!_AIActualPlaying)
            {
                if(event.key.code == _evenement->getEventKey("Pause")){
                    setPause(true);
                    *_state = INDEX;
                }

                if(event.key.code == _evenement->getEventKey("Gauche")){
                    if (matrix.moveLeft())
                        initTimeoutOnMove();
                }

                if(event.key.code == _evenement->getEventKey("Droite")){
                    if(matrix.moveRight())
                        initTimeoutOnMove();
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
                    if(matrix.rotateLeft())
                        initTimeoutOnMove();
                }
                if(event.key.code == _evenement->getEventKey("Rotation Droite"))
                {
                    if(matrix.rotateRight())
                        initTimeoutOnMove();
                }
                if(event.key.code == sf::Keyboard::Space)   // à définir dans la configuration des touches
                {
                    if(holdTetromino())
                        setTimeLastMoveDown();
                }
            }

            if(event.key.code == sf::Keyboard::F8)
            {
                _AIPlay = !_AIPlay;
            }
            if(event.key.code == sf::Keyboard::F9)
            {
                _AINbTetromino = 1;
            }
            if(event.key.code == sf::Keyboard::F10)
            {
                _AINbTetromino = 2;
            }
            if(event.key.code == sf::Keyboard::F11)
            {
                _AINbTetromino = 3;
            }
            if(event.key.code == sf::Keyboard::F12)
            {
                _AINbTetromino = 4;
            }

        break;
        case sf::Event::MouseMoved:
            if(!_gameConfig->get3DAutorotation() && _gameConfig->get3DMode()){
                _oGL->onEvent(event);
                return;
            }
            if (!_gameConfig->getUseMouse())
                return;
            if (matrix.mouseLeftRight(event))
                initTimeoutOnMove();
        break;
        case sf::Event::MouseButtonPressed:
            if (!_gameConfig->getUseMouse() || _gameConfig->get3DMode())
                return;
            switch(event.mouseButton.button)
            {
                case sf::Mouse::Left:
                    if(matrix.rotateLeft())
                        initTimeoutOnMove();
                break;
                case sf::Mouse::Right:
                    if(matrix.rotateRight())
                        initTimeoutOnMove();
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


bool Game::nextPiece(bool cancelCountTetromino = false)
{
    Tetromino p = nextTetromino[0].getPiece();

    if (!matrix.newPiece(p))
    {
        return false;
    }


    canHoldTetromino = true;


    for (int i=0; i<NB_NEXT_TETROMINO; i++)
    {
        if (i < NB_NEXT_TETROMINO - 1)
        {

            Tetromino t = nextTetromino[i+1].getPiece();
            nextTetromino[i].newPiece(t);
        }
        else
            nextTetromino[i].newPiece(*(new Tetromino(tetrominoRand.getTetrominoType(), 0, sf::Vector2i(0, 0))));
    }


    if (!cancelCountTetromino) _nb_tetromino++;
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


    tetrominoRand.regen();


    matrix.newPiece(*(new Tetromino(tetrominoRand.getTetrominoType(), 0)));
    if (_score > 0)
        scoreInfosBefore.setText(L"Partie précédente :  \nScore : "+ to_string(_score) +"\n"+
                                 "Lignes : "+to_string(_nb_line)+"\n"+
                                 "Niveau : "+to_string(getLevel())+"\n"+
                                 "Tetrominos : "+to_string(_nb_tetromino)+"\n"+
                                 "Temps : "+formattedDuration(getGameTime(), 1));

    for (int i=0; i<NB_NEXT_TETROMINO; i++)
    {
        nextTetromino[i].newPiece(*(new Tetromino(tetrominoRand.getTetrominoType(), 0, sf::Vector2i(0, 0))));
    }



    RecordLine record;
    string name = _gameConfig->getNickName();
    for (unsigned int i=0; i<29 && i<name.size(); i++)
        record.name[i] = name[i];
    record.name[(name.size()<29)?name.size():29] = '\0';
    record.points = _score;
    record.lines = _nb_line;
    record.tetrominos = _nb_tetromino;
    record.time = lrint(getGameTime().asSeconds());
    _scores->addScore(record);
    if (_gameConfig->getOnlineScore() && _score > 0)
        _scoreSender.addDataToFinishGame(record);
    else
        _scoreSender.clearData();

    _nb_line = _score = 0;
    _nb_tetromino = 1;
    gameClock.restart();
    totalPauseTime = sf::Time::Zero;

    holdedTetromino.clearPiece();
    hasHoldedTetromino = false;
    canHoldTetromino = true;
    _AIActualPlaying = _AIPlay;
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

    if (getPause())
        setPause(false);

    if (_AIActualPlaying)
    {
        TetrisAI ai((LogicalTetrisBoard) matrix);
        for (unsigned int i=0; i<_AINbTetromino-1 && i<nextTetromino.size(); i++)
            ai.addNextTetromino(nextTetromino[i].getPiece());
        Tetromino result = ai.getTetrominoWithBestPosition();
    }

    if (!matrix.pieceIsActive())
    {   // passage à la pièce suivante
        int new_del_line = matrix.fullLinesClear(&_explosions);
        int old_score = _score;
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

        if (!_AIActualPlaying)
            _scoreSender.addDataInfoNextPiece(_score, _score - old_score, _nb_tetromino,
                                              getGameTime(), _nb_line,
                                              new_del_line, _nb_manual_down,
                                              matrix.getPieceCourrante());

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



    scoreInfos.setText("Partie en cours :    \nScore : "+to_string(_score)+"\n"+
                       "Lignes : "+to_string(_nb_line)+"\n"+
                       "Niveau : "+to_string(getLevel())+"\n"+
                       "Tetrominos : "+to_string(_nb_tetromino)+"\n"+
                       "Temps : "+formattedDuration(getGameTime(), 1)+"");
    _explosions.update();

    matrix.dessinePieceCourrante(_gameConfig->getDrawGhost());

    if(_gameConfig->get3DMode())
        _oGL->preDraw();//Pré-dessinage de la scène 3D

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
    Menu::draw(target, states);

    if (!_gameConfig->get3DMode())
        target.draw(matrix, states);


    for (int i = 0; i<NB_NEXT_TETROMINO; i++)
    {
        target.draw(nextTetromino[i], states);
    }
    for (unsigned int i = 0; i<textTetrominoBoard.size(); i++)
    {
        target.draw(textTetrominoBoard[i], states);
    }
    target.draw(holdedTetromino, states);
    target.draw(scoreInfos, states);
    target.draw(scoreInfosBefore, states);
    if (!_gameConfig->get3DMode() && _gameConfig->getDrawExplosions())
        target.draw(_explosions, states);
}
