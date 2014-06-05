#include "BoutonLink.hpp"


void launch_external_navigator(string link)
{
    Console::out("Ouverture de " + link);
    #ifdef _WIN32
    system(("start " + link).c_str());
    #elif defined(__GNUC__)
    system(("xdg-open " + link).c_str());
    #else
    Console::err(L"L'ouverture d'une URI n'est pas encore implémenté pour votre système", __FILE__, __LINE__);
    #endif
}









BoutonLink::BoutonLink(sf::Text t, string l)
{
    _mouseClick = false;
    _mouseHover = false;
    texte = t;
    _lien = l;
    updateGraphics();
}

BoutonLink::~BoutonLink(){}






void BoutonLink::onEvent(sf::Event & event)
{
    switch(event.type)
    {
        case sf::Event::MouseMoved:
            onMouseMove(event);
        break;
        case sf::Event::MouseButtonPressed:
            onMouseDown(event);
        break;
        case sf::Event::MouseButtonReleased:
            onMouseUp(event);
        break;
        default:
        break;
    }
    updateGraphics();
}
void BoutonLink::onMouseMove(sf::Event & event)
{
    if (event.type != Event::MouseMoved)
        return;
    sf::FloatRect r = texte.getGlobalBounds();
    r.height += texte.getCharacterSize() / 2.0;
    r.top -= texte.getCharacterSize() / 8.0;
    _mouseHover = r.contains(event.mouseMove.x,event.mouseMove.y);
}
void BoutonLink::onMouseDown(sf::Event & event)
{
    if (event.type != Event::MouseButtonPressed
        || event.mouseButton.button != sf::Mouse::Left)
        return;
    sf::FloatRect r = texte.getGlobalBounds();
    r.height += texte.getCharacterSize() / 2.0;
    r.top -= texte.getCharacterSize() / 8.0;
    _mouseHover = r.contains(event.mouseButton.x,event.mouseButton.y);
    _mouseClick = _mouseHover;
}
void BoutonLink::onMouseUp(sf::Event & event)
{
    if (event.type != Event::MouseButtonReleased
        || event.mouseButton.button != sf::Mouse::Left)
        return;
    if (_mouseHover && _mouseClick)
        launch_external_navigator(_lien);
    _mouseClick = false;
}


bool BoutonLink::isClicked(){return _mouseClick;}
bool BoutonLink::isHover(){return _mouseHover;}



void BoutonLink::updateGraphics()
{
    if (_mouseClick)
    {
        texte.setColor(sf::Color(187, 187, 187));
        texte.setStyle(sf::Text::Regular);
    }
    else if (_mouseHover)
    {
        texte.setColor(sf::Color(187, 187, 187));
        texte.setStyle(sf::Text::Underlined);
    }
    else
    {
        texte.setColor(sf::Color::White);
        texte.setStyle(sf::Text::Underlined);
    }
}

sf::Text & BoutonLink::getText()
{
    return texte;
}




void BoutonLink::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(texte, states);
}



