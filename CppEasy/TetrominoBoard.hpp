#ifndef TETROMINOBOARD_H
#define TETROMINOBOARD_H

#include "headers.hpp"

#include "Tetromino.hpp"
#include "TetrisBoard.hpp"


class TetrominoBoard : public sf::Drawable
{
    public:
        TetrominoBoard(sf::Vector2f position);
        virtual ~TetrominoBoard();


        void newPiece(Tetromino & t); // place la nouvelle pièce en haut

        Tetromino getPiece();

        void clearPiece();


    protected:
        void dessinePiece();

        void setMatrixData(int x, int y, int data);
    private:

        int matrix[4][4];
        vector<sf::RectangleShape> shapeMatrix;

        sf::RectangleShape boardShape; // le rectangle principal

        Tetromino piece;

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // TETROMINOBOARD_H
