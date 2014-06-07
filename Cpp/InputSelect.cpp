#include "InputSelect.hpp"

InputSelect::InputSelect(sf::Vector2f pos, sf::Vector2f taille_1_elmt, unsigned int nb_aff_elmt, vector<string> values, unsigned int valueSelected):
    _selectedElmt(taille_1_elmt)
{
    _pos = pos;
    _action = -1;
    _taille_elmt = taille_1_elmt;
    _nbValAff = nb_aff_elmt;
    _valueFirtAff = 0;
    heightUpDownBouton = 25;
    _valSelected = valueSelected;

    _selectedElmt.setFillColor(sf::Color::White);

    _upBouton = Bouton(pos, sf::Vector2f(taille_1_elmt.x, heightUpDownBouton), 15, &_action, -2);
    _upBouton.setText(L"<<< Précédent");
    _downBouton = Bouton(pos + sf::Vector2f(0, heightUpDownBouton + _nbValAff * taille_1_elmt.y), sf::Vector2f(taille_1_elmt.x, heightUpDownBouton), 15, &_action, -3);
    _downBouton.setText(L"Suivant >>>");
    for (unsigned int i=0; i<values.size(); i++)
    {
        _boutonsValues.push_back(Bouton(pos+sf::Vector2f(0, heightUpDownBouton + (i-_valueFirtAff) * taille_1_elmt.y),
                                        taille_1_elmt,
                                        14, &_action, (char)i));
        _boutonsValues[_boutonsValues.size()-1].setText(values[i].substr(0, 50));
        if (i == valueSelected)
            _selectedElmt.setPosition(pos+sf::Vector2f(0, heightUpDownBouton + (i-_valueFirtAff) * taille_1_elmt.y));
    }
}

InputSelect::~InputSelect()
{

}



void InputSelect::updateGraphics()
{

    for (unsigned int i=_valueFirtAff; i<_valueFirtAff+_nbValAff && i<_boutonsValues.size(); i++)
        _boutonsValues[i].setPosition(_pos+sf::Vector2f(0, heightUpDownBouton + (i-_valueFirtAff) * _taille_elmt.y));
    _selectedElmt.setPosition(_pos+sf::Vector2f(0, heightUpDownBouton + (_valSelected-_valueFirtAff) * _taille_elmt.y));
}
void InputSelect::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (_valSelected >= _valueFirtAff && _valSelected < _valueFirtAff+_nbValAff)
        target.draw(_selectedElmt, states);
    if (_valueFirtAff>0)
        target.draw(_upBouton, states);
    if (_valueFirtAff+_nbValAff < _boutonsValues.size())
        target.draw(_downBouton, states);
    for (unsigned int i=_valueFirtAff; i<_valueFirtAff+_nbValAff && i<_boutonsValues.size(); i++)
        target.draw(_boutonsValues[i], states);
}

void InputSelect::onEvent(sf::Event & event)
{
    // évènement des boutons
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

    // traitement des actions des boutons

    // up
    if (_action == -2 && _valueFirtAff > 0)
        _valueFirtAff--;
    // down
    else if (_action == -3 && _valueFirtAff+_nbValAff < _boutonsValues.size())
        _valueFirtAff++;
    // select new val
    else if (_action >= 0 && _action < _boutonsValues.size())
        _valSelected = (int) _action;
    if (_action != -1)
        updateGraphics();

    _action = -1;
}
void InputSelect::onMouseMove(sf::Event & event)
{
    if (event.type != Event::MouseMoved)
        return;

    for (unsigned int i=_valueFirtAff; i<_valueFirtAff+_nbValAff && i<_boutonsValues.size(); i++)
    {
        _boutonsValues[i].onMouseMove(event);
    }
    _upBouton.onMouseMove(event);
    _downBouton.onMouseMove(event);
}
void InputSelect::onMouseDown(sf::Event & event)
{
    if (event.type != Event::MouseButtonPressed)
        return;

    for (unsigned int i=_valueFirtAff; i<_valueFirtAff+_nbValAff && i<_boutonsValues.size(); i++)
    {
        _boutonsValues[i].onMouseDown(event);
    }
    _upBouton.onMouseDown(event);
    _downBouton.onMouseDown(event);
}
void InputSelect::onMouseUp(sf::Event & event)
{
    if (event.type != Event::MouseButtonReleased)
        return;

    for (unsigned int i=_valueFirtAff; i<_valueFirtAff+_nbValAff && i<_boutonsValues.size(); i++)
    {
        _boutonsValues[i].onMouseUp(event);
    }
    _upBouton.onMouseUp(event);
    _downBouton.onMouseUp(event);
}


unsigned int InputSelect::getValueSelected()
{
    return _valSelected;
}
