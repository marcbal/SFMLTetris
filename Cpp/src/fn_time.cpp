#include "fn_time.hpp"


string formattedDuration(sf::Time time)
{
    return formattedDuration(time, 0);
}

string formattedDuration(sf::Time time, unsigned int nb_dec)
{
    float secondsF = time.asSeconds();

    int s = (int) secondsF;
    int tot_s = s;

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
        str += to_string(h, 2) + "h ";
    if (m>0 || h>0 || d>0)
        str += to_string(m, 2) + "m ";
    str += to_string(s, 2);

    if (nb_dec > 0)
    {
        int subsec = secondsF * pow(10.0, (double) nb_dec) - tot_s * pow(10.0, (double) nb_dec);
        str += "." + to_string(subsec, nb_dec);
    }
    str += "s";

    return str;
}
