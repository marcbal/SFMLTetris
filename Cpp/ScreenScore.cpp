#include "ScreenScore.hpp"




ScreenScore::ScreenScore(sf::Vector2i * window_size, char *state, Scores * scores) :
    Menu(window_size, state),
    scoreTable(10)
{
    _scores = scores;


    sf::Font* font = new sf::Font();
    font->loadFromFile("res/LiberationMono-Regular.ttf");




    for (unsigned int i=0; i<scoreTable.size(); i++)
    {
        sf::Text t;
        t.setCharacterSize(15);
        t.setFont(*font);
        t.setColor(sf::Color::White);
        t.setString("gne");
        t.setPosition(20, i * (window_size->y -100) / scoreTable.size() + 20);
        scoreTable[i] = t;
    }

    menuElements.push_back(Bouton(sf::Vector2f(20, window_size->y-60), sf::Vector2f(100, 50), 20, _state, INDEX));
    menuElements[menuElements.size()-1].setText("Retour");
}


ScreenScore::~ScreenScore()
{

}





void ScreenScore::update()
{
    vector<RecordLine> scoreData = _scores->getScores();
    for (unsigned int i=0; i<scoreTable.size(); i++)
    {
        if (i<scoreData.size())
        {
            RecordLine l = scoreData[i];
            Time t = sf::seconds(l.time);
            scoreTable[i].setString(to_string((int) i+1)+" : "+(string)l.name+" - "+
                                    to_string((int)l.points)+" points - "+
                                    to_string((int)l.tetrominos)+" tetrominos - "+
                                    to_string((int)l.lines)+" ligne"+((l.lines>1)?"s":"")+" - "+
                                    formattedDuration(t));
        }
        else
        {
            scoreTable[i].setString("");
        }

    }
}



void ScreenScore::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned int i=0; i<scoreTable.size(); i++)
        target.draw(scoreTable[i]);

    for (unsigned int i=0; i<menuElements.size(); i++)
        target.draw(menuElements[i]);
}
