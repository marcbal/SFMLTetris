#include "Console.hpp"

#include "fileManager.hpp"


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
    add_message(message, false);
}
void Console::err(sf::String message)
{
    add_message(message, true);
}


void Console::err(sf::String message, string file, int line)
{
    add_message(message, true);
    add_message("-> in \"" + file + "\" line " + to_string(line), true);
}



void Console::add_message(sf::String message, bool error)
{

    sf::String fullMessage = "[" + to_string(_clock.getElapsedTime().asMilliseconds() / 1000.0f) + "] ";
    if (error)
        fullMessage += "[error] ";
    else
        fullMessage += "[info] ";

    fullMessage += message;

    vector<sf::String> splittedLines = explode(wordwrap(fullMessage, DEBUG_NB_CHAR_WIDTH), U'\n');

    _threadLock.lock(); /* cette fonction pouvant être appelé par plusieurs threads, on met des protections
            pour éviter que les lignes des messages se mélangent */
            
    // output to console
    (error ? cerr : cout) << fullMessage.toAnsiString() << endl;
    

    if (_logfile != nullptr && _logfile->is_open())
        (*_logfile) << fullMessage.toAnsiString() << endl;
    
    for (unsigned int i=0; i<splittedLines.size(); i++) {
        buffer_to_debugger.push_back(splittedLines[i]);
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
