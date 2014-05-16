#ifndef SCOREWEBSENDER_H
#define SCOREWEBSENDER_H

#include "headers.hpp"
#include "Scores.hpp"
#include "fn_base64.hpp"
#include "Tetromino.hpp"

using namespace std;


void webSendData(string& data);


union ScoreWebSenderDataSample
{
    byte b[31];
    struct
    {
        uint32_t score;
        uint32_t scoreDiff;
        uint32_t nbTetromino;
        uint32_t timeMilliseconds;
        uint32_t nbDelLines;
        uint32_t nbDelLinesDiff;
        uint32_t nbManualDown;

            // 4 bits de poids fort : le type           : 0x0- � 0x6-
            // 4 bits de poids faible : l'orientation   : 0x-0 � 0x-3
        byte tetrominoTypeAndOrientation;

        int8_t tetrominoPositionX;
        int8_t tetrominoPositionY;
    };

    struct
    {
        _4bytes score;
        _4bytes scoreDiff;
        _4bytes nbTetromino;
        _4bytes timeMilliseconds;
        _4bytes nbDelLines;
        _4bytes nbDelLinesDiff;
        _4bytes nbManualDown;
        byte tetrominoTypeAndOrientation;
        int8_t tetrominoPositionX;
        int8_t tetrominoPositionY;
    } u;


};


class ScoreWebSender
{
    private:

        vector<ScoreWebSenderDataSample> gameDatas;



        void clearData();

    public:
        ScoreWebSender();
        virtual ~ScoreWebSender();

        // appel� apr�s chaque pose d'une pi�ce dans le tetris board
        // c'est � dire au moment ou elle est fix�e
        void addDataInfoNextPiece(int score,                // nouveau score obtenu
                                  int scoreDiff,            // diff�rence avec l'ancien score
                                  int nbTetromino,          // nombre de tetromino pos�
                                  sf::Time time,            // horloge actuelle
                                  int delLines,             // nombre de lignes d�truites depuis le d�but
                                  int newDelLines,          // nombre de ligne d�truite � ce moment
                                  int nbManualDown,         // compteur d'acc�l�ration de descente
                                  Tetromino tetrominoPlace);// le t�tromino tout juste pos� (avec son type/orientation/position)

        void addDataToFinishGame(RecordLine rL);

    protected:
};

#endif // SCOREWEBSENDER_H
