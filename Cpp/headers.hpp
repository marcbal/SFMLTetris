#ifndef HEADERS_HPP
#define HEADERS_HPP

// Bibliothèques standard C++
#include <iostream>
#include <sstream>
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>

#ifndef WIN32
    #include <sys/types.h>
#endif

// Bibliothèques SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
//Pour l'affichage 3D
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>






// affichage de debuggage
#include "Console.hpp"

#define DEBUG_NB_CHAR_WIDTH 100
#define DEBUG_NB_CHAR_HEIGHT 30
#define DEBUG_CHAR_SIZE 13






// Defines

// Game :
#define LEVEL_COEFF 10
#define SPEED_LEVEL_COEFF 0.10

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
#define SETTINGSGRAPHIC 7


// TetrisBoard :
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10
#define INIT_POS_X 3
#define INIT_POS_Y -1

#define CEIL_SIZE 22






// Scores :
// force les valeurs stockés dans les fichiers binaire
// au format little endian
#define BINARY_FILE_BIG_ENDIAN false




// ScoreWebSender
#define SERVER_ADDR "sfmltetris.no-ip.org"
#define SERVER_PORT 80
#define SERVER_QUERRY "/SFMLTetris/post_score.php"

// nécessaire car c'est la norme sur les réseaux
#define BINARY_NETWORK_BIG_ENDIAN true





#endif // HEADERS_HPP
