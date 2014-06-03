#ifndef BOUTONLINK_H
#define BOUTONLINK_H

#include "headers.hpp"

using namespace std;
using namespace sf;


void launch_external_navigator(string link);


class BoutonLink : public sf::Drawable
{
    private:
        bool _mouseHover;
        bool _mouseClick;

        sf::Text texte;

        string _lien;

        void updateGraphics();

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:
        BoutonLink(sf::Text t, string l);
        virtual ~BoutonLink();

        void onEvent(sf::Event & event);
        virtual void onMouseMove(sf::Event & event);
        virtual void onMouseDown(sf::Event & event);
        virtual void onMouseUp(sf::Event & event);


        bool isClicked();
        bool isHover();
        sf::Text & getText();
};

#endif // BOUTONLINK_H
