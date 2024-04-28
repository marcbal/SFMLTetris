#ifndef GAME_H
#define GAME_H


#include "headers.hpp"


#include "Menu.hpp"
#include "Bouton.hpp"
#include "TetrisBoard.hpp"
#include "Tetromino.hpp"
#include "ScreenElement.hpp"
#include "NextTetrominoBoard.hpp"
#include "fn_string.hpp"
#include "fn_time.hpp"
#include "Evenement.hpp"
#include "ExplosionManager.hpp"
#include "Scores.hpp"
#include "TetrominoRandomizer.hpp"
#include "ScoreWebSender.hpp"
#include "OpenGL_Manager.hpp"
#include "GameConfiguration.hpp"
#include "AudioConfiguration.hpp"
#include "TetrisAI.hpp"


using namespace std;
using namespace sf;









class Game : public Menu
{
    private:


        Evenement * _evenement;
        OpenGL_Manager * _oGL;
        TetrisBoard matrix;
        vector<NextTetrominoBoard> nextTetromino;
        vector<sf::Text> textTetrominoBoard;

        NextTetrominoBoard holdedTetromino;
        bool hasHoldedTetromino;
        bool canHoldTetromino;

        Bouton scoreInfos;
        Bouton scoreInfosBefore;

        char * _state;
        char _replay;


        bool _pause;

    public:
        bool _AIPlay;
        bool _AIActualPlaying;
        unsigned int _AINbTetromino;


        int _score;
        int _nb_line;
        int _nb_manual_down;
        int _nb_tetromino;

        sf::Time timeLastMoveDown;
        sf::Clock gameClock;
        sf::Time totalPauseTime;
        sf::Time lastPauseStartingTime;
    private:
        ExplosionManager _explosions;

        Scores * _scores;
        ScoreWebSender _scoreSender;

        GameConfiguration * _gameConfig;

        AudioConfiguration * _audio;

        TetrominoRandomizer tetrominoRand;


        bool nextPiece(bool cancelCountTetromino);

        bool holdTetromino();

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:
        Game(sf::Vector2i * window_size,
             char * state,
             Evenement * evenement,
             Scores * scores,
             OpenGL_Manager * oGL,
             GameConfiguration * gameConfig,
             AudioConfiguration * audio);
        virtual ~Game();


        int getLevel();

        void setTimeLastMoveDown();
        void initTimeoutOnMove();

        sf::Time getGameTime();

        void setPause(bool p);
        bool getPause();

        void restartGame(bool init = false);


        // permet de prendre en compte le lag dans la descente de la pièce
        sf::Time getTimeAutoMoveDown();


        virtual void onEvent(sf::Event & event);


        virtual void update();
};

#endif // GAME_H
