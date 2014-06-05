#ifndef _OPENGL_MANAGER_
#define _OPENGL_MANAGER_
#include "headers.hpp"
#include "Tetromino.hpp"
#include "GameConfiguration.hpp"
#include "fn_random.hpp"


class OpenGL_Manager
{
    public:
        OpenGL_Manager(GameConfiguration* _gameConfig);
        void setTetrisBoard(uint8_t tetrisBoard[][BOARD_HEIGHT]);
        void preDraw();
        void drawShape();
        void drawShapeAlpha(int x, int y);
        void drawArretes();
        void setGLColor(float r, float g, float b);
        void setGLColor();
        void onEvent(sf::Event & event);
        ~OpenGL_Manager();

    private:
        uint8_t ** _tetrisBoard;
        sf::Vector3f orientation_progress;
        sf::Vector3f orientation_vitesse;
        sf::Vector3f orientation_timeMax;
        sf::Clock orientation_timer[3];
        Clock timer;
        bool _isClicked;
        sf::Vector2i lastMousePos;
        float color[4];
        GameConfiguration * _gameConfig;
};

#endif //_OPENGL_MANGER
