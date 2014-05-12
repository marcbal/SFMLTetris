#include "TetrominoRandomizer.hpp"

TetrominoRandomizer::TetrominoRandomizer()
{
    regen();
}

TetrominoRandomizer::~TetrominoRandomizer()
{
    //dtor
}




int TetrominoRandomizer::getTetrominoType()
{
    nbTetrominoReserve--;
    int val = randTetrominoType[nbTetrominoReserve];
    if (nbTetrominoReserve == 0)
        regen();
    return val;
}




void TetrominoRandomizer::regen()
{
    nbTetrominoReserve = 7;
    for (int i=0; i<7; i++)
        randTetrominoType[i] = i;


    for (int i=0; i<20; i++)
    {
        int r1 = rand_int(0, 6), r2;
        do { r2 = rand_int(0, 6); } while (r1 == r2);
        swap(randTetrominoType[r1], randTetrominoType[r2]);
    }
}
