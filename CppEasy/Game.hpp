#ifndef GAME_H
#define GAME_H


#include "headers.hpp"


#include "TetrisBoard.hpp"
#include "Tetromino.hpp"
#include "TetrominoBoard.hpp"
#include "fn_string.hpp"
#include "fn_time.hpp"


using namespace std;
using namespace sf;









class Game : public sf::Drawable
{
    private:
        sf::Vector2i * _window_size;


        TetrisBoard matrix;
        TetrominoBoard nextTetromino;
        vector<sf::Text> textTetrominoBoard;
        sf::Text scoreInfos;
        sf::Text scoreInfosBefore;
        sf::Text commandes;

        TetrominoBoard holdedTetromino;
        bool hasHoldedTetromino;
        bool canHoldTetromino;

        char _replay;

    public:


        int _score;
        int _nb_line;
        int _nb_manual_down;
        int _nb_tetromino;

        sf::Time timeLastMoveDown;
        sf::Clock gameClock;
    private:


        bool nextPiece(bool cancelCountTetromino);

        bool holdTetromino();

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:
        Game(sf::Vector2i * window_size);
        virtual ~Game();


        int getLevel();

        void setTimeLastMoveDown();
        void initTimeoutOnMove();

        sf::Time getGameTime();


        void restartGame();


        // permet de prendre en compte le lag dans la descente de la pièce
        sf::Time getTimeAutoMoveDown();


        virtual void onEvent(sf::Event & event);


        virtual void update();
};

#endif // GAME_H
