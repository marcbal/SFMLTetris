#ifndef SCREENSCORE_H
#define SCREENSCORE_H

#include "headers.hpp"

#include "fn_time.hpp"
#include "Menu.hpp"
#include "Bouton.hpp"
#include "BoutonLink.hpp"
#include "Scores.hpp"


class ScreenScore : public Menu
{
    public:
        ScreenScore(sf::Vector2i * window_size, char *state, Scores * scores);
        virtual ~ScreenScore();


        virtual void update();

        virtual void onEvent(sf::Event & event);


    protected:
    private:

        Scores * _scores;
        vector<vector<sf::Text> > scoreTable;
        BoutonLink lien;
        unsigned int _page;
        unsigned int _max_page;
        unsigned int nbScorePerPage;
        char _pageChange;

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // SCREENSCORE_H
