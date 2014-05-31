#include "TetrisAI.hpp"

TetrisAI::TetrisAI(LogicalTetrisBoard initial_board):
    tetrominoQueue()
{
    BoardState init;
    init.board = initial_board;
    init.tetrominos.clear();
    vector<BoardState> init_v;
    init_v.push_back(init);
    boardDatas.push_back(init_v);

    Tetromino t = initial_board.getPieceCourrante();
    addNextTetromino(t);
}

TetrisAI::~TetrisAI() {}



void TetrisAI::addNextTetromino(Tetromino t)
{
    tetrominoQueue.push_back(t);
}




Tetromino TetrisAI::getTetrominoWithBestPosition()
{
    // on parcours tout les tétrominos de la file
    for (int p=0; p<tetrominoQueue.size(); p++)
    {
        Tetromino actualTetromino = tetrominoQueue[p];
        vector<BoardState> new_states;

        // pour chaque tétromino, on les testes sur les cas possibles du tétromino précédent
        for (int q=0; q<boardDatas[p].size(); q++)
        {

            BoardState previous_state = boardDatas[p][q];
            Tetromino tetrominoTest = actualTetromino;

            for (int r=0; r<4; r++)
            {
                // on calcule les extrèmes (gauche et droite) pour les déplacements de la pièce
                Tetromino tetrominoTestOrientation = Tetromino(tetrominoTest.getTypePiece(), r, tetrominoTest.getPosition());
                LogicalTetrisBoard boardTestOrientation = previous_state.board;
                boardTestOrientation.newPiece(tetrominoTestOrientation, false);
                while (boardTestOrientation.moveLeft());
                int pos_left = boardTestOrientation.getPieceCourrante().getPosition().x;
                while (boardTestOrientation.moveRight());
                int pos_right = boardTestOrientation.getPieceCourrante().getPosition().x;

            }
        }

        boardDatas.push_back(new_states);
    }


    // ------------------------------------
    // ----------- temporaire -------------
    // ------------------------------------
    return tetrominoQueue[0];
    // ------------------------------------

}
