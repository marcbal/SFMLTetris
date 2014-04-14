#include "NextTetrominoBoard.hpp"

NextTetrominoBoard::NextTetrominoBoard(sf::Vector2f position) :
    shapeMatrix(4*4),
    boardShape(),
    piece(0, 0, sf::Vector2i(INIT_POS_X, INIT_POS_Y))
{
    clearPiece();

    boardShape.setPosition(position);
    boardShape.setSize(sf::Vector2f(4 * CEIL_SIZE, 4 * CEIL_SIZE));
    boardShape.setFillColor(sf::Color(0, 0, 0, 192));
    boardShape.setOutlineThickness(1);
    boardShape.setOutlineColor(sf::Color(255, 255, 255, 128));



    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
        {
            shapeMatrix[i*4+j] = *(new sf::RectangleShape(sf::Vector2f(CEIL_SIZE, CEIL_SIZE)));
            shapeMatrix[i*4+j].setPosition(position + sf::Vector2f(CEIL_SIZE*i, CEIL_SIZE*j));
            shapeMatrix[i*4+j].setOutlineThickness(-1);
            shapeMatrix[i*4+j].setOutlineColor(sf::Color(63, 63, 63, 63));
            shapeMatrix[i*4+j].setFillColor(sf::Color::Transparent);

        }
}

NextTetrominoBoard::~NextTetrominoBoard() {}


void NextTetrominoBoard::newPiece(Tetromino & t)
{
    cout << "newPiece (";
    piece = t;
    clearPiece();
    dessinePiece();

    cout << ") ok" << endl;
}


Tetromino NextTetrominoBoard::getPiece()
{
    return piece;
}




void NextTetrominoBoard::dessinePiece()
{
    MatrixShape shape = piece.getMatrixShape();
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
        {
            if (shape[i][j])
                setMatrixData(i, j, piece.getTypePiece() + 20);
        }

}
void NextTetrominoBoard::clearPiece()
{
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            setMatrixData(i, j, 0);
}


void NextTetrominoBoard::setMatrixData(int x, int y, int data)
{
    if (x<0 || x>=4 || y<0 || y>=4)
        return;
    matrix[x][y] = data;

    /*
    if (matrix[x][y] >= 10 && matrix[x][y] < 17)
    {
        sf::Color c = Tetromino::couleurs[matrix[x][y]-10];
        c.a = 192; // règle l'alpha de la couleur
        shapeMatrix[x*4+y].setFillColor(c);
    }
    else*/ if (matrix[x][y] >= 20 && matrix[x][y] < 27)
    {
        sf::Color c = Tetromino::couleurs[matrix[x][y]-20];
        shapeMatrix[x*4+y].setFillColor(c);
    }
    else
        shapeMatrix[x*4+y].setFillColor(sf::Color::Transparent);
}




void NextTetrominoBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(boardShape, states);
    for (int i=0; i< (4*4); i++)
        target.draw(shapeMatrix[i], states);
}

