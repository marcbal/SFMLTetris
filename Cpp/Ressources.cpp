#include "Ressources.hpp"

sf::Font * Ressources::default_font = nullptr;



sf::Font * Ressources::getDefaultFont()
{
    if (default_font == nullptr)
    {
        default_font = new sf::Font();
        default_font->loadFromFile("res/LiberationMono-Regular.ttf");
    }
    return default_font;
}
