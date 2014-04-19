#ifndef _fileManager_hpp_
#define _fileManager_hpp_
#include <vector>
#include <string>

#include <dirent.h>

#ifndef WIN32
    #include <sys/types.h>
#endif

using namespace std;
//using namespace std;

vector<string> listOfFiles(string dir);

#endif
