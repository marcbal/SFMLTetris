#include "MenuSettingsGraphic.hpp"

using namespace std;
using namespace sf;
MenuSettingsGraphic::MenuSettingsGraphic(sf::Vector2i * window_size,char *state,OpenGL_Manager * oGL):
    Menu(window_size,state),
    _activate3D(Vector2f(_window_size->x/2-200,200), Vector2f(20,20),oGL->getActivate()),
    textActivate3D(),
    _inclinaison(Vector2f(_window_size->x/2-200,290),Vector2f(400,24),-oGL->getInclinaison(),0,100),
    textInclinaison()
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


    textActivate3D.setCharacterSize(20);
    textActivate3D.setColor(sf::Color::White);
    textActivate3D.setFont(*Ressources::getDefaultFont());
    textActivate3D.setPosition(_window_size->x/2-160, 200);
    textActivate3D.setString("Activer la 3D ?");

    textInclinaison.setCharacterSize(20);
    textInclinaison.setColor(sf::Color::White);
    textInclinaison.setFont(*Ressources::getDefaultFont());
    textInclinaison.setPosition(_window_size->x/2-200, 250);
    textInclinaison.setString("Inclinaison de la matrice :");
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
    target.draw(textActivate3D,states);
    target.draw(textInclinaison,states);
}

