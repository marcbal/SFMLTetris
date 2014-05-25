#include "ScreenScore.hpp"




ScreenScore::ScreenScore(sf::Vector2i * window_size, char *state, Scores * scores) :
    Menu(window_size, state),
    scoreTable(255/20+1)
{
    _scores = scores;

    _page = 0;

    titre.setString("Meilleurs scores");


    nbScorePerPage = 20;



    for (unsigned int i=0; i<scoreTable.size(); i++)
    {
        scoreTable[i].clear();

        for(int j=0; j<nbScorePerPage; j++)
        {
            sf::Text t;
            t.setCharacterSize(15);
            t.setFont(*Ressources::getDefaultFont());
            t.setColor(sf::Color::White);
            t.setString("");
            t.setPosition(20, j * (window_size->y -150) / nbScorePerPage + 70);
            scoreTable[i].push_back(t);
        }

    }

    menuElements.push_back(Bouton(sf::Vector2f(20, window_size->y-60), sf::Vector2f(100, 50), 20, _state, INDEX));
    menuElements[menuElements.size()-1].setText("Retour");

    menuElements.push_back(Bouton(sf::Vector2f(160, window_size->y-60), sf::Vector2f(50, 50), 25, (char*)&_pageChange, (char)-1));
    menuElements[menuElements.size()-1].setText(L"<");

    menuElements.push_back(Bouton(sf::Vector2f(220, window_size->y-60), sf::Vector2f(50, 50), 25, &_pageChange, (char)1));
    menuElements[menuElements.size()-1].setText(L">");
}


ScreenScore::~ScreenScore()
{

}






void ScreenScore::update()
{
    vector<RecordLine> scoreData = _scores->getScores();
    _max_page = (scoreData.size()-1)/20+1;

    if (_pageChange == 1 || _page > 0)
    _page += (int)_pageChange;
    _pageChange = (char)0;
    if (_page < 0) _page = 0;
    if (_page >= _max_page) _page = _max_page-1;



    for (unsigned int i=0; i<scoreTable[_page].size(); i++)
    {
        if (i+_page*nbScorePerPage<scoreData.size())
        {
            RecordLine l = scoreData[i+_page*nbScorePerPage];
            Time t = sf::seconds(l.time);
            scoreTable[_page][i].setString(to_string((int) (i+1+_page*nbScorePerPage))+" : "+(string)l.name+" - "+
                                    to_string((int)l.points)+" points - "+
                                    to_string((int)l.tetrominos)+" tetrominos - "+
                                    to_string((int)l.lines)+" ligne"+((l.lines>1)?"s":"")+" - "+
                                    formattedDuration(t));
        }
        else if (i+_page*nbScorePerPage < 255)
            scoreTable[_page][i].setString(to_string((int) (i+1+_page*nbScorePerPage))+" : -");
        else
            scoreTable[_page][i].setString("");

    }
}



void ScreenScore::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
        target.draw(titre, states);
        target.draw(menuElements[0], states); // bouton Retour
        if (_page > 0)
        target.draw(menuElements[1], states);
        if (_page < _max_page - 1)
        target.draw(menuElements[2], states);

    for (unsigned int i=0; i<scoreTable[_page].size(); i++)
        target.draw(scoreTable[_page][i], states);
}
