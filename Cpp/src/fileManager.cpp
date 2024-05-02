#include "fileManager.hpp"

#include <filesystem>

#ifdef __unix__
    #include <pwd.h>
    #include <unistd.h>
#endif

vector<string> listOfFiles(string dir) {
    vector<string> files;
    if (!filesystem::is_directory(dir)) {
        return files;
    }
    for (const auto & entry : filesystem::directory_iterator(dir)) {
        files.push_back(entry.path().filename().string());
    }
    return files;
}


void makeDir(string dir) {
    filesystem::create_directories(dir);
}



string getUserDataPath() {
    string dir;
    #ifdef __unix__
        char *homedir;
        if ((homedir = getenv("HOME")) == nullptr) {
            homedir = getpwuid(getuid())->pw_dir;
        }
        dir = string(homedir);
    #elif defined(_WIN32) || defined(WIN32)
        char *appdata = getenv("APPDATA");
        if (appdata == nullptr) {
            Console::err("Unable to read environment variable APPDATA.");
        }
        dir = string(appdata);
    #endif
    return dir;
}


string getGameDataPath() {
    return (filesystem::path(getUserDataPath()) / DATA_DIR).string();
}

string getGameDataPath(string relativePath) {
    return (filesystem::path(getGameDataPath()) / relativePath).string();
}