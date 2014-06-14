#include "fn_string.hpp"

#ifdef _WIN32
string to_string( int Value )
{
    std::ostringstream oss;
    oss << Value;
    return oss.str();
}
#endif

string to_string( int Value, unsigned int nb_car )
{
    std::ostringstream oss;
    oss << Value;
    string nb = oss.str();
    while (nb.size() < nb_car)
        nb = "0"+nb;

    return nb;
}

string to_string( int Value, string separateur_millier )
{
    std::ostringstream oss;
    oss << Value;
    string nb = oss.str();
    vector<string> milliers;
    while (nb.size()>3)
    {
        milliers.push_back(nb.substr(nb.size()-3));
        nb = nb.substr(0, nb.size()-3);
    }
    milliers.push_back(nb);

    int i=0, j=milliers.size()-1;
    while (i<j)
    {
        swap(milliers[i], milliers[j]);
        i++; j--;
    }

    nb = implode(milliers, separateur_millier);
    return nb;
}



string to_string( long long Value )
{
    std::ostringstream oss;
    oss << Value;
    return oss.str();
}

string to_string( double Value )
{
    std::ostringstream oss;
    oss << Value;
    return oss.str();
}


string to_string( bool Value )
{
    string r;
    if (Value)
		r = "true";
	else
		r = "false";

	return r;
}




string implode(vector<string> & tabstr, string ch)
{
	string out = "";
	for (unsigned int i=0; i<tabstr.size(); i++)
	{
		if (i!=0)
			out.append(ch);
		out.append(tabstr[i]);
	}
	return out;
}

