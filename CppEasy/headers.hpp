#ifndef HEADERS_HPP
#define HEADERS_HPP

// Bibliothèques standard C++
#include <cstring>
#include <ctime>
#include <sstream>
#include <string>
#include <vector>

// Bibliothèques SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>






// Defines

// Game :
#define LEVEL_COEFF 10
#define SPEED_LEVEL_COEFF 0.10

#define HARD_DROP_BONUS_COEFF 2
#define SOFT_DROP_BONUS_COEFF 1


// Application :
#define FPS_MAX 60
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 540


// TetrisBoard :
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10
#define INIT_POS_X 3
#define INIT_POS_Y -1

#define CEIL_SIZE 22




#endif // HEADERS_HPP
