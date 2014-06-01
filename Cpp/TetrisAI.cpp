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
    for (unsigned int p=0; p<tetrominoQueue.size(); p++)
    {
        vector<BoardState> new_states;
        if (boardDatas[p].size() == 0)
        {
            break;
        }
        Tetromino actualTetromino = tetrominoQueue[p];

        // pour chaque tétromino, on les testes sur les cas possibles du tétromino précédent
        for (unsigned int q=0; q<boardDatas[p].size(); q++)
        {

            BoardState previous_state = boardDatas[p][q];
            Tetromino tetrominoTest = actualTetromino;

            for (int r=0; r<4; r++)
            {
                // on calcule les extrèmes (gauche et droite) pour les déplacements de la pièce actuelle
                Tetromino tetrominoTestOrientation = Tetromino(tetrominoTest.getTypePiece(), r, tetrominoTest.getPosition());
                LogicalTetrisBoard boardTestOrientation = previous_state.board;
                if (!boardTestOrientation.newPiece(tetrominoTestOrientation, false))
                    continue;   // on prends en compte la possibilité qu'on ne puisse pas positionner le tetromino dans ce sens
                while (boardTestOrientation.moveLeft());
                int pos_left = boardTestOrientation.getPieceCourrante().getPosition().x;
                while (boardTestOrientation.moveRight());
                int pos_right = boardTestOrientation.getPieceCourrante().getPosition().x;

                // on va d'un extrème à l'autre, pour effectuer toute la largeur possible;
                for (int s=pos_left; s<=pos_right; s++)
                {
                    // on est parti pour tester une possibilité
                    LogicalTetrisBoard boardTestPosition = boardTestOrientation;

                    if (!boardTestPosition.newPiece(Tetromino(tetrominoTestOrientation.getTypePiece(),
                                                              r, sf::Vector2i(s,
                                                                              tetrominoTestOrientation.getPosition().y)), false))
                        continue;   // on passe à la position suivante si on peut pas ici

                    boardTestPosition.HardDrop();

                    int nbDelLines = boardTestPosition.fullLinesClear();


                    BoardState state;
                    state.board = boardTestPosition;
                    state.tetrominos = previous_state.tetrominos;
                    state.tetrominos.push_back(boardTestPosition.getPieceCourrante());


                    // calcul de la valeur de l'état en cours
                    setValueForBoardState(state, previous_state, nbDelLines);

                    if (p==tetrominoQueue.size()-1)
                    {
                        if (new_states.size() == 0 || state.value > new_states[new_states.size()-1].value)
                            new_states.push_back(state);
                    }
                    else
                        new_states.push_back(state);
                }
            }
        }

        boardDatas.push_back(new_states);
    }

    if (boardDatas[boardDatas.size()-1].size() == 0 ||
        boardDatas[boardDatas.size()-1][boardDatas[boardDatas.size()-1].size()-1].tetrominos.size() == 0)
    {
        boardDatas[0][0].board.HardDrop();
        return boardDatas[0][0].board.getPieceCourrante();
    }
    return boardDatas[boardDatas.size()-1][boardDatas[boardDatas.size()-1].size()-1].tetrominos[0];

}



void TetrisAI::setValueForBoardState(BoardState & state, const BoardState & previous_state, int nbDelLines)
{
    state.value = previous_state.value;


    state.value -= 1000 * (state.board.getHigherFilledCell() - previous_state.board.getHigherFilledCell());

    state.value -= 50 * (state.board.getNbrOfEmptyField() - previous_state.board.getNbrOfEmptyField());


    state.value += 10 * nbDelLines;

    state.value += 5 * state.tetrominos[0].getPosition().y;





}


