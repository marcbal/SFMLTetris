#ifndef TETRISBOARD_H
#define TETRISBOARD_H

#include "Tetromino.hpp"
#include "fn_random.hpp"
#include <vector>





#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10
#define INIT_POS_X 3
#define INIT_POS_Y -1

#define CEIL_SIZE 22



using namespace std;
using namespace sf;


class TetrisBoard : public sf::Drawable
{
    public:

        TetrisBoard(sf::Vector2i * window_size);
        virtual ~TetrisBoard();


        bool newPiece(Tetromino p); // place la nouvelle pièce en haut
        Tetromino & getPieceCourrante();

        void clearBoard();

        void HardDrop();

        bool MoveDown();
        bool moveLeft();
        bool moveRight();
        bool rotateLeft();
        bool rotateRight();


        void fixPiece();
        void dessinePieceCourrante();
        void effacePieceCourrante();

        int getBoardData(int x, int y);
        void setBoardData(int x, int y, int data);



    private:

        // element graphique
        sf::RectangleShape boardShape; // le rectangle principal
        vector<sf::RectangleShape> shapeMatrix; // les rectangles de chaque cases

        sf::Vector2i * _window_size;

        bool verifierPlacementPiece(sf::Vector2i pos, int o);

        Tetromino pieceCourrante;
        bool pieceCouranteActive;
        int area[BOARD_WIDTH][BOARD_HEIGHT];
        /*
            Valeurs des cases possibles
            0 : vide (les cases de 1 à 9 peuvent être considéré comme vide (pour faciliter les conditions))
            10-16 : les cases fixes
            20-26 : les cases de la pièce en mouvement
        */

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // TETRISBOARD_H
