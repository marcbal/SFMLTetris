#ifndef _fileManager_hpp_
#define _fileManager_hpp_

#include "headers.hpp"

using namespace std;

vector<string> listOfFiles(string dir);

void makeDir(string dir);

string getUserDataPath();

string getGameDataPath();

string getGameDataPath(string relativePath);

#endif
