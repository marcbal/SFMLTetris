#ifndef NEXTTETROMINOBOARD_H
#define NEXTTETROMINOBOARD_H

#include "headers.hpp"

#include "Tetromino.hpp"
#include "TetrisBoard.hpp"


class NextTetrominoBoard : public sf::Drawable
{
    public:
        NextTetrominoBoard(sf::Vector2f position);
        virtual ~NextTetrominoBoard();


        void newPiece(Tetromino & t); // place la nouvelle pièce en haut

        Tetromino getPiece();


    protected:
        void dessinePiece();
        void clearPiece();

        void setMatrixData(int x, int y, int data);
    private:

        int matrix[4][4];
        vector<sf::RectangleShape> shapeMatrix;

        sf::RectangleShape boardShape; // le rectangle principal

        Tetromino piece;

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // NEXTTETROMINOBOARD_H
