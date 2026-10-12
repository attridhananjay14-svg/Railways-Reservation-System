#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <string>
using namespace std;

class Passenger {
public:
    int passengerId, age;
    string name;

    Passenger() {
        passengerId = 0;
        age = 0;
    }

    void display() const {
        cout << "Passenger ID: " << passengerId << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};

#endif