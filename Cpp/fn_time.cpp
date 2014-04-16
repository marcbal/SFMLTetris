#include "fn_time.hpp"

string formattedDuration(sf::Time time)
{
    float secondsF = time.asSeconds();

    int s = (int) secondsF;

    int d = s/86400;
    s -= d*86400;
    int h = s/3600;
    s -= h*3600;
    int m = s/60;
    s -= m*60;

    string str = "";
    if (d>0)
        str += to_string(d) + "j ";
    if (h>0 || d>0)
        str += to_string(h, 2) + ":";
    if (m>0 || h>0 || d>0)
        str += to_string(m, 2) + ":";
    str += to_string(s, 2);

    return str;
}
