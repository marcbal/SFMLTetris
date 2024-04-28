#ifndef TETRISBOARD_H
#define TETRISBOARD_H

#include "headers.hpp"

#include "Tetromino.hpp"
#include "fn_random.hpp"
#include "Collision.hpp"
#include "ExplosionManager.hpp"
#include "OpenGL_Manager.hpp"
#include "AudioConfiguration.hpp"
#include "LogicalTetrisBoard.hpp"
using namespace std;
using namespace sf;


class TetrisBoard : public LogicalTetrisBoard, public sf::Drawable
{
    public:

        TetrisBoard(sf::Vector2i * window_size,OpenGL_Manager * oGL, AudioConfiguration * audio);
        virtual ~TetrisBoard();

        bool mouseLeftRight(sf::Event event);

        int fullLinesClear(ExplosionManager * explosions);

        void updateGraphics(char mode);

        void mouseIADisturb(sf::Event & event);

        void clearBoard(ExplosionManager * explosions);



    private:
        OpenGL_Manager * _oGL;
        // element graphique
        sf::RectangleShape boardShape; // le rectangle principal
        vector<sf::RectangleShape> shapeMatrix; // les rectangles de chaque cases

        sf::Vector2i * _window_size;

        AudioConfiguration * _audio;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // TETRISBOARD_H
