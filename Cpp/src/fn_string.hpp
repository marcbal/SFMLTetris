#ifndef FN_STRING_HPP
#define FN_STRING_HPP


#include "headers.hpp"

using namespace std;


float string_to_float( const string & Str);

int string_to_int( const string & Str);

string to_string( int Value, unsigned int nb_car );

string to_string( int Value, string separateur_millier );

string to_string( bool Value );

vector<string> explode(const string& str, const char& ch);

vector<sf::String> explode(const sf::String& str, char32_t ch);

sf::String wordwrap(sf::String str, unsigned int width);

string implode(vector<string> & tabstr, string ch);

sf::String implode(vector<sf::String> & tabstr, sf::String ch);


#endif // FN_STRING_HPP
