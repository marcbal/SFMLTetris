#ifndef SCORES_H
#define SCORES_H

#include "headers.hpp"
#include "fileManager.hpp"

using namespace std;

using byte = uint8_t;

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


_2bytes convert_endianness(_2bytes var, bool external_endianness_big_endian);
_4bytes convert_endianness(_4bytes var, bool external_endianness_big_endian);
_8bytes convert_endianness(_8bytes var, bool external_endianness_big_endian);






union RecordLine
{
    byte b[48];
    char c[48];
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









