#ifndef TETROMINO_H
#define TETROMINO_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>




class Tetromino
{
    public:
        Tetromino(int t, int o, sf::Vector2i pos);
        Tetromino(int t, int o);
        Tetromino(); // génère aléatoirement un tetromino à l'orientation 0
        virtual ~Tetromino();

        int getTypePiece();
        void setTypePiece(int type);
        int getOrientation();
        void setOrientation(int o);
        sf::Vector2i getPosition();
        void setPosition(sf::Vector2i pos);

        sf::Color getColor();
        int** getMatrixShape();

    protected:

        void setMatrixShape();

    private:



        int type_piece;
        int orientation;
        sf::Vector2i position;

        sf::Color couleur;

        int** piece;



        static const int pieces[7][4][4][4];
        /*
            pieces[0] : O
            pieces[1] : I
            pieces[2] : S
            pieces[3] : Z
            pieces[4] : L
            pieces[5] : J
            pieces[6] : T
         */
        static const sf::Color couleurs[7];
};

#endif // TETROMINO_H
