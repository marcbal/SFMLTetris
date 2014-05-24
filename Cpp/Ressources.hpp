#ifndef RESSOURCES_H
#define RESSOURCES_H

#include "headers.hpp"

using namespace std;
using namespace sf;

class Ressources
{
    public:
        static sf::Font * getDefaultFont();
    private:
        static sf::Font * default_font;
};

#endif // RESSOURCES_H
