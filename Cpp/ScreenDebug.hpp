#ifndef SCREENDEBUG_H
#define SCREENDEBUG_H

#include "headers.hpp"
#include "ScreenElement.hpp"
#include "Ressources.hpp"
#include "fn_time.hpp"




class ScreenDebug : public ScreenElement
{
    public:
        ScreenDebug(sf::Vector2i* window_size);
        virtual ~ScreenDebug();
        virtual void update();
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:

        vector<string> _console_lines;

        sf::Clock _FPSclock;
        sf::Clock _clock;

        sf::Text _debug_info;
        sf::RectangleShape _debug_info_background;

        sf::Text _console_text;
        sf::RectangleShape _console_text_background;



};



#endif // SCREENDEBUG_H
