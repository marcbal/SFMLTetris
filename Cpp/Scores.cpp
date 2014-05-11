#include "Scores.hpp"

bool os_arch_is_big_endian()
{
    union {
        uint32_t i;
        byte b[4];
    } bint = {0x01020304};
    return bint.b[0] == 1;
}

_2bytes convert_endianness(_2bytes var)
{
    if (BINARY_FILE_BIG_ENDIAN == os_arch_is_big_endian())
        return var;
    _2bytes r = {0x0000};
    r.b[0] = var.b[1]; r.b[1] = var.b[0];
    return r;
}

_4bytes convert_endianness(_4bytes var)
{
    if (BINARY_FILE_BIG_ENDIAN == os_arch_is_big_endian())
        return var;
    _4bytes r = {0x00000000};
    r.b[0] = var.b[3]; r.b[1] = var.b[2];
    r.b[2] = var.b[1]; r.b[3] = var.b[0];
    return r;
}

_8bytes convert_endianness(_8bytes var)
{
    if (BINARY_FILE_BIG_ENDIAN == os_arch_is_big_endian())
        return var;
    _8bytes r;
    r.b[0] = var.b[7]; r.b[1] = var.b[6];
    r.b[2] = var.b[5]; r.b[3] = var.b[4];
    r.b[4] = var.b[3]; r.b[5] = var.b[2];
    r.b[6] = var.b[1]; r.b[7] = var.b[0];
    return r;
}





const string Scores::scoreFile = "save/score.bin";



Scores::Scores() :
    scoreTable()
{
    loadFromFile();
}

Scores::~Scores()
{
    saveToFile();
}





RecordLine Scores::getScore(unsigned int i)
{
    if (i < scoreTable.size())
        return scoreTable[i];
    RecordLine r;
    r.tetrominos = 0;
    return r;
}

void Scores::addScore(RecordLine rec)
{
    scoreTable.push_back(rec);

    for (int i=scoreTable.size()-1; i>0; i++)
    {
        if (scoreTable[i].points > scoreTable[i-1].points)
            swap(scoreTable[i], scoreTable[i-1]);
        else
            break;
    }

    while (scoreTable.size() > 255)
        scoreTable.pop_back();

    saveToFile();
}




void Scores::loadFromFile()
{
    ifstream file (Scores::scoreFile, ios::in | ios::binary);

    if (!file.is_open())
    {
        cout << "Erreur lors du chargement des scores" << endl;
        return;
    }


    file.seekg (0, file.end);
    int fileSize = file.tellg();
    file.seekg (0, file.beg);


    if (fileSize < 6)
    {
        cout << "Erreur lors du chargement des scores" << endl;
        return;
    }

    byte nbEnregistrement = 0;
    byte sizeEnregistrement = 0;
    _4bytes sumControlCheck;
    sumControlCheck.i = 0;

    file.read((char*)&nbEnregistrement, sizeof(byte));
    file.read((char*)&sizeEnregistrement, sizeof(byte));

    if (sizeEnregistrement != sizeof(RecordLine))
    {
        cout << "Erreur lors du chargement des scores" << endl;
        return;
    }

    if (fileSize != sizeEnregistrement*nbEnregistrement+6)
    {
        cout << "Erreur lors du chargement des scores" << endl;
        return;
    }

    vector<RecordLine> r;

    for (int i=0; i<nbEnregistrement; i++)
    {
        RecordLine l;
        file.read((char*)&l.b, sizeEnregistrement);
        l.lines_u = convert_endianness(l.lines_u);
        l.points_u = convert_endianness(l.points_u);
        l.tetrominos_u = convert_endianness(l.tetrominos_u);
        l.time_u = convert_endianness(l.time_u);
        sumControlCheck.i += l.lines + l.points + l.tetrominos + l.time;
        r.push_back(l);
    }
    _4bytes sumControlFile;
    file.read((char*)&sumControlFile.b, sizeof(_4bytes));
    sumControlFile = convert_endianness(sumControlFile);
    if (sumControlCheck.i != sumControlFile.i)
    {
        r.clear();
        cout << "Erreur lors du chargement des scores" << endl;
        return;
    }

    scoreTable = r;

}
void Scores::saveToFile()
{
    ofstream file (Scores::scoreFile, ios::out | ios::binary | ios::trunc);


    if (!file.is_open())
    {
        cout << "Erreur : impossible d'écrire dans le fichier des scores" << endl;
        return;
    }


    byte nbEnregistrement = scoreTable.size();
    byte sizeEnregistrement = sizeof(RecordLine);
    _4bytes checkSum = {0x00000000};
    file.write((char*)&nbEnregistrement, sizeof(byte));
    file.write((char*)&sizeEnregistrement, sizeof(byte));
    for (unsigned int i=0; i<scoreTable.size(); i++)
    {
        RecordLine l = scoreTable[i];
        l.lines_u = convert_endianness(l.lines_u);
        l.points_u = convert_endianness(l.points_u);
        l.tetrominos_u = convert_endianness(l.tetrominos_u);
        l.time_u = convert_endianness(l.time_u);
        file.write((char*)&l.b, sizeof(RecordLine));
        checkSum.i += l.lines + l.points + l.tetrominos + l.time;
    }
    checkSum = convert_endianness(checkSum);
    file.write((char*)&checkSum.b, sizeof(_4bytes));


}
