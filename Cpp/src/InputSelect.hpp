#ifndef INPUTSELECT_H
#define INPUTSELECT_H

#include "headers.hpp"
#include "Bouton.hpp"


class InputSelect : public sf::Drawable
{
    private:

        vector<Bouton> _boutonsValues;
        unsigned int _valSelected;
        unsigned int _valueFirtAff;
        unsigned int _nbValAff;
        Bouton _upBouton;
        Bouton _downBouton;
        sf::RectangleShape _ascenceur;
        sf::Vector2f _pos;
        sf::Vector2f _taille_elmt;
        sf::RectangleShape _selectedElmt;

        int heightUpDownBouton;

        char _action;


        void updateGraphics();
        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:
        InputSelect(sf::Vector2f pos, sf::Vector2f taille_1_elmt, unsigned int nb_aff_elmt, vector<string> values, unsigned int valueSelecte);
        virtual ~InputSelect();

        void onEvent(sf::Event & event);
        virtual void onMouseMove(sf::Event & event);
        virtual void onMouseDown(sf::Event & event);
        virtual void onMouseUp(sf::Event & event);


        unsigned int getValueSelected();
};

#endif // INPUTSELECT_H
