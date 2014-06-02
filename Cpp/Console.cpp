#include "Console.hpp"


vector<string> Console::buffer_to_debugger;
sf::Clock Console::_clock;
sf::Mutex Console::_threadLock;



#ifdef SFML_STRING_HPP
void Console::out(sf::String message)
{
    wstring ws = message.toWideString();
    string s(ws.begin(), ws.end());
    add_message(s, 'o');
}
void Console::err(sf::String message)
{
    wstring ws = message.toWideString();
    string s(ws.begin(), ws.end());
    add_message(s, 'e');
}
#else
void Console::out(wstring message)
{
    string s(message.begin(), message.end());
    out(s);
}
void Console::err(wstring message)
{
    string s(message.begin(), message.end());
    err(s);
}

void Console::out(string message)
{
    add_message(message, 'o');
}
void Console::err(string message)
{
    add_message(message, 'e');
}
#endif



void Console::add_message(string message, char out)
{

    string init_out = "[" + to_string((int) (_clock.getElapsedTime().asSeconds())) + "] ";
    if (out == 'o')
        init_out += "[info] ";
    else if (out == 'e')
        init_out += "[error] ";

    vector<string> lines = explode(wordwrap(message, DEBUG_NB_CHAR_WIDTH - init_out.size()), '\n');
    _threadLock.lock(); /* cette fonction pouvant être appelé par plusieurs threads, on met des protection
            pour éviter que les lignes des messages se mélangent */
    for (unsigned int i=0; i<lines.size(); i++)
    {
        buffer_to_debugger.push_back(init_out + lines[i]);
        if (out == 'o')
            cout << init_out << lines[i] << endl;
        else if (out == 'e')
            cerr << init_out << lines[i] << endl;
    }

    _threadLock.unlock();
}



vector<string> Console::getLogMessages()
{
    _threadLock.lock();
    vector<string> r = buffer_to_debugger;
    buffer_to_debugger.clear();
    _threadLock.unlock();
    return r;

}
