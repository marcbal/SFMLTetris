#include "fn_string.hpp"

// converti un string en un flottant
float string_to_float( const string & Str)
{
	float Dest;
    // créer un flux à partir de la chaîne donnée
    istringstream iss( Str );
    // tenter la conversion vers Dest
    iss >> Dest;
    return Dest;
}



int string_to_int( const string & Str)
{
	int Dest;
    // créer un flux à partir de la chaîne donnée
    istringstream iss( Str );
    // tenter la conversion vers Dest
    iss >> Dest;
    return Dest;
}

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




string to_string( bool value )
{
    return value ? "true" : "false";
}





vector<string> explode(const string& str, const char& ch)
{
    string suivant;
    vector<string> result;

    // pour chaque caractère dans la chaine
    for (string::const_iterator i = str.begin(); i != str.end(); i++) {
        // si on rencontre la chaine de séparation
        if (*i == ch) {
            // si on a eu des caractères depuis la précédente rencontre du caractère séparateur
            if (!suivant.empty()) {
                // on ajoute au résultat de la fonction
                result.push_back(suivant);
                suivant.clear();
            }
        } else {
            // on ajoute le caractère courant dans le résultat
            suivant += *i;
        }
    }
    if (!suivant.empty())
         result.push_back(suivant);
    return result;
}



vector<sf::String> explode(const sf::String& str, char32_t ch)
{
    sf::String suivant;
    vector<sf::String> result;

    // pour chaque caractère dans la chaine
    for (unsigned int i = 0; i != str.getSize(); i++) {
        // si on rencontre la chaine de séparation
        if (str[i] == ch) {
            // si on a eu des caractères depuis la précédente rencontre du caractère séparateur
            if (!suivant.isEmpty()) {
                // on ajoute au résultat de la fonction
                result.push_back(suivant);
                suivant.clear();
            }
        } else {
            // on ajoute le caractère courant dans le résultat
            suivant += str[i];
        }
    }
    if (!suivant.isEmpty())
         result.push_back(suivant);
    return result;
}



sf::String wordwrap(sf::String str, unsigned int width)
{
    if (width == 0)
        return str;


    vector<sf::String> lines = explode(str, U'\n');
    sf::String result = "";
    for (unsigned int i=0; i<lines.size(); i++)
    {
        while (lines[i].getSize()>width)
        {
            result += lines[i].toWideString().substr(0, width) + "\n";
            lines[i] = lines[i].toWideString().substr(width, lines[i].getSize()-width);
        }
        result += lines[i]+"\n";
    }

    return (sf::String)(result.toWideString().substr(0, result.getSize()-1)); // on retire le dernier \n
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


sf::String implode(vector<sf::String> & tabstr, sf::String ch)
{
	sf::String out;
	for (unsigned int i=0; i<tabstr.size(); i++)
	{
		if (i!=0)
			out += ch;
		out += tabstr[i];
	}
	return out;
}
