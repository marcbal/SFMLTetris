#ifndef HEADERS_HPP
#define HEADERS_HPP

// Bibliothèques standard C++
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <dirent.h>
#include <fstream>

#ifndef WIN32
    #include <sys/types.h>
#endif

// Bibliothèques SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>








// Defines

// Game :
#define POINTS_LEVEL 1000
#define SPEED_LEVEL_COEFF 0.2

#define HARD_DROP_BONUS_COEFF 2
#define SOFT_DROP_BONUS_COEFF 1

#define NB_NEXT_TETROMINO 3


// Application :
#define FPS_MAX 60
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

#define INDEX 0
#define GAME 1
#define SETTINGS 2
#define CLOSE 3
#define SETTINGSTOUCHES 4
#define SETTINGSAUDIO 5
#define SCORE 6


// TetrisBoard :
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10
#define INIT_POS_X 3
#define INIT_POS_Y -1

#define CEIL_SIZE 22






#endif // HEADERS_HPP
