#ifndef _OPENGL_MANAGER_
#define _OPENGL_MANAGER_
#include "headers.hpp"
#include "Tetromino.hpp"
class OpenGL_Manager{
    public :
        OpenGL_Manager();
        void setTetrisBoard(int tetrisBoard[][BOARD_HEIGHT]);
        void preDraw();
        void drawShape();
        void drawArretes();
        void setGLColor(float r, float g, float b);
        void setGLColor();
        bool getActivate();
        float getInclinaison();
        void setActivate(bool _n);
        void setInclinaison(float _n);
        ~OpenGL_Manager();

    private:
    bool _isActivate;
    float _inclinaison;
    float color[3];
    int ** _tetrisBoard;
    float test;
};

#endif //_OPENGL_MANGER
