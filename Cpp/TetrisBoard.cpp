#include "TetrisBoard.hpp"

TetrisBoard::TetrisBoard(sf::Vector2i * window_size,OpenGL_Manager * oGL) :
    LogicalTetrisBoard(),
    boardShape(),
    shapeMatrix(BOARD_WIDTH * BOARD_HEIGHT)
{
    _oGL = oGL;
    _oGL->setTetrisBoard(area);

    _window_size = window_size;

    // positionnement du tetris board à l'écran
    sf::Vector2f top_left_pos(((812 - 285) - BOARD_WIDTH * CEIL_SIZE)/2 + 285,
                              (window_size->y - BOARD_HEIGHT * CEIL_SIZE)/2);


    boardShape.setPosition(top_left_pos);
    boardShape.setSize(sf::Vector2f(BOARD_WIDTH * CEIL_SIZE, BOARD_HEIGHT * CEIL_SIZE));
    boardShape.setFillColor(sf::Color(0, 0, 0, 192));
    boardShape.setOutlineThickness(2);
    boardShape.setOutlineColor(sf::Color::White);
    for (int i=0; i<BOARD_WIDTH; i++)
        for (int j=0; j<BOARD_HEIGHT; j++)
        {
            shapeMatrix[i*BOARD_HEIGHT+j] = sf::RectangleShape(sf::Vector2f(CEIL_SIZE, CEIL_SIZE));
            shapeMatrix[i*BOARD_HEIGHT+j].setPosition(top_left_pos + sf::Vector2f(CEIL_SIZE*i, CEIL_SIZE*j));
            shapeMatrix[i*BOARD_HEIGHT+j].setOutlineThickness(-1);
            shapeMatrix[i*BOARD_HEIGHT+j].setOutlineColor(sf::Color(46, 46, 46, 46));
            shapeMatrix[i*BOARD_HEIGHT+j].setFillColor(sf::Color::Transparent);

        }


}

TetrisBoard::~TetrisBoard(){}




void TetrisBoard::mouseIADisturb(sf::Event & event)
{
    sf::FloatRect rect = boardShape.getGlobalBounds();
    if (event.type != sf::Event::MouseButtonPressed)
        return;
    sf::Vector2f cur_pos(event.mouseButton.x, event.mouseButton.y);
    if (!rect.contains(cur_pos))
        return;
    sf::Vector2f local_cur_pos = cur_pos - boardShape.getPosition();

    sf::Vector2i matrixPos((int)((local_cur_pos.x/(float)rect.width)*BOARD_WIDTH),
                           (int)((local_cur_pos.y/(float)rect.height)*BOARD_HEIGHT));

    if (event.mouseButton.button == sf::Mouse::Left
        && getBoardData(matrixPos.x, matrixPos.y) < 10)
        setBoardData(matrixPos.x, matrixPos.y, rand_int(10, 16));
    else if (event.mouseButton.button == sf::Mouse::Right
             && getBoardData(matrixPos.x, matrixPos.y) >= 10
             && getBoardData(matrixPos.x, matrixPos.y) < 20)
        setBoardData(matrixPos.x, matrixPos.y, 0);



}








bool TetrisBoard::mouseLeftRight(sf::Event event)
{
    if (event.type != sf::Event::MouseMoved)
        return false;
    sf::Vector2f cur_pos(event.mouseMove.x, event.mouseMove.y);
    sf::Vector2f top_left(((812 - 285) - BOARD_WIDTH * CEIL_SIZE)/2 + 285,
                              (_window_size->y - BOARD_HEIGHT * CEIL_SIZE)/2);
    sf::Vector2f board_size(BOARD_WIDTH * CEIL_SIZE,
                            BOARD_HEIGHT * CEIL_SIZE);
    if (!pointInRect(top_left - sf::Vector2f(CEIL_SIZE, 0), board_size + sf::Vector2f(2*CEIL_SIZE, 0), cur_pos))
        return false;
    cur_pos -= top_left;
    int tetromino_new_pos = (cur_pos.x * BOARD_WIDTH) / board_size.x;
    tetromino_new_pos -= 2; // décalage pour centrer sur la souris
    bool continuer = true;
    bool hasMove = false;
    while (tetromino_new_pos < pieceCourrante.getPosition().x && continuer)
    {
        continuer = moveLeft();
        if (continuer) hasMove = true;
    }
    while (tetromino_new_pos > pieceCourrante.getPosition().x && continuer)
    {
        continuer = moveRight();
        if (continuer) hasMove = true;
    }
    return hasMove;
}





void TetrisBoard::updateGraphics(char mode)
{
    for (int x=0; x<BOARD_WIDTH; x++)
        for (int y=0; y<BOARD_HEIGHT; y++)
        {
            if (mode == 0)
            {
                if (area[x][y] >= 10 && area[x][y] < 17)
                {
                    sf::Color c = Tetromino::couleurs[area[x][y]-10];
                    c.a = 192; // règle l'alpha de la couleur
                    shapeMatrix[x*BOARD_HEIGHT+y].setFillColor(c);
                }
                else if (area[x][y] >= 20 && area[x][y] < 27)
                {
                    sf::Color c = Tetromino::couleurs[area[x][y]-20];
                    shapeMatrix[x*BOARD_HEIGHT+y].setFillColor(c);
                }
                else if (area[x][y] >= 30 && area[x][y] < 37)
                {
                    sf::Color c = Tetromino::couleurs[area[x][y]-30];
                    c.a = 64; // règle l'alpha de la couleur
                    shapeMatrix[x*BOARD_HEIGHT+y].setFillColor(c);
                }
                else
                    shapeMatrix[x*BOARD_HEIGHT+y].setFillColor(sf::Color::Transparent);
            }
            else if (mode == 1)
            {   // Dark Tetris Mode
                sf::Vector2f midpoint = pieceCourrante.getMidpoint();
                float dist = sqrt((midpoint.x-x)*(midpoint.x-x)+(midpoint.y-y)*(midpoint.y-y));
                float champ_vision = 10.f;
                float coeff = (dist > champ_vision)? 0.f : (champ_vision-dist)/champ_vision ;

                if (area[x][y] >= 10 && area[x][y] < 17)
                {
                    sf::Color c = Tetromino::couleurs[area[x][y]-10];
                    c.a = 192 * coeff; // règle l'alpha de la couleur
                    shapeMatrix[x*BOARD_HEIGHT+y].setFillColor(c);
                }
                else if (area[x][y] >= 20 && area[x][y] < 27)
                {
                    sf::Color c = Tetromino::couleurs[area[x][y]-20];
                    c.a = 255 * coeff;
                    shapeMatrix[x*BOARD_HEIGHT+y].setFillColor(c);
                }
                else if (area[x][y] >= 30 && area[x][y] < 37)
                {
                    sf::Color c = Tetromino::couleurs[area[x][y]-30];
                    c.a = 64 * coeff; // règle l'alpha de la couleur
                    shapeMatrix[x*BOARD_HEIGHT+y].setFillColor(c);
                }
                else
                    shapeMatrix[x*BOARD_HEIGHT+y].setFillColor(sf::Color::Transparent);
            }
        }

}


int TetrisBoard::fullLinesClear(ExplosionManager * explosions)
{
    int nbr_lines = 0;
    for (int i=0; i<BOARD_HEIGHT; i++)
    {   // on parcours les lignes de haut en bas
        bool full = true;
        // on vérifie si la ligne est complète
        for (int j=0; j<BOARD_WIDTH && full; j++)
            if (getBoardData(j, i) < 10)
                full = false;

        if (full)
        {
            nbr_lines++;
            // on efface la ligne
            for (int j=0; j<BOARD_WIDTH; j++)
            {
                sf::RectangleShape r = shapeMatrix[j*BOARD_HEIGHT+i];
                if (explosions != nullptr)
                    explosions->addExplosion(RectangleExplosion(_window_size,
                                                          sf::FloatRect(r.getPosition(), r.getSize()),
                                                          (ExplosionManager::_nbParticules>500)?4:20,
                                                          6.0,
                                                          r.getFillColor()));
                setBoardData(j, i, 0);
            }

            // on décale tout ce qui se trouve au dessus

            for (int j=i; j>-2; j--) // on remonte les lignes
                for (int k=0; k<BOARD_WIDTH; k++)
                    setBoardData(k, j, getBoardData(k, j-1));

            // on efface la ligne tout en haut
            for (int j=0; j<BOARD_WIDTH; j++)
                setBoardData(j, -2, 0);

        }
    }
    return nbr_lines;
}





void TetrisBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(boardShape, states);
    for (int i=0; i< (BOARD_WIDTH*BOARD_HEIGHT); i++)
        target.draw(shapeMatrix[i], states);
}




