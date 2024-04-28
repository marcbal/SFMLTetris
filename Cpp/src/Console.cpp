#include "Console.hpp"


vector<sf::String> Console::buffer_to_debugger;
sf::Clock Console::_clock;
sf::Mutex Console::_threadLock;
ofstream * Console::_logfile = nullptr;



void Console::initLogFile()
{
    makeDir("logs");
    if (_logfile == nullptr)
    {
        _logfile = new ofstream(("logs/"+to_string((int)time(NULL))+".log").c_str(), ios::out | ios::trunc);
        if (!_logfile->is_open())
            Console::err(L"Impossible d'accéder au fichier log pour écriture.");
    }
}




void Console::out(sf::String message)
{
    add_message(message, 'o');
}
void Console::err(sf::String message)
{
    add_message(message, 'e');
}


void Console::err(sf::String message, string file, int line)
{
    add_message(message, 'e');
    add_message("-> in \"" + file + "\" line " + to_string(line), 'e');
}



void Console::add_message(sf::String message, char out)
{

    sf::String init_out = "[" + to_string((int) (_clock.getElapsedTime().asSeconds())) + "] ";
    if (out == 'o')
        init_out += "[info] ";
    else if (out == 'e')
        init_out += "[error] ";

    vector<sf::String> lines = explode(wordwrap(message, DEBUG_NB_CHAR_WIDTH - init_out.getSize()), U'\n');
    _threadLock.lock(); /* cette fonction pouvant être appelé par plusieurs threads, on met des protection
            pour éviter que les lignes des messages se mélangent */
    for (unsigned int i=0; i<lines.size(); i++)
    {
        buffer_to_debugger.push_back(init_out + lines[i]);
        if (out == 'o')
        {
            cout << init_out.toAnsiString() << lines[i].toAnsiString() << endl;
        }
        else if (out == 'e')
            cerr << init_out.toAnsiString() << lines[i].toAnsiString() << endl;

        if (_logfile != nullptr && _logfile->is_open())
            (*_logfile) << init_out.toAnsiString() << lines[i].toAnsiString() << endl;
    }

    _threadLock.unlock();
}



vector<sf::String> Console::getLogMessages()
{
    _threadLock.lock();
    vector<sf::String> r = buffer_to_debugger;
    buffer_to_debugger.clear();
    _threadLock.unlock();
    return r;

}
