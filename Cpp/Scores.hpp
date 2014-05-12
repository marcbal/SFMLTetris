#ifndef SCORES_H
#define SCORES_H

#include "headers.hpp"

using namespace std;

using byte = unsigned char;

union _8bytes
{
    uint64_t i;
    byte b[8];
};

union _4bytes
{
    uint32_t i;
    byte b[4];
};

union _2bytes
{
    uint16_t i;
    byte b[2];
};



// vérifie la façon dont est stocké les données en mémoire
// en big-endian ou little-endian (pour la portabilité des données)
bool is_big_endian();


_2bytes convert_endianness(_2bytes var);
_4bytes convert_endianness(_4bytes var);
_8bytes convert_endianness(_8bytes var);






union RecordLine
{
    byte b[46];
    char c[46];
    struct
    {
        char name[30];
        uint32_t points;
        uint32_t lines;
        uint32_t tetrominos;
        uint32_t time;
    };
    struct
    {
        byte name_u[30];
        _4bytes points_u;
        _4bytes lines_u;
        _4bytes tetrominos_u;
        _4bytes time_u;
    };
};

class Scores
{
    public:




        Scores();
        virtual ~Scores();

        vector<RecordLine> getScores();
        void addScore(RecordLine rec);

    protected:
        void loadFromFile();
        void saveToFile();
    private:
        static const uint8_t recordSize = sizeof(RecordLine);

        static const string scoreFile;

        vector<RecordLine> scoreTable;
};

#endif // SCORES_H









