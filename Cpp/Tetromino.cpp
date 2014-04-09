#include "Tetromino.hpp"
#include "fn_random.hpp"

using namespace std;
using namespace sf;


Tetromino::Tetromino(int t, int o, sf::Vector2i pos)
{



    piece = new bool*[4];
    for (int i = 0; i<4; i++)
        piece[i] = new bool[4];

    setTypePiece(t);
    setOrientation(o);
    setPosition(pos);
}
Tetromino::Tetromino(int t, int o) : Tetromino(t, o, sf::Vector2i(0, 0))
{
}
Tetromino::Tetromino() : Tetromino(rand_int(0, 6), 0)
{
}
Tetromino::~Tetromino()
{
    for (int i = 0; i<4; i++)
        delete[] piece[i];
    delete[] piece;
}





int Tetromino::getTypePiece()
{
    return type_piece;
}
void Tetromino::setTypePiece(int type)
{
    if (type < 0) type += 7;
    type = type % 7;
    type_piece = type;

    couleur = Tetromino::couleurs[type_piece];
    setMatrixShape();
}
int Tetromino::getOrientation()
{
    return orientation;
}
void Tetromino::setOrientation(int o)
{
    if (o < 0) o += 4;
    o = o % 4;
    orientation = o;
    setMatrixShape();
}
sf::Vector2i Tetromino::getPosition()
{
    return position;
}
void Tetromino::setPosition(sf::Vector2i pos)
{
    position = pos;
}

sf::Color Tetromino::getColor()
{
    return couleur;
}

bool** Tetromino::getMatrixShape()
{
    setMatrixShape();
    return piece;

}




void Tetromino::setMatrixShape()
{
    if (type_piece < 0 || type_piece > 6 || orientation < 0 || orientation > 3)
        return;
    for (int i=0; i<4; i++)
    {

        for (int j=0; j<4; j++)
        {
            piece[i][j] = pieces[type_piece][orientation][j][i];
        }
    }
}





const sf::Color Tetromino::couleurs[7] =
{
    sf::Color::Blue,
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Cyan,
    sf::Color::Magenta,
    sf::Color::White,
    sf::Color::Yellow
};



const bool Tetromino::pieces[7][4][4][4] =
{
    { // O
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }
    },

    { // I
        {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0}
        },

        {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0}
        },

        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        }
    },

    { // S
        {
            {0, 0, 0, 0},
            {0, 0, 1, 1},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 1, 0},
            {0, 0, 1, 1},
            {0, 0, 0, 1},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 0, 0},
            {0, 0, 1, 1},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 1, 0},
            {0, 0, 1, 1},
            {0, 0, 0, 1},
            {0, 0, 0, 0}
        }
    },

    { // Z
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 1, 1},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 0, 1},
            {0, 0, 1, 1},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 1, 1},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 0, 1},
            {0, 0, 1, 1},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        }
    },

    { // L
        {
            {0, 0, 0, 0},
            {0, 1, 1, 1},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 1},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 0, 1},
            {0, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        }
    },

    { // J
        {
            {0, 0, 0, 0},
            {0, 1, 1, 1},
            {0, 0, 0, 1},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 1, 1},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 1, 0, 0},
            {0, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }
    },

    { // T
        {
            {0, 0, 0, 0},
            {0, 1, 1, 1},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 1, 0},
            {0, 0, 1, 1},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 1, 0},
            {0, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        }
    }
};
