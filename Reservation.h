#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
using namespace std;

class Reservation {
public:
    int reservationId;
    int trainId;
    int passengerId;
    int seatNo;
    double fare;
    bool active;

    Reservation() {
        reservationId = 0;
        trainId = 0;
        passengerId = 0;
        seatNo = 0;
        fare = 0;
        active = true;
    }

    double calculateFare() const {
        return fare;
    }

    void cancel() {
        active = false;
    }

    void display() const {
        cout << "Reservation ID: " << reservationId << endl;
        cout << "Train ID: " << trainId << endl;
        cout << "Passenger ID: " << passengerId << endl;
        cout << "Seat Number: " << seatNo << endl;
        cout << "Fare: Rs. " << fare << endl;
        cout << "Status: "
             << (active ? "Confirmed" : "Cancelled") << endl;
    }
};

#endif