#include "LogicalTetrisBoard.hpp"

LogicalTetrisBoard::LogicalTetrisBoard() :
    pieceCourrante(0, 0, sf::Vector2i(INIT_POS_X, INIT_POS_Y))
{
    pieceCouranteActive = true;
    clearBoard();
}

LogicalTetrisBoard::~LogicalTetrisBoard() {}



bool LogicalTetrisBoard::newPiece(Tetromino p, bool init_pos)
{
    pieceCouranteActive = true;
    pieceCourrante = p;
    if (init_pos)
        pieceCourrante.setPosition(sf::Vector2i(INIT_POS_X, INIT_POS_Y));
    if (verifierPlacementPiece(pieceCourrante.getPosition(), pieceCourrante.getOrientation()))
        return true;
    else
    {
        pieceCouranteActive = false;
        return false;
    }
}


Tetromino & LogicalTetrisBoard::getPieceCourrante()
{
    return pieceCourrante;
}


void LogicalTetrisBoard::clearBoard()
{
    for (int i=0; i<BOARD_WIDTH; i++)
        for (int j=-2; j<BOARD_HEIGHT; j++)
            setBoardData(i, j, 0);
    pieceCouranteActive = false;
}



int LogicalTetrisBoard::HardDrop()
{
    int nb_down = 0;
    // ancienne implémentation : difficilement optimisable mais très facile à comprendre
    //while(MoveDown()) nb_down++;

    // nouvelle implémentation : tentative d'optimisation
    sf::Vector2i new_pos = pieceCourrante.getPosition();
    sf::Clock c;
    while (verifierPlacementPiece(new_pos + sf::Vector2i(0, 1), pieceCourrante.getOrientation()))
    {
        nb_down++;
        new_pos.y++;
    }
    effacePieceCourrante();
    pieceCourrante.setPosition(new_pos);
    dessinePieceCourrante(false);
    fixPiece();

    // ------------------------------
    return nb_down;
}




bool LogicalTetrisBoard::MoveDown()
{
    sf::Vector2i new_pos = pieceCourrante.getPosition() + sf::Vector2i(0, 1);
    if (verifierPlacementPiece(new_pos, pieceCourrante.getOrientation()))
    {
        pieceCourrante.setPosition(new_pos);
        return true;
    }
    else
    {
        effacePieceCourrante();
        dessinePieceCourrante(false);
        fixPiece();
        return false;
    }
}
bool LogicalTetrisBoard::MoveDownCheck()
{
    return verifierPlacementPiece(pieceCourrante.getPosition() + sf::Vector2i(0, 1),
                                  pieceCourrante.getOrientation());
}


bool LogicalTetrisBoard::moveLeft()
{

    sf::Vector2i new_pos = pieceCourrante.getPosition() + sf::Vector2i(-1, 0);
    if (verifierPlacementPiece(new_pos, pieceCourrante.getOrientation()))
    {
        pieceCourrante.setPosition(new_pos);
        return true;
    }
    return false;
}
bool LogicalTetrisBoard::moveRight()
{

    sf::Vector2i new_pos = pieceCourrante.getPosition() + sf::Vector2i(1, 0);
    if (verifierPlacementPiece(new_pos, pieceCourrante.getOrientation()))
    {
        pieceCourrante.setPosition(new_pos);
        return true;
    }
    return false;
}
bool LogicalTetrisBoard::rotateLeft()
{
    int new_rotation = (pieceCourrante.getOrientation()+1)%4;
    sf::Vector3i new_pos = SRSRotate(pieceCourrante.getOrientation(), new_rotation);
    if (new_pos.z == pieceCourrante.getOrientation())
        return false;
    pieceCourrante.setOrientation(new_rotation);
    pieceCourrante.setPosition(pieceCourrante.getPosition()+
                               sf::Vector2i(new_pos.x, new_pos.y));
    return true;
}
bool LogicalTetrisBoard::rotateRight()
{
    int new_rotation = (pieceCourrante.getOrientation()-1)%4;
    sf::Vector3i new_pos = SRSRotate(pieceCourrante.getOrientation(), new_rotation);
    if (new_pos.z == pieceCourrante.getOrientation())
        return false;
    pieceCourrante.setOrientation(new_rotation);
    pieceCourrante.setPosition(pieceCourrante.getPosition()+
                               sf::Vector2i(new_pos.x, new_pos.y));
    return true;
}






void LogicalTetrisBoard::fixPiece()
{

    pieceCouranteActive = false;


    for (int i=0; i<BOARD_WIDTH; i++)
        for (int j=-2; j<BOARD_HEIGHT; j++)
            if (getBoardData(i, j) >= 20 && getBoardData(i, j) <= 26)
                setBoardData(i, j, getBoardData(i, j) - 10);

}







void LogicalTetrisBoard::dessinePieceCourrante(bool drawGhost)
{
    if (!pieceCouranteActive)
        return;

    // on positionne et trace le fantome de la pièce courante
    if (drawGhost)
    {
        int y = pieceCourrante.getPosition().y;
        while (verifierPlacementPiece(sf::Vector2i(pieceCourrante.getPosition().x, y+1), pieceCourrante.getOrientation()))
            y++;
        sf::Vector2i fpos = sf::Vector2i(pieceCourrante.getPosition().x, y);
        MatrixShape fshape = pieceCourrante.getMatrixShape();
        for (int i=0; i<4; i++)
            for (int j=0; j<4; j++)
                if (fshape[i][j])
                    setBoardData(fpos.x + i,
                                 fpos.y + j,
                                 pieceCourrante.getTypePiece() + 30);

    }
    // ------------------------------


    sf::Vector2i pos = pieceCourrante.getPosition();
    MatrixShape shape = pieceCourrante.getMatrixShape();
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            if (shape[i][j])
                setBoardData(pos.x + i,
                             pos.y + j,
                             pieceCourrante.getTypePiece() + 20);

}


bool LogicalTetrisBoard::pieceIsActive()
{
    return pieceCouranteActive;
}


void LogicalTetrisBoard::effacePieceCourrante()
{
    for (int i=0; i<BOARD_WIDTH; i++)
        for (int j=-2; j<BOARD_HEIGHT; j++)
            if ((getBoardData(i, j) >= 20 && getBoardData(i, j) <= 26) || (getBoardData(i, j) >= 30 && getBoardData(i, j) <= 36))
                setBoardData(i, j, 0);
}

int LogicalTetrisBoard::getBoardData(int x, int y) const
{
    if (x<0 || x>=BOARD_WIDTH || y<-2 || y>=BOARD_HEIGHT)
        return 0;
    if (y<0) return areasup[x][y+2];
    else return area[x][y];
}



void LogicalTetrisBoard::setBoardData(int x, int y, int data)
{
    if (x<0 || x>=BOARD_WIDTH || y<-2 || y>=BOARD_HEIGHT)
        return;

    if (y<0)
    {
        areasup[x][y+2] = data;
        return;
    }


    area[x][y] = data;

}





int LogicalTetrisBoard::fullLinesClear()
{
    int nbr_lines = 0;
    for (int i=0; i<BOARD_HEIGHT; i++)
    {   // on parcours les lignes de haut en bas
        bool full = true;
        // on vérifie si la ligne est complète
        for (int j=0; j<BOARD_WIDTH && full; j++)
            if (getBoardData(j, i) < 10)
                full = false;

        if (full)
        {
            nbr_lines++;
            // on efface la ligne
            for (int j=0; j<BOARD_WIDTH; j++)
                setBoardData(j, i, 0);

            // on décale tout ce qui se trouve au dessus
            for (int j=i; j>-2; j--) // on remonte les lignes
                for (int k=0; k<BOARD_WIDTH; k++)
                    setBoardData(k, j, getBoardData(k, j-1));

            // on efface la ligne tout en haut
            for (int j=0; j<BOARD_WIDTH; j++)
                setBoardData(j, -2, 0);

        }
    }
    return nbr_lines;
}


int LogicalTetrisBoard::getNbPieceCellsEliminated()
{
    int nbr_cells = 0;
    MatrixShape pieceShape = pieceCourrante.getMatrixShape();
    for (int i=0; i<BOARD_HEIGHT; i++)
    {   // on parcours les lignes de haut en bas
        bool full = true;
        // on vérifie si la ligne est complète
        for (int j=0; j<BOARD_WIDTH && full; j++)
            if (getBoardData(j, i) < 10)
                full = false;

        if (full && i>=pieceCourrante.getPosition().y && i<pieceCourrante.getPosition().y+4)
        {
            int piecePosY = i-pieceCourrante.getPosition().y;
            for (int j=0; j<4; j++)
            {
                if (pieceShape[j][piecePosY])
                    nbr_cells++;
            }
        }
    }
    return nbr_cells;
}


int LogicalTetrisBoard::getTransitionCountForRow(int y)
{
    if (y < -2 || y >= BOARD_HEIGHT)
        return 0;
    int transitionCount = 0;
    for (int i=0; i<BOARD_WIDTH-1; i++)
    {
        if ((getBoardData(i, y) >= 10 && getBoardData(i+1, y) < 10)
            || (getBoardData(i, y) < 10 && getBoardData(i+1, y) >= 10))
            transitionCount++;
    }
    if (getBoardData(0, y) < 10)  // l'extérieur à gauche est supposé pleine
        transitionCount++;
    if (getBoardData(BOARD_WIDTH-1, y) < 10)  // l'extérieur à droite est supposé pleine
        transitionCount++;
    return transitionCount;
}




int LogicalTetrisBoard::getTransitionCountForColumn(int x)
{
    if (x < 0 || x >= BOARD_WIDTH)
        return 0;
    int transitionCount = 0;
    for (int j=-2; j<BOARD_HEIGHT-1; j++)
    {
        if ((getBoardData(x, j) >= 10 && getBoardData(x, j+1) < 10)
            || (getBoardData(x, j) < 10 && getBoardData(x, j+1) >= 10))
            transitionCount++;
    }
    if (getBoardData(x, -2) >= 10)  // l'extérieur au dessus est supposé vide
        transitionCount++;
    if (getBoardData(x, BOARD_HEIGHT-1) < 10)  // l'extérieur en dessous est supposé pleine
        transitionCount++;
    return transitionCount;
}





int LogicalTetrisBoard::getAllWellsForColumn(int x)
{
    if (x < 0 || x >= BOARD_WIDTH)
        return 0;
    int valeurPuit = 0;
    for (int j=-2; j<BOARD_HEIGHT; j++)
    {
        bool left = true, right = true;
        // on récupère
        if (x >= 1)
            left = (getBoardData(x-1, j) >= 10);
        if (x < BOARD_WIDTH-1)
            right = (getBoardData(x+1, j) >= 10);

        if (left && right && getBoardData(x, j) < 10)
        {
            for (int k=j; k<BOARD_HEIGHT && getBoardData(x, k) < 10; k++)
            {
                valeurPuit++;
            }
        }
    }
    return valeurPuit;
}



bool LogicalTetrisBoard::verifierPlacementPiece(sf::Vector2i pos, int o)
{
    // tests si la forme sors totalement de l'écran
    if (pos.x > BOARD_WIDTH || pos.y > BOARD_HEIGHT || pos.y+4 < -2 || pos.x+4 < 0)
        return false;
    // crée un tetromino de test qui correspond à la position/orientation/forme testée
    Tetromino pieceTest(pieceCourrante.getTypePiece(), o, pos);
    MatrixShape shape = pieceTest.getMatrixShape();
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            sf::Vector2i posB(pos.x + i, pos.y + j);
            if (shape[i][j] &&
                (posB.x < 0 || posB.y < -2 ||       // ici, on prends en compte que la matrice a 2 lignes invisibles au dessus
                 posB.x >= BOARD_WIDTH || posB.y >= BOARD_HEIGHT ||
                 (getBoardData(posB.x,posB.y) >= 10 && getBoardData(posB.x,posB.y) < 20)))
            {
                return false;
            }

        }

    }
    return true;
}





bool LogicalTetrisBoard::verifierDeplacementPiece(sf::Vector2i var_pos, int o)
{
    return verifierPlacementPiece(pieceCourrante.getPosition() + var_pos, o);
}






// SRS = Super Rotation System
sf::Vector3i LogicalTetrisBoard::SRSRotate(int oldOrient, int newOrient)
{


    // 0 : 0
    // L : 1
    // 2 : 2
    // R : 3

    // pour tout type de pièce, on teste l'orientation sans déplacement
    // le test réussi forcément pour la piéce O
    if(pieceCourrante.getTypePiece() == 0 ||
                verifierDeplacementPiece(sf::Vector2i(0, 0), newOrient))
        return sf::Vector3i(0, 0, newOrient);

    if (pieceCourrante.getTypePiece() == 1) // I
    {
        if ((oldOrient == 2 && newOrient == 3) ||
            (oldOrient == 1 && newOrient == 0))
        {
            if (verifierDeplacementPiece(sf::Vector2i(1, 0), newOrient))
                return sf::Vector3i(1, 0, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(-2, 0), newOrient))
                return sf::Vector3i(-2, 0, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(1, 2), newOrient))
                return sf::Vector3i(1, 2, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(-2, -1), newOrient))
                return sf::Vector3i(-2, -1, newOrient);
        }
        else if ((oldOrient == 3 && newOrient == 0) ||
            (oldOrient == 2 && newOrient == 1))
        {
            if (verifierDeplacementPiece(sf::Vector2i(2, 0), newOrient))
                return sf::Vector3i(2, 0, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(-1, 0), newOrient))
                return sf::Vector3i(-1, 0, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(2, -1), newOrient))
                return sf::Vector3i(2, -1, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(-1, 2), newOrient))
                return sf::Vector3i(-1, 2, newOrient);
        }
        else if ((oldOrient == 3 && newOrient == 2) ||
            (oldOrient == 0 && newOrient == 1))
        {
            if (verifierDeplacementPiece(sf::Vector2i(-1, 0), newOrient))
                return sf::Vector3i(-1, 0, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(2, 0), newOrient))
                return sf::Vector3i(2, 0, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(-1, -2), newOrient))
                return sf::Vector3i(-1, -2, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(2, 1), newOrient))
                return sf::Vector3i(2, 1, newOrient);
        }
        else if ((oldOrient == 0 && newOrient == 3) ||
            (oldOrient == 1 && newOrient == 2))
        {
            if (verifierDeplacementPiece(sf::Vector2i(-2, 0), newOrient))
                return sf::Vector3i(-2, 0, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(1, 0), newOrient))
                return sf::Vector3i(1, 0, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(-2, 1), newOrient))
                return sf::Vector3i(-2, 1, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(1, -2), newOrient))
                return sf::Vector3i(1, -2, newOrient);
        }
    }
    else  // Z, S, L, J, T
    {
        if ((oldOrient == 2 && newOrient == 1) ||
            (oldOrient == 0 && newOrient == 1))
        {
            if (verifierDeplacementPiece(sf::Vector2i(1, 0), newOrient))
                return sf::Vector3i(1, 0, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(1, -1), newOrient))
                return sf::Vector3i(1, -1, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(0, 2), newOrient))
                return sf::Vector3i(0, 2, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(1, 2), newOrient))
                return sf::Vector3i(1, 2, newOrient);
        }
        else if ((oldOrient == 3 && newOrient == 0) ||
            (oldOrient == 3 && newOrient == 2))
        {
            if (verifierDeplacementPiece(sf::Vector2i(1, 0), newOrient))
                return sf::Vector3i(1, 0, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(1, 1), newOrient))
                return sf::Vector3i(1, 1, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(0, -2), newOrient))
                return sf::Vector3i(0, -2, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(1, -2), newOrient))
                return sf::Vector3i(1, -2, newOrient);
        }
        else if ((oldOrient == 0 && newOrient == 3) ||
            (oldOrient == 2 && newOrient == 3))
        {
            if (verifierDeplacementPiece(sf::Vector2i(-1, 0), newOrient))
                return sf::Vector3i(-1, 0, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(-1, -1), newOrient))
                return sf::Vector3i(-1, -1, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(0, 2), newOrient))
                return sf::Vector3i(0, 2, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(-1, 2), newOrient))
                return sf::Vector3i(-1, 2, newOrient);
        }
        else if ((oldOrient == 1 && newOrient == 2) ||
            (oldOrient == 1 && newOrient == 0))
        {
            if (verifierDeplacementPiece(sf::Vector2i(-1, 0), newOrient))
                return sf::Vector3i(-1, 0, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(-1, 1), newOrient))
                return sf::Vector3i(-1, 1, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(0, -2), newOrient))
                return sf::Vector3i(0, -2, newOrient);
            else if (verifierDeplacementPiece(sf::Vector2i(1, -2), newOrient))
                return sf::Vector3i(1, -2, newOrient);
        }
    }
    return sf::Vector3i(0, 0, oldOrient);
}








void LogicalTetrisBoard::drawConsole()
{
    for (int i=0; i<BOARD_HEIGHT; i++)
    {
        cout << "[";
        for (int j=0; j<BOARD_WIDTH; j++)
        {
            if (j!=0)
                cout << "|";
            cout << to_string(getBoardData(j, i), 2);
        }
        cout << "]" << endl;
    }
}




int LogicalTetrisBoard::getHigherFilledCell() const
{
    int height = 0;
    for (int i=-2; i<BOARD_HEIGHT; i++)
        for (int j=0; j<BOARD_WIDTH; j++)
            if (getBoardData(j, i)>=10 && BOARD_HEIGHT-i > height)
                height = BOARD_HEIGHT-i;
    return height;
}



int LogicalTetrisBoard::getNbrOfEmptyField() const
{
    int nb = 0;
    for (int i=0; i<BOARD_WIDTH; i++)
    {
        bool canCount = false;
        for (int j=-2; j<BOARD_HEIGHT; j++)
        {
            bool b = getBoardData(i, j) >= 10;
            if (b) canCount = true;
            else if (canCount) nb++;
        }
    }
    return nb;
}

