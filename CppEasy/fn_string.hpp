#ifndef FN_STRING_HPP
#define FN_STRING_HPP


#include "headers.hpp"

using namespace std;

#ifdef _WIN32
string to_string( int Value );
#endif

string to_string( int Value, unsigned int nb_car );

string to_string( int Value, string separateur_millier );

string to_string( long long Value );

string to_string( double Value );

string to_string( bool Value );

string implode(vector<string> & tabstr, string ch);

#endif // FN_STRING_HPP
