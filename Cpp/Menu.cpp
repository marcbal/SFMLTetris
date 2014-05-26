#include "Menu.hpp"

using namespace std;
using namespace sf;

Menu::Menu(sf::Vector2i * window_size,char * state) :
    menuElements(),
    titre()
{
    _state = state;
    _window_size = window_size;

    // création des éléments de menu
    menuElements.clear();
    titre.setCharacterSize(30);
    titre.setPosition(50, 20);
    titre.setFont(*Ressources::getDefaultFont());
    titre.setColor(sf::Color::White);
    titre.setString("");
}

Menu::~Menu() {}


void Menu::update()
{
    // rien à mettre pour le moment
}


void Menu::onMouseMove(sf::Event & event)
{
    if (event.type != Event::MouseMoved)
        return;

    for (unsigned int i=0; i<menuElements.size(); i++)
    {
        menuElements[i].onMouseMove(event);
    }
}

void Menu::onEvent(sf::Event & event){
		switch(event.type)
		{
            case Event::MouseMoved:
                this->onMouseMove(event);
            break;

            case sf::Event::MouseButtonPressed:
                this->onMouseDown(event);
            break;


            case sf::Event::MouseButtonReleased:
                this->onMouseUp(event);
            break;

            default:
            break;
		}
}

void Menu::onMouseDown(sf::Event & event)
{
    if (event.type != Event::MouseButtonPressed)
        return;

    for (unsigned int i=0; i<menuElements.size(); i++)
    {
        menuElements[i].onMouseDown(event);
    }
}

void Menu::onMouseUp(sf::Event & event)
{
    if (event.type != Event::MouseButtonReleased)
        return;

    for (unsigned int i=0; i<menuElements.size(); i++)
    {
        menuElements[i].onMouseUp(event);
    }
}



void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned int i=0; i<menuElements.size(); i++)
    {
        target.draw(menuElements[i], states);
    }
    target.draw(titre, states);
}

