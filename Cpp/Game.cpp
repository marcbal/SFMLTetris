#include "Game.hpp"

Game::Game(sf::Vector2i * window_size, char *state) :
    matrix(window_size),
    pieceSuivante()
{
    _window_size = window_size;
    _state = state;

}

Game::~Game() {}


void Game::onEvent(sf::Event & event)
{
    switch(event.type)
    {
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Escape:
                    *_state = INDEX;
                break;
                case sf::Keyboard::Left:
                    matrix.moveLeft();
                break;
                case sf::Keyboard::Right:
                    matrix.moveRight();
                break;
                case sf::Keyboard::Down:
                    matrix.MoveDown();
                break;
                case sf::Keyboard::Space:
                    matrix.HardDrop();
                break;
                case sf::Keyboard::Q:
                    matrix.rotateLeft();
                break;
                case sf::Keyboard::D:
                    matrix.rotateRight();
                break;
                default: break;
            }
        break;
        default:

        break;
    }





}



void Game::update()
{
    matrix.effacePieceCourrante();
    if (!matrix.pieceIsActive())
    {   // passage à la pièce suivante
        if (!matrix.newPiece(pieceSuivante))
        {
            matrix.clearBoard();
            matrix.newPiece(pieceSuivante);
        }
        pieceSuivante = *(new Tetromino());
    }





    matrix.dessinePieceCourrante();
}





void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(matrix, states);
}
