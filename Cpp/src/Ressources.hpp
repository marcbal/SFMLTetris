#ifndef RESSOURCES_H
#define RESSOURCES_H

#include "headers.hpp"

using namespace std;
using namespace sf;

class Ressources
{
    public:
        static sf::Font * getDefaultFont();
        static sf::Image * getLogo();
        static sf::Image * getLogoMin();
    private:
        static sf::Font * default_font;
        static sf::Image * logo;
        static sf::Image * logoMin;
};

#endif // RESSOURCES_H
