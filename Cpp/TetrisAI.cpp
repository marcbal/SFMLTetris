#include "TetrisAI.hpp"

TetrisAI::TetrisAI(LogicalTetrisBoard initial_board, bool type_AI):
    tetrominoQueue()
{
    _typeAI_perso = type_AI;
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


                    BoardState state;
                    state.board = boardTestPosition;
                    state.tetrominos = previous_state.tetrominos;
                    state.tetrominos.push_back(boardTestPosition.getPieceCourrante());


                    // calcul de la valeur de l'état en cours
                    // et en profite pour fullLinesClear() sur le board
                    setValueForBoardState(state, previous_state);

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



void TetrisAI::setValueForBoardState(BoardState & state, const BoardState & previous_state)
{
    // une ancienne implémentation de ma part, elle pouvait faire une centaine de lignes à peu près, en utilisant
    // la pièce suivante
    if (_typeAI_perso)
    {
        int nbDelLines = state.board.fullLinesClear();

        state.value = previous_state.value;
        state.value -= 1000 * (state.board.getHigherFilledCell() - previous_state.board.getHigherFilledCell());
        state.value -= 50 * (state.board.getNbrOfEmptyField() - previous_state.board.getNbrOfEmptyField());
        state.value += 10 * nbDelLines;
        state.value += 5 * state.tetrominos[0].getPosition().y;

        return;
    }











    /*
    Le code qui suit est basé sur la fonction d'évaluation codé initialement par
    Pierre Dellacherie (France) (E-mail : dellache@club-internet.fr) en Pascal, puis adapté
    en C++ par Colin Fahey (http://www.colinfahey.com/tetris/tetris.html). Je me suis basé sur la version c++.
    L'algorithme de Pierre Dellacherie est connu pour être un des plus efficace au monde, avec en moyenne
    650 000 lignes complétés par parties.

    Il est important ici de préciser que seul la partie "évaluation d'un état" (c'est à dire ce qui suit)
    est basé sur cet algorithme.

    L'évaluation ne se fait que sur la pièce courrante, mais le fait de prendre toutes les pièces en compte
    est important car il peut y avoir des résultats inatendu par rapport à mon code.


    Le mémoire de Christophe Thiery intitulé "Contrôle optimal stochastique et le jeu Tetris"
        http://hal.archives-ouvertes.fr/docs/00/17/32/48/PDF/rapport_master_tetris.pdf (page 8-9)
    explique, dans un tableau synthétique, les critères de selections utilisés par Dellacherie.

    */


    int   erodedPieceCellsMetric = 0;
    int   boardRowTransitions    = 0;
    int   boardColTransitions    = 0;
    int   boardBuriedHoles       = 0;
    int   boardWells             = 0;




    // hauteur de la pièce posée (la moyenne entre la case la plus haute et la plus basse)
    double landingHeight = state.board.getPieceCourrante().getVerticalMidpoint();






    // ici, on s'attaque aux lignes détruites
    // et au nombre de case détruites appartenant à la dernière pièce posée
    LogicalTetrisBoard boardBeforeDelLines = state.board;
    int completedRows = state.board.fullLinesClear();
    if (completedRows > 0)
    {
        int pieceCellsEliminated = boardBeforeDelLines.getNbPieceCellsEliminated();
        erodedPieceCellsMetric = completedRows * pieceCellsEliminated;
    }




    // on s'occupe ici des transitions : cases vides / cases pleines
    // d'abord ligne par ligne
    boardRowTransitions = 2 * (BOARD_HEIGHT - state.board.getHigherFilledCell());
    for (int y = BOARD_HEIGHT - 1; y >= BOARD_HEIGHT - state.board.getHigherFilledCell(); y--)
        boardRowTransitions += state.board.getTransitionCountForRow(y);
    // puis colonnes par colonnes
    for (int x = 0; x < BOARD_WIDTH; x++)
        boardColTransitions += state.board.getTransitionCountForColumn(x);





    // on compte maintenant le nombre de cases vides
    boardBuriedHoles = state.board.getNbrOfEmptyField();




    // finalement, on s'occupe des puits profonds :
    /* "Un puits est une succession de cellules vides et non recouvertes dans la même colonne
        et telles quel leurs cases voisines à gauche et à droite soient toutes les deux pleines.
        Les puits profonds sont pénalisants car ils obligent à attendre une barre verticale."
        (Extrait de Contrôle optimal stochastique et le jeu de Tetris, de Christophe Thiery,
         annotation 1 page 33) */

    for (int x = 0; x < BOARD_WIDTH; x++)
        boardWells += state.board.getAllWellsForColumn(x);



    state.board.drawConsole();
    // rassemblement des résultats
    state.value  =  0.0;    // à changer pour prendre en compte les pièces précédentes
    cout << state.value << endl;
    state.value += -1.0 * landingHeight;
    cout << "          hauteur piece " << landingHeight << endl;
    state.value +=  1.0 * erodedPieceCellsMetric;
    cout << "nbligne * nb cell piece " << erodedPieceCellsMetric << endl;
    state.value += -1.0 * boardRowTransitions;
    cout << "         row transition " << boardRowTransitions << endl;
    state.value += -1.0 * boardColTransitions;
    cout << "      column transition " << boardColTransitions << endl;
    state.value += -4.0 * boardBuriedHoles;
    cout << "               nb trous " << boardBuriedHoles << endl;
    state.value += -1.0 * boardWells;
    cout << "          hauteur puits " << boardWells << endl;
    cout << "---------- Sous Total : " << state.value << endl;


    /* l'algorithme de Dellacherie gère un système de priorité, dans le cas ou on a des
     valeurs identiques : ici, pour l'adapter à notre code, on multiplie par 1000 la
     valueur totale obtenu au dessus, puis on ajoute à cette valeur le niveau de
     priorité, d'un ordre de grandeur bien plus faible */

    state.value *= 1000.0;
    cout << "--- 1000 * Sous Total : " << state.value << endl;

    int priority = 100 * abs(state.board.getPieceCourrante().getPosition().x - INIT_POS_X);
    if (state.board.getPieceCourrante().getPosition().x < INIT_POS_X)
        priority += 10;
    priority -= state.board.getPieceCourrante().getOrientation();
    cout << "               priority " << priority << endl;

    state.value += priority;
    cout << "--------------  TOTAL : " << state.value << endl;


}


