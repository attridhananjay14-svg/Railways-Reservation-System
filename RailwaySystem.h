#ifndef RAILWAYSYSTEM_H
#define RAILWAYSYSTEM_H

#include <vector>
#include "Train.h"
#include "Passenger.h"
#include "Seat.h"
#include "Reservation.h"
#include "FileManager.h"

using namespace std;

class RailwaySystem {
private:
    vector<Train> trains;
    vector<Passenger> passengers;
    vector<Seat> seats;
    vector<Reservation> reservations;

    int nextTrainId;
    int nextPassengerId;
    int nextReservationId;

    FileManager storage;

    int findTrain(int id);
    int findPassenger(int id);

    void addTrain();
    void addPassenger();
    void displayRecords();
    void searchRecord();
    void updateRecord();
    void deleteRecord();
    void bookSeat();
    void cancelTicket();
    void report();

public:
    RailwaySystem();

    void run();
    void save();
    void load();
};

#endif