#ifndef CONSOLE_H
#define CONSOLE_H



#include "headers.hpp"
#include "fn_string.hpp"

using namespace std;
using namespace sf;


class Console
{
    private :
        static vector<string> buffer_to_debugger;
        static sf::Clock _clock;
        static sf::Mutex _threadLock;

        static void add_message(string message, char out);
    public :

        // pas nécessaire avec sf::String apparament :
        #ifdef SFML_STRING_HPP
        static void out(sf::String message);
        static void err(sf::String message);
        #else
        static void out(string message);
        static void err(string message);

        static void out(wstring message);
        static void err(wstring message);
        #endif

        static vector<string> getLogMessages();
};

#endif // CONSOLE_H
