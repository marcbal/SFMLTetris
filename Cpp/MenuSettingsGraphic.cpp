#include "MenuSettingsGraphic.hpp"

using namespace std;
using namespace sf;
MenuSettingsGraphic::MenuSettingsGraphic(sf::Vector2i * window_size,char *state,OpenGL_Manager * oGL):
    Menu(window_size,state),
    _activate3D(Vector2f(_window_size->x/2-7,260), Vector2f(15,15),oGL->getActivate()),
    _inclinaison(Vector2f(_window_size->x/2-150,200),Vector2f(300,20),-oGL->getInclinaison(),0,100)
{
    _oGL = oGL;

    menuElements.push_back(Bouton(sf::Vector2f(50, _window_size->y-120),
                                        sf::Vector2f(200, 30),
                                        18,
                                        _state));

    menuElements[0].setAction(SETTINGS);
    menuElements[0].setText(L"Retour");

    menuElements.push_back(Bouton(sf::Vector2f(50, _window_size->y-80),
                                        sf::Vector2f(200, 30),
                                        18,
                                        _state));

    menuElements[1].setAction(INDEX);
    menuElements[1].setText(L"Menu Principal");
}




void MenuSettingsGraphic::onEvent(Event & event){
    _activate3D.onEvent(event);
    _inclinaison.onEvent(event);
    Menu::onEvent(event);
    _oGL->setInclinaison(-_inclinaison.getValue());
    _oGL->setActivate(_activate3D.getValue());
}

void MenuSettingsGraphic::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Menu::draw(target,states);
    target.draw(_activate3D,states);
    target.draw(_inclinaison,states);
}

