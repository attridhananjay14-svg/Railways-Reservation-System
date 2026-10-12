#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
using namespace std;

class FileManager {
public:
    string filename;

    FileManager(string file);

    void save(string data);
    string load();
};

#endif