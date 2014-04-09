#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Bouton.hpp"
#include "TetrisBoard.hpp"
#include "ScreenElement.hpp"
#include "Application.hpp"

using namespace std;
using namespace sf;


class Game : public ScreenElement
{
    private:
        TetrisBoard matrix;
        Tetromino pieceSuivante;

        char * _state;

        int _score = 0;
        int _nb_line = 0;

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:
        Game(sf::Vector2i * window_size, char *state);
        virtual ~Game();


        virtual void onEvent(sf::Event & event);


        virtual void update();
};

#endif // GAME_H
