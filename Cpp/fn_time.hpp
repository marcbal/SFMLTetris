#ifndef FN_TIME_H
#define FN_TIME_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <cmath>
#include "fn_string.hpp"


using namespace std;
using namespace sf;


string formattedDuration(sf::Time time);
string formattedDuration(sf::Time time, unsigned int nb_dec);



#endif // FN_TIME_H
