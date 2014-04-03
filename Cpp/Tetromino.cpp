#include "Tetromino.hpp"
#include "fn_random.hpp"


Tetromino::Tetromino(int t, int o, sf::Vector2i pos)
{
    piece = new int*[4];
    for (int i = 0; i<4; i++)
        piece[i] = new int[4];

    setTypePiece(t);
    setOrientation(o);
    setPosition(pos);
}
Tetromino::Tetromino(int t, int o)
{
    Tetromino(t, o, sf::Vector2i(0, 0));
}
Tetromino::Tetromino()
{
    Tetromino(rand_int(0, 6), 0);
}
Tetromino::~Tetromino() {}

int Tetromino::getTypePiece()
{
    return type_piece;
}
void Tetromino::setTypePiece(int type)
{
    if (type < 0 || type > 6)
        type = type % 7;
    type_piece = type;

    couleur = Tetromino::couleurs[type_piece];
    setMatrix();
}
int Tetromino::getOrientation()
{
    return orientation;
}
void Tetromino::setOrientation(int o)
{

    if (o < 0 || o > 3)
        o = o % 4;
    orientation = o;
    setMatrix();
}
sf::Vector2i Tetromino::getPosition()
{
    return position;
}
void Tetromino::setPosition(sf::Vector2i pos)
{
    position.x = pos.x;
    position.y = pos.y;
}

sf::Color Tetromino::getColor()
{
    return couleur;
}

int** Tetromino::getMatrixShape()
{
    return piece;

}




void Tetromino::setMatrix()
{
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            piece[i][j] = pieces[type_piece][orientation][i][j];
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



const int Tetromino::pieces[7][4][4][4] =
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
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0}
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
