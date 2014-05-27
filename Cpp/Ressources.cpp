#include "Ressources.hpp"

sf::Font * Ressources::default_font = nullptr;
sf::Image * Ressources::logo = nullptr;
sf::Image * Ressources::logoMin = nullptr;



sf::Font * Ressources::getDefaultFont()
{
    if (default_font == nullptr)
    {
        default_font = new sf::Font();
        default_font->loadFromFile("res/LiberationMono-Regular.ttf");
    }
    return default_font;
}



sf::Image * Ressources::getLogo()
{
    if (logo == nullptr)
    {
        logo = new sf::Image();
        logo->loadFromFile("res/Crystal_Clear_app_ksirtet.png");
    }
    return logo;
}


sf::Image * Ressources::getLogoMin()
{
    if (logoMin == nullptr)
    {
        logoMin = new sf::Image();
        logoMin->loadFromFile("res/icone.png");
    }
    return logoMin;
}
