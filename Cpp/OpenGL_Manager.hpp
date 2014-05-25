#ifndef _OPENGL_MANAGER_
#define _OPENGL_MANAGER_
#include "headers.hpp"
#include "Tetromino.hpp"
#include "GameConfiguration.hpp"


class OpenGL_Manager
{
    public:
        OpenGL_Manager(GameConfiguration* _gameConfig);
        void setTetrisBoard(int tetrisBoard[][BOARD_HEIGHT]);
        void preDraw();
        void drawShape();
        void drawArretes();
        void setGLColor(float r, float g, float b);
        void setGLColor();
        ~OpenGL_Manager();

    private:
        float color[3];
        int ** _tetrisBoard;
        float orientation_progress;
        GameConfiguration * _gameConfig;
};

#endif //_OPENGL_MANGER
