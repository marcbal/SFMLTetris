#include "TetrisBoard.hpp"

TetrisBoard::TetrisBoard(sf::Vector2i * window_size) :
    boardShape(),
    shapeMatrix(BOARD_WIDTH * BOARD_HEIGHT) ,
    pieceCourrante(rand_int(0, 6), 0, sf::Vector2i(0, 0))
{
    pieceCouranteActive = false;
    clearBoard();


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
            shapeMatrix[i*BOARD_HEIGHT+j].setOutlineColor(sf::Color(255, 255, 255, 16));
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
            area[i][j] = 0;
    pieceCouranteActive = false;
}
void TetrisBoard::HardDrop()
{

}
bool TetrisBoard::MoveDown()
{

}


bool moveLeft()
{

}
bool moveRight()
{

}
bool rotateLeft()
{

}
bool rotateRight()
{

}




void TetrisBoard::fixPiece()
{

    pieceCouranteActive = false;

    for (int i=0; i<BOARD_WIDTH; i++)
        for (int j=0; j<BOARD_HEIGHT; j++)
            if (area[i][j] >= 20 && area[i][j] <= 26)
                area[i][j] -= 10;

}


void TetrisBoard::dessinePieceCourrante()
{
    sf::Vector2i pos = pieceCourrante.getPosition();
    int ** shape = pieceCourrante.getMatrixShape();
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            if (shape[i][j])
                area[pos.x + i][pos.y + j] = pieceCourrante.getTypePiece() + 20;

}


void TetrisBoard::effacePieceCourrante()
{
    for (int i=0; i<BOARD_WIDTH; i++)
        for (int j=0; j<BOARD_HEIGHT; j++)
            if (area[i][j] >= 20 && area[i][j] <= 26)
                area[i][j] = 0;
}

int TetrisBoard::getBoardData(int x, int y)
{
    return area[x][y];
}
void TetrisBoard::setBoardData(int x, int y, int data)
{
    area[x][y] = data;
}


bool TetrisBoard::verifierPlacementPiece(sf::Vector2i pos, int o)
{
    // tests si la forme sors totalement de l'écran
    if (pos.x > BOARD_WIDTH || pos.y > BOARD_HEIGHT || pos.y-4 < 0 || pos.x-4 < 0)
        return false;

    // crée un tetromino de test qui correspond à la position/orientation/forme testée
    Tetromino pieceTest(pieceCourrante.getTypePiece(), o, pos);
    int ** shape = pieceTest.getMatrixShape();


    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
        {
            sf::Vector2i posB(pos.x + i, pos.y + j);
            if (shape[i][j] &&
                (area[posB.x][posB.y] > 10 ||
                 posB.x < 0 || posB.y < 0 ||
                 posB.x >= BOARD_WIDTH || posB.y >= BOARD_HEIGHT))
            {
                return false;
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



