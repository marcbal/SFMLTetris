#include "Game.hpp"

Game::Game(sf::Vector2i * window_size, char *state) :
    matrix(window_size),
    pieceSuivante()
{
    _window_size = window_size;

}

Game::~Game() {}


void Game::onEvent(sf::Event & event)
{
}



void Game::update()
{
    matrix.dessinePieceCourrante();
}






void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(matrix, states);
}
