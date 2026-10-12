#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <string>
using namespace std;

class Train {
public:
    int trainId;
    string name, source, destination;

    Train() {
        trainId = 0;
    }

    void display() const {
        cout << "Train ID: " << trainId << endl;
        cout << "Name: " << name << endl;
        cout << "Source: " << source << endl;
        cout << "Destination: " << destination << endl;
    }
};

#endif