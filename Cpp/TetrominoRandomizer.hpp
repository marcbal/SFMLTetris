#ifndef TETROMINORANDOMIZER_H
#define TETROMINORANDOMIZER_H


#include "headers.hpp"

#include "Tetromino.hpp"
#include "fn_random.hpp"


class TetrominoRandomizer
{
    private:


        int randTetrominoType[7];
        int nbTetrominoReserve;

        void regen();

    public:
        TetrominoRandomizer();
        virtual ~TetrominoRandomizer();

        int getTetrominoType();

};

#endif // TETROMINORANDOMIZER_H
