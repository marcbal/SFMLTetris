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


    public:
        TetrominoRandomizer();
        virtual ~TetrominoRandomizer();

        int getTetrominoType();
        void regen();

};

#endif // TETROMINORANDOMIZER_H
