#include "Ressources.hpp"

sf::Font * Ressources::default_font = nullptr;
sf::Image * Ressources::logo = nullptr;
sf::Image * Ressources::logoMin = nullptr;



sf::Font * Ressources::getDefaultFont()
{
    if (default_font == nullptr)
    {
        default_font = new sf::Font();
        if (!default_font->loadFromFile("res/LiberationMono-Regular.ttf"))
            Console::err(L"Erreur lors du chargement du fichier de police de caractère\nVérifiez la présence d'un fichier nommé \"res/LiberationMono-Regular.ttf\"");
    }
    return default_font;
}



sf::Image * Ressources::getLogo()
{
    if (logo == nullptr)
    {
        logo = new sf::Image();
        if (!logo->loadFromFile("res/Crystal_Clear_app_ksirtet.png"))
            Console::err(L"Erreur lors du chargement du logo\nVérifiez la présence d'un fichier nommé \"res/Crystal_Clear_app_ksirtet.png\"");
    }
    return logo;
}


sf::Image * Ressources::getLogoMin()
{
    if (logoMin == nullptr)
    {
        logoMin = new sf::Image();
        if (!logoMin->loadFromFile("res/icone.png"))
            Console::err(L"Erreur lors du chargement de l'icône\nVérifiez la présence d'un fichier nommé \"res/icone.png\"");
    }
    return logoMin;
}
