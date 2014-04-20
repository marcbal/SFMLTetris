#include "fileManager.hpp"

vector<string> listOfFiles(string dir){
    vector<string> files;
    DIR* rep = NULL;
    rep = opendir(dir.c_str());
    if(rep==NULL)
        return files;
    struct dirent* fichierLu = NULL;
    while ((fichierLu = readdir(rep)) != NULL)
        files.push_back(fichierLu->d_name);
    return files;
}
