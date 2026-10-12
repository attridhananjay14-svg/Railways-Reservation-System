#include "FileManager.h"
#include <fstream>
#include <iostream>
using namespace std;

FileManager::FileManager(string file) {
    filename = file;
}

void FileManager::save(string data) {
    ofstream file(filename);

    if (file.is_open()) {
        file << data;
        file.close();
        cout << "Data saved successfully." << endl;
    } else {
        cout << "Error saving data." << endl;
    }
}

string FileManager::load() {
    ifstream file(filename);
    string data, line;

    if (!file.is_open()) {
        cout << "No saved data found." << endl;
        return "";
    }

    while (getline(file, line)) {
        data += line + "\n";
    }

    file.close();
    return data;
}