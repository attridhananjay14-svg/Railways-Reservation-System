#ifndef SEAT_H
#define SEAT_H

#include <iostream>
#include <string>
using namespace std;

class Seat {
public:
    int seatNo;
    string coach;
    bool reserved;

    Seat() {
        seatNo = 0;
        reserved = false;
    }

    void display() const {
        cout << "Seat Number: " << seatNo << endl;
        cout << "Coach: " << coach << endl;
        cout << "Status: "
             << (reserved ? "Reserved" : "Available")
             << endl;
    }

    bool reserve() {
        if (reserved)
            return false;

        reserved = true;
        return true;
    }
};

#endif