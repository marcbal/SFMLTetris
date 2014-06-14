#ifndef TETRISBOARD_H
#define TETRISBOARD_H

#include "headers.hpp"

#include "Tetromino.hpp"
#include "fn_random.hpp"
using namespace std;
using namespace sf;


class TetrisBoard : public sf::Drawable
{
    public:

        TetrisBoard(sf::Vector2i * window_size);
        virtual ~TetrisBoard();

        void updateGraphics(char mode);

        bool newPiece(Tetromino p, bool init_pos = true); // place la nouvelle pièce en haut
        Tetromino & getPieceCourrante();

        void clearBoard();

        int HardDrop();

        bool MoveDown();
        bool MoveDownCheck();
        bool moveLeft();
        bool moveRight();
        bool rotateLeft();
        bool rotateRight();

        // les valeurs x et y sont les nouvelles coordonnées du tetromino
        // la valeur z correspond à la nouvelle orientation (0-3)
        // si z = ancienne orientation, la rotation n'a pas lieu.
        sf::Vector3i SRSRotate(int oldOrient, int newOrient);

        void fixPiece();
        void dessinePieceCourrante(bool drawGhost);
        void effacePieceCourrante();
        int fullLinesClear();
        bool pieceIsActive();
        int getBoardData(int x, int y) const;
        void setBoardData(int x, int y, int data);



    private:
        // element graphique
        sf::RectangleShape boardShape; // le rectangle principal
        vector<sf::RectangleShape> shapeMatrix; // les rectangles de chaque cases

        sf::Vector2i * _window_size;



        bool verifierPlacementPiece(sf::Vector2i pos, int o);   // par rapport à la position absolue
        bool verifierDeplacementPiece(sf::Vector2i var_pos, int o);// par rapport à la position relative


        Tetromino pieceCourrante;
        bool pieceCouranteActive;
        uint8_t area[BOARD_WIDTH][BOARD_HEIGHT];
        /*
            Valeurs des cases possibles
            0 : vide (les cases de 1 à 9 peuvent être considéré comme vide (pour faciliter les conditions))
            10-16 : les cases fixes
            20-26 : les cases de la pièce en mouvement
            30-36 : les cases du fantôme de la pièce en mouvement
        */
        uint8_t areasup[BOARD_WIDTH][2];
        // contient les valeurs des cases cachés au dessus


        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // TETRISBOARD_H
