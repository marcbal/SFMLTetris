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




string to_string( bool Value )
{
    string r;
    if (Value)
		r = "true";
	else
		r = "false";

	return r;
}




int nombre_car_mot(string mot, char l)
{
	int max = mot.size();
	int count = 0;
	for (int i=0; i<max; i++)
	{
		count += (mot[i] == l);
	}
	return count;
}





bool sont_anagramme(string mot1, string mot2)
{
	if (mot1.size() != mot2.size())
		return false;
	for (unsigned int i=0;i<mot1.size();i++){mot1[i]=toupper(mot1[i]);}
	for (unsigned int i=0;i<mot2.size();i++){mot2[i]=toupper(mot2[i]);}
	// 2 méthodes
	// -------------------
	// lettre par lettre (A, B, ...), on compte leurs ittération dans les 2 mots et on compare, puis on continue si ==
	//*
	string car = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	bool anagramme = true;
	int i = 0;
	while (i<26 && anagramme)
	{
		if (!(nombre_car_mot(mot1, car[i]) == nombre_car_mot(mot2, car[i])))
			return false;
		i++;
	}
	// -------------------- */
	// on compare la taille des 2 mots (.size()). Si ==, on trie les lettres des 2 mots et on compare.


	return anagramme;
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



string wordwrap(string str, unsigned int width)
{
    if (width == 0)
        return str;


    vector<string> lines = explode(str, '\n');
    string result = "";
    for (unsigned int i=0; i<lines.size(); i++)
    {
        while (lines[i].size()>width)
        {
            result += lines[i].substr(0, width) + "\n";
            lines[i] = lines[i].substr(width, lines[i].size()-width);
        }
        result += lines[i]+"\n";
    }

    return result.substr(0, result.size()-1); // on retire le dernier \n
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



int nombre_mot(string & chaine)
{
	vector<string> mots = explode(chaine, ' ');
	return mots.size();
}




bool sont_palindrome(string mot)
{
	int max=mot.size()/2;
	int i=0;
	do
	{
		if (mot[i] != mot[mot.size()-1-i])
			return false;
		i++;
	} while (i<max);
	return true;
}



// compte le nombre d'occurence se pattern dans chaine
int substr_count(string chaine, string pattern)
{
	if (chaine.size() == 0 || pattern.size() == 0 || chaine.size() < pattern.size())
		return 0;

	int max = chaine.size()-pattern.size(), count = 0;

	for (int i = 0; i<= max; i++)
	{
		bool match = true;
		int j = 0;
		int i2 = i;
		int max2 = pattern.size();
		while (j<max2 && match)
		{
			if (chaine[i2+j] != pattern[j])
				match = false;
			j++;

		}
		if (match)
			count++;
	}
	return count;
}







map<string, int> iterration_mots(string texte)
{
	map<string, int> it_mots;

	vector<string> lignes = explode(texte, '\n');

	for (unsigned int l=0; l<lignes.size(); l++)
	{
		string ligne = lignes[l];
		vector<string> mots_ligne = explode(ligne, ' ');
		for (unsigned int i=0; i<mots_ligne.size(); i++)
		{
			if (it_mots.find(mots_ligne[i]) != it_mots.end()) // le mot est déjà dans le map
				it_mots[mots_ligne[i]]++;
			else
				it_mots[mots_ligne[i]] = 1;

		}

	}


	return it_mots;
}


string str_replace_car(char match, char replaced, string str)
{
    for (unsigned int i=0; i<str.size(); i++)
        if (str[i]==match)
            str[i]=replaced;
    return str;
}

