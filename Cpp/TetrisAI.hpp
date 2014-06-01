#ifndef TETRISAI_H
#define TETRISAI_H

#include "headers.hpp"

#include "Tetromino.hpp"
#include "TetrisBoard.hpp"





struct BoardState
{
    vector<Tetromino> tetrominos;
    LogicalTetrisBoard board;
    float value = 0.f;
};





class TetrisAI
{
    public:
        TetrisAI(LogicalTetrisBoard initial_board, bool type_AI);
        virtual ~TetrisAI();

        void addNextTetromino(Tetromino t);

        Tetromino getTetrominoWithBestPosition();
    protected:
    private:

        void setValueForBoardState(BoardState & state, const BoardState & previous_state);



        vector<Tetromino> tetrominoQueue;

        vector<vector<BoardState> > boardDatas;

        bool _typeAI_perso;
};

#endif // TETRISAI_H

