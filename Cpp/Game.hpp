#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Bouton.hpp"
#include "TetrisBoard.hpp"
#include "ScreenElement.hpp"

using namespace std;
using namespace sf;


class Game : public ScreenElement
{
    private:
        TetrisBoard matrix;

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:
        Game(sf::Vector2i window_size, char *state);
        virtual ~Game();
};

#endif // GAME_H
