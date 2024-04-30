#include "fileManager.hpp"

#include <filesystem>

vector<string> listOfFiles(string dir){
    vector<string> files;
    if (!filesystem::is_directory(dir)) {
        return files;
    }
    for (const auto & entry : filesystem::directory_iterator(dir)) {
        files.push_back(entry.path().filename().string());
    }
    return files;
}


void makeDir(string dir)
{
    filesystem::create_directories(dir);
}
