#ifndef GAME_H
#define GAME_H


#include "headers.hpp"

#include "Bouton.hpp"
#include "TetrisBoard.hpp"
#include "Tetromino.hpp"
#include "ScreenElement.hpp"
#include "Application.hpp"
#include "NextTetrominoBoard.hpp"
#include "fn_string.hpp"
#include "fn_time.hpp"
#include "Evenement.hpp"
#include "ExplosionManager.hpp"
#include "Scores.hpp"
#include "TetrominoRandomizer.hpp"
#include "ScoreWebSender.hpp"


using namespace std;
using namespace sf;


class Game : public ScreenElement
{
    private:




        Evenement * _evenement;

        TetrisBoard matrix;
        vector<NextTetrominoBoard> nextTetromino;

        Bouton scoreInfos;
        Bouton scoreInfosBefore;

        char * _state;

        bool _pause;


        int _score;
        int _nb_line;
        int _nb_manual_down;
        int _nb_tetromino;

        sf::Time timeLastMoveDown;
        sf::Clock gameClock;
        sf::Time totalPauseTime;
        sf::Time lastPauseStartingTime;

        ExplosionManager _explosions;

        Scores * _scores;
        ScoreWebSender _scoreSender;

        TetrominoRandomizer tetrominoRand;


        bool nextPiece();

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:
        Game(sf::Vector2i * window_size, char *state, Evenement * evenement, Scores * scores);
        virtual ~Game();


        int getLevel();

        void setTimeLastMoveDown();

        sf::Time getGameTime();

        void setPause(bool p);
        bool getPause();

        void restartGame();


        // permet de prendre en compte le lag dans la descente de la pièce
        sf::Time getTimeAutoMoveDown();


        virtual void onEvent(sf::Event & event);


        virtual void update();
};

#endif // GAME_H
