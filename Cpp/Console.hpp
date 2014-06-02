#ifndef CONSOLE_H
#define CONSOLE_H



#include "headers.hpp"
#include "fn_string.hpp"

using namespace std;
using namespace sf;


class Console
{
    private :
        static vector<sf::String> buffer_to_debugger;
        static sf::Clock _clock;
        static sf::Mutex _threadLock;

        static void add_message(sf::String message, char out);
    public :

        static void out(sf::String message);
        static void err(sf::String message);

        static vector<sf::String> getLogMessages();
};

#endif // CONSOLE_H
