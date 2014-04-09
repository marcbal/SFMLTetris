#include "TetrisBoard.hpp"

TetrisBoard::TetrisBoard(sf::Vector2i * window_size) :
    boardShape(),
    shapeMatrix(BOARD_WIDTH * BOARD_HEIGHT) ,
    pieceCourrante(rand_int(0, 6), 0, sf::Vector2i(INIT_POS_X, INIT_POS_Y))
{
    clearBoard();
    pieceCouranteActive = true;


    _window_size = window_size;

    // positionnement du tetris board à l'écran
    sf::Vector2f top_left_pos((window_size->x - BOARD_WIDTH * CEIL_SIZE)/2.0,
                              (window_size->y - BOARD_HEIGHT * CEIL_SIZE)/2.0);


    boardShape.setPosition(top_left_pos);
    boardShape.setSize(sf::Vector2f(BOARD_WIDTH * CEIL_SIZE, BOARD_HEIGHT * CEIL_SIZE));
    boardShape.setFillColor(sf::Color(0, 0, 0, 192));
    boardShape.setOutlineThickness(1);
    boardShape.setOutlineColor(sf::Color(255, 255, 255, 128));

    for (int i=0; i<BOARD_WIDTH; i++)
        for (int j=0; j<BOARD_HEIGHT; j++)
        {
            shapeMatrix[i*BOARD_HEIGHT+j] = *(new sf::RectangleShape(sf::Vector2f(CEIL_SIZE, CEIL_SIZE)));
            shapeMatrix[i*BOARD_HEIGHT+j].setPosition(top_left_pos + sf::Vector2f(CEIL_SIZE*i, CEIL_SIZE*j));
            shapeMatrix[i*BOARD_HEIGHT+j].setOutlineThickness(-1);
            shapeMatrix[i*BOARD_HEIGHT+j].setOutlineColor(sf::Color(63, 63, 63, 63));
            shapeMatrix[i*BOARD_HEIGHT+j].setFillColor(sf::Color::Transparent);

        }





}

TetrisBoard::~TetrisBoard(){}




bool TetrisBoard::newPiece(Tetromino p)
{
    pieceCouranteActive = true;
    pieceCourrante = p;
    pieceCourrante.setPosition(sf::Vector2i(INIT_POS_X, INIT_POS_Y));
    if (verifierPlacementPiece(pieceCourrante.getPosition(), pieceCourrante.getOrientation()))
        return true;
    else
    {
        pieceCouranteActive = false;
        return false;
    }
}
Tetromino & TetrisBoard::getPieceCourrante()
{
    return pieceCourrante;
}

void TetrisBoard::clearBoard()
{
    for (int i=0; i<BOARD_WIDTH; i++)
        for (int j=0; j<BOARD_HEIGHT; j++)
            setBoardData(i, j, 0);
    pieceCouranteActive = false;
}
void TetrisBoard::HardDrop()
{
    bool continuer;
    do
    {
        continuer = MoveDown();
    }
    while (continuer);
}
bool TetrisBoard::MoveDown()
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
        dessinePieceCourrante();
        fixPiece();
        return false;
    }
}


void TetrisBoard::moveLeft()
{

    sf::Vector2i new_pos = pieceCourrante.getPosition() + sf::Vector2i(-1, 0);
    if (verifierPlacementPiece(new_pos, pieceCourrante.getOrientation()))
    {
        pieceCourrante.setPosition(new_pos);
    }
}
void TetrisBoard::moveRight()
{

    sf::Vector2i new_pos = pieceCourrante.getPosition() + sf::Vector2i(1, 0);
    if (verifierPlacementPiece(new_pos, pieceCourrante.getOrientation()))
    {
        pieceCourrante.setPosition(new_pos);
    }
}
void TetrisBoard::rotateLeft()
{
    int new_rotation = pieceCourrante.getOrientation()+1;
    if (verifierPlacementPiece(pieceCourrante.getPosition(), new_rotation))
    {
        pieceCourrante.setOrientation(new_rotation);
    } // suite : décalage de la pièce pour que la rotation soit effectuée
    else if (verifierPlacementPiece(pieceCourrante.getPosition()+sf::Vector2i(0, 1), new_rotation))
    {
        pieceCourrante.setOrientation(new_rotation);
        pieceCourrante.setPosition(pieceCourrante.getPosition()+sf::Vector2i(0, 1));
    }
    else if (verifierPlacementPiece(pieceCourrante.getPosition()+sf::Vector2i(-1,0), new_rotation))
    {
        pieceCourrante.setOrientation(new_rotation);
        pieceCourrante.setPosition(pieceCourrante.getPosition()+sf::Vector2i(-1,0));
    }
    else if (verifierPlacementPiece(pieceCourrante.getPosition()+sf::Vector2i(1, 0), new_rotation))
    {
        pieceCourrante.setOrientation(new_rotation);
        pieceCourrante.setPosition(pieceCourrante.getPosition()+sf::Vector2i(1, 0));
    }
    else if (verifierPlacementPiece(pieceCourrante.getPosition()+sf::Vector2i(0, -1), new_rotation))
    {
        pieceCourrante.setOrientation(new_rotation);
        pieceCourrante.setPosition(pieceCourrante.getPosition()+sf::Vector2i(0, -1));
    }
}
void TetrisBoard::rotateRight()
{

    int new_rotation = pieceCourrante.getOrientation()-1;
    if (verifierPlacementPiece(pieceCourrante.getPosition(), new_rotation))
    {
        pieceCourrante.setOrientation(new_rotation);
    } // suite : décalage de la pièce pour que la rotation soit effectuée
    else if (verifierPlacementPiece(pieceCourrante.getPosition()+sf::Vector2i(0, 1), new_rotation))
    {
        pieceCourrante.setOrientation(new_rotation);
        pieceCourrante.setPosition(pieceCourrante.getPosition()+sf::Vector2i(0, 1));
    }
    else if (verifierPlacementPiece(pieceCourrante.getPosition()+sf::Vector2i(-1,0), new_rotation))
    {
        pieceCourrante.setOrientation(new_rotation);
        pieceCourrante.setPosition(pieceCourrante.getPosition()+sf::Vector2i(-1,0));
    }
    else if (verifierPlacementPiece(pieceCourrante.getPosition()+sf::Vector2i(1, 0), new_rotation))
    {
        pieceCourrante.setOrientation(new_rotation);
        pieceCourrante.setPosition(pieceCourrante.getPosition()+sf::Vector2i(1, 0));
    }
    else if (verifierPlacementPiece(pieceCourrante.getPosition()+sf::Vector2i(0, -1), new_rotation))
    {
        pieceCourrante.setOrientation(new_rotation);
        pieceCourrante.setPosition(pieceCourrante.getPosition()+sf::Vector2i(0, -1));
    }
}




void TetrisBoard::fixPiece()
{

    pieceCouranteActive = false;


    for (int i=0; i<BOARD_WIDTH; i++)
        for (int j=0; j<BOARD_HEIGHT; j++)
            if (getBoardData(i, j) >= 20 && getBoardData(i, j) <= 26)
                setBoardData(i, j, getBoardData(i, j) - 10);

}


void TetrisBoard::dessinePieceCourrante()
{
    if (!pieceCouranteActive)
        return;

    sf::Vector2i pos = pieceCourrante.getPosition();
    bool ** shape = pieceCourrante.getMatrixShape();
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            if (shape[i][j])
                setBoardData(pos.x + i,
                             pos.y + j,
                             pieceCourrante.getTypePiece() + 20);

}


 bool TetrisBoard::pieceIsActive()
 {
     return pieceCouranteActive;
 }


void TetrisBoard::effacePieceCourrante()
{
    for (int i=0; i<BOARD_WIDTH; i++)
        for (int j=0; j<BOARD_HEIGHT; j++)
            if (area[i][j] >= 20 && area[i][j] <= 26)
                setBoardData(i, j, 0);
}

int TetrisBoard::getBoardData(int x, int y)
{
    return area[x][y];
}


void TetrisBoard::setBoardData(int x, int y, int data)
{
    if (x<0 || x>=BOARD_WIDTH || y<0 || y>=BOARD_HEIGHT)
        return;
    area[x][y] = data;

    if (area[x][y] >= 10 && area[x][y] < 17)
    {
        sf::Color c = Tetromino::couleurs[area[x][y]-10];
        c.a = 192; // règle l'alpha de la couleur
        shapeMatrix[x*BOARD_HEIGHT+y].setFillColor(c);
    }
    else if (area[x][y] >= 20 && area[x][y] < 27)
    {
        sf::Color c = Tetromino::couleurs[area[x][y]-20];
        shapeMatrix[x*BOARD_HEIGHT+y].setFillColor(c);
    }
    else
        shapeMatrix[x*BOARD_HEIGHT+y].setFillColor(sf::Color::Transparent);
}






int TetrisBoard::fullLinesClear()
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

            for (int j=i; j>0; j--) // on remonte les lignes
                for (int k=0; k<BOARD_WIDTH; k++)
                    setBoardData(k, j, getBoardData(k, j-1));

            // on efface la ligne tout en haut
            for (int j=0; j<BOARD_WIDTH; j++)
                setBoardData(j, 0, 0);

        }
    }
    return nbr_lines;
}






bool TetrisBoard::verifierPlacementPiece(sf::Vector2i pos, int o)
{
    // tests si la forme sors totalement de l'écran
    if (pos.x > BOARD_WIDTH || pos.y > BOARD_HEIGHT || pos.y+4 < 0 || pos.x+4 < 0)
        return false;
    // crée un tetromino de test qui correspond à la position/orientation/forme testée
    Tetromino pieceTest(pieceCourrante.getTypePiece(), o, pos);
    bool ** shape = pieceTest.getMatrixShape();

    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            sf::Vector2i posB(pos.x + i, pos.y + j);
            if (shape[i][j] &&
                ((area[posB.x][posB.y] >= 10 && area[posB.x][posB.y] < 20) ||
                 posB.x < 0 || posB.y < 0 ||
                 posB.x >= BOARD_WIDTH || posB.y >= BOARD_HEIGHT))
            {
                return false;
            }

        }

    }

    return true;
}



void TetrisBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(boardShape, states);
    for (int i=0; i< (BOARD_WIDTH*BOARD_HEIGHT); i++)
        target.draw(shapeMatrix[i], states);
}



