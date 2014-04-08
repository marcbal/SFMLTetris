#include "Game.hpp"

Game::Game(sf::Vector2i window_size, char *state) :
    Menu(window_size,state),
    matrix(window_size)
{


}

Game::~Game() {}






void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(matrix, states);
}
