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

        static ofstream * _logfile;

        static void add_message(sf::String message, char out);
    public :

        static void out(sf::String message);
        static void err(sf::String message);
        static void err(sf::String message, string file, int line);

        static vector<sf::String> getLogMessages();

        static void initLogFile();
};

#endif // CONSOLE_H
