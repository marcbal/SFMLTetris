#ifndef FN_STRING_HPP
#define FN_STRING_HPP

#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;


float string_to_float( const string & Str);

int string_to_int( const string & Str);

string to_string( int Value );

string to_string( int Value, unsigned int nb_car );

string to_string( long long Value );

string to_string( double Value );

string to_string( bool Value );

void compter_voyelles_consonnes(string mot, int& voyelles, int& consonnes);

int nombre_car_mot(string mot, char l);

bool sont_anagramme(string mot1, string mot2);

vector<string> explode(const string& str, const char& ch);

string implode(vector<string> & tabstr, string ch);

int nombre_mot(string & chaine);

bool sont_palindrome(string mot);

// compte le nombre d'occurence se pattern dans chaine
int substr_count(string chaine, string pattern);

map<string, int> iterration_mots(string texte);

#endif // FN_STRING_HPP
