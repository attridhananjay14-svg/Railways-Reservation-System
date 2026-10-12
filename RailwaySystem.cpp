#include "RailwaySystem.h"
#include <iostream>
#include <sstream>
#include <limits>
using namespace std;

// Constructor
RailwaySystem::RailwaySystem()
    : nextTrainId(1), nextPassengerId(1),
      nextReservationId(1), storage("railway_data.txt") {

    for (int i = 1; i <= 20; i++) {
        Seat s;
        s.seatNo = i;
        s.coach = (i <= 10) ? "S1" : "S2";
        seats.push_back(s);
    }
}

// Find train
int RailwaySystem::findTrain(int id) {
    for (int i = 0; i < trains.size(); i++)
        if (trains[i].trainId == id)
            return i;

    return -1;
}

// Find passenger
int RailwaySystem::findPassenger(int id) {
    for (int i = 0; i < passengers.size(); i++)
        if (passengers[i].passengerId == id)
            return i;

    return -1;
}

// Add train
void RailwaySystem::addTrain() {
    Train t;
    t.trainId = nextTrainId++;

    cout << "Enter train name: ";
    getline(cin, t.name);

    cout << "Enter source: ";
    getline(cin, t.source);

    cout << "Enter destination: ";
    getline(cin, t.destination);

    trains.push_back(t);
    cout << "Train added successfully. ID: "
         << t.trainId << endl;
}

// Add passenger
void RailwaySystem::addPassenger() {
    Passenger p;
    p.passengerId = nextPassengerId++;

    cout << "Enter passenger name: ";
    getline(cin, p.name);

    cout << "Enter age: ";
    if (!(cin >> p.age) || p.age < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid age.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    passengers.push_back(p);

    cout << "Passenger added successfully. ID: "
         << p.passengerId << endl;
}

// Display records
void RailwaySystem::displayRecords() {
    cout << "\n--- TRAINS ---\n";
    for (const auto& t : trains)
        t.display();

    cout << "\n--- PASSENGERS ---\n";
    for (const auto& p : passengers)
        p.display();

    cout << "\n--- RESERVATIONS ---\n";
    for (const auto& r : reservations)
        r.display();
}

// Search records
void RailwaySystem::searchRecord() {
    int choice, id;

    cout << "1. Search Train\n2. Search Passenger\nChoice: ";
    cin >> choice;

    cout << "Enter ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 1) {
        int i = findTrain(id);

        if (i == -1)
            cout << "Train not found.\n";
        else
            trains[i].display();
    }
    else if (choice == 2) {
        int i = findPassenger(id);

        if (i == -1)
            cout << "Passenger not found.\n";
        else
            passengers[i].display();
    }
    else {
        cout << "Invalid choice.\n";
    }
}

// Update records
void RailwaySystem::updateRecord() {
    int choice, id;

    cout << "1. Update Train\n2. Update Passenger\nChoice: ";
    cin >> choice;

    cout << "Enter ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 1) {
        int i = findTrain(id);

        if (i == -1) {
            cout << "Train not found.\n";
            return;
        }

        cout << "New name: ";
        getline(cin, trains[i].name);

        cout << "New source: ";
        getline(cin, trains[i].source);

        cout << "New destination: ";
        getline(cin, trains[i].destination);

        cout << "Train updated.\n";
    }
    else if (choice == 2) {
        int i = findPassenger(id);

        if (i == -1) {
            cout << "Passenger not found.\n";
            return;
        }

        cout << "New name: ";
        getline(cin, passengers[i].name);

        cout << "New age: ";
        cin >> passengers[i].age;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Passenger updated.\n";
    }
    else {
        cout << "Invalid choice.\n";
    }
}

// Delete records
void RailwaySystem::deleteRecord() {
    int choice, id;

    cout << "1. Delete Train\n2. Delete Passenger\nChoice: ";
    cin >> choice;

    cout << "Enter ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 1) {
        int i = findTrain(id);

        if (i == -1) {
            cout << "Train not found.\n";
            return;
        }

        for (const auto& r : reservations) {
            if (r.active && r.trainId == id) {
                cout << "Cancel active tickets first.\n";
                return;
            }
        }

        trains.erase(trains.begin() + i);
        cout << "Train deleted.\n";
    }
    else if (choice == 2) {
        int i = findPassenger(id);

        if (i == -1) {
            cout << "Passenger not found.\n";
            return;
        }

        for (const auto& r : reservations) {
            if (r.active && r.passengerId == id) {
                cout << "Cancel active tickets first.\n";
                return;
            }
        }

        passengers.erase(passengers.begin() + i);
        cout << "Passenger deleted.\n";
    }
    else {
        cout << "Invalid choice.\n";
    }
}

// Book seat
void RailwaySystem::bookSeat() {
    if (trains.empty() || passengers.empty()) {
        cout << "Add a train and passenger first.\n";
        return;
    }

    int tid, pid, sn;

    cout << "\nAvailable trains:\n";
    for (const auto& t : trains)
        t.display();

    cout << "Enter train ID: ";
    cin >> tid;

    if (findTrain(tid) == -1) {
        cout << "Train not found.\n";
        return;
    }

    cout << "Enter passenger ID: ";
    cin >> pid;

    if (findPassenger(pid) == -1) {
        cout << "Passenger not found.\n";
        return;
    }

    cout << "\nAvailable seats:\n";

    for (const auto& s : seats) {
        bool occupied = false;

        for (const auto& r : reservations) {
            if (r.active && r.trainId == tid &&
                r.seatNo == s.seatNo) {
                occupied = true;
                break;
            }
        }

        if (!occupied)
            s.display();
    }

    cout << "Enter seat number: ";
    cin >> sn;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int seatIndex = -1;

    for (int i = 0; i < seats.size(); i++)
        if (seats[i].seatNo == sn)
            seatIndex = i;

    if (seatIndex == -1) {
        cout << "Invalid seat number.\n";
        return;
    }

    for (const auto& r : reservations) {
        if (r.active && r.trainId == tid && r.seatNo == sn) {
            cout << "Seat already booked.\n";
            return;
        }
    }

    Reservation r;
    r.reservationId = nextReservationId++;
    r.trainId = tid;
    r.passengerId = pid;
    r.seatNo = sn;
    r.fare = 500;
    r.active = true;

    reservations.push_back(r);

    cout << "Ticket booked successfully!\n";
    r.display();
}

// Cancel ticket
void RailwaySystem::cancelTicket() {
    int id;

    cout << "Enter reservation ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto& r : reservations) {
        if (r.reservationId == id && r.active) {
            r.cancel();
            cout << "Ticket cancelled successfully.\n";
            return;
        }
    }

    cout << "Reservation not found.\n";
}

// Generate report
void RailwaySystem::report() {
    int active = 0;
    double revenue = 0;

    for (const auto& r : reservations) {
        if (r.active) {
            active++;
            revenue += r.calculateFare();
        }
    }

    cout << "\n--- RAILWAY REPORT ---\n";
    cout << "Total trains: " << trains.size() << endl;
    cout << "Total passengers: " << passengers.size() << endl;
    cout << "Total reservations: " << reservations.size() << endl;
    cout << "Active reservations: " << active << endl;
    cout << "Revenue: Rs. " << revenue << endl;
}

// Save records
void RailwaySystem::save() {
    ostringstream out;

    out << nextTrainId << '\n'
        << nextPassengerId << '\n'
        << nextReservationId << '\n';

    out << trains.size() << '\n';
    for (const auto& t : trains)
        out << t.trainId << '\n' << t.name << '\n'
            << t.source << '\n' << t.destination << '\n';

    out << passengers.size() << '\n';
    for (const auto& p : passengers)
        out << p.passengerId << '\n'
            << p.name << '\n' << p.age << '\n';

    out << reservations.size() << '\n';
    for (const auto& r : reservations)
        out << r.reservationId << ' ' << r.trainId << ' '
            << r.passengerId << ' ' << r.seatNo << ' '
            << r.fare << ' ' << r.active << '\n';

    storage.save(out.str());
}

// Load records
void RailwaySystem::load() {
    string data = storage.load();

    if (data.empty())
        return;

    istringstream in(data);
    size_t count;

    if (!(in >> nextTrainId >> nextPassengerId
             >> nextReservationId))
        return;

    in.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Train> newTrains;
    vector<Passenger> newPassengers;
    vector<Reservation> newReservations;

    if (!(in >> count) || count > 10000)
        return;

    in.ignore(numeric_limits<streamsize>::max(), '\n');

    for (size_t i = 0; i < count; i++) {
        Train t;
        in >> t.trainId;
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        getline(in, t.name);
        getline(in, t.source);
        getline(in, t.destination);

        if (!in)
            return;

        newTrains.push_back(t);
    }

    if (!(in >> count) || count > 10000)
        return;

    in.ignore(numeric_limits<streamsize>::max(), '\n');

    for (size_t i = 0; i < count; i++) {
        Passenger p;
        in >> p.passengerId;
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        getline(in, p.name);
        in >> p.age;
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!in)
            return;

        newPassengers.push_back(p);
    }

    if (!(in >> count) || count > 100000)
        return;

    for (size_t i = 0; i < count; i++) {
        Reservation r;

        if (!(in >> r.reservationId >> r.trainId
                 >> r.passengerId >> r.seatNo
                 >> r.fare >> r.active))
            return;

        newReservations.push_back(r);
    }

    trains = newTrains;
    passengers = newPassengers;
    reservations = newReservations;

    cout << "Data loaded successfully.\n";
}

// Main menu
void RailwaySystem::run() {
    int choice;

    do {
        cout << "\n===== RAILWAY RESERVATION SYSTEM =====\n";
        cout << "1. Add Record\n";
        cout << "2. Display Records\n";
        cout << "3. Search Record\n";
        cout << "4. Update Record\n";
        cout << "5. Delete Record\n";
        cout << "6. Book / Cancel Ticket\n";
        cout << "7. Report\n";
        cout << "8. Save / Load\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a valid number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            int type;
            cout << "1. Add Train\n2. Add Passenger\nChoice: ";
            cin >> type;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (type == 1)
                addTrain();
            else if (type == 2)
                addPassenger();
            else
                cout << "Invalid choice.\n";
            break;
        }

        case 2:
            displayRecords();
            break;

        case 3:
            searchRecord();
            break;

        case 4:
            updateRecord();
            break;

        case 5:
            deleteRecord();
            break;

        case 6: {
            int action;
            cout << "1. Book Seat\n2. Cancel Ticket\nChoice: ";
            cin >> action;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (action == 1)
                bookSeat();
            else if (action == 2)
                cancelTicket();
            else
                cout << "Invalid choice.\n";
            break;
        }

        case 7:
            report();
            break;

        case 8: {
            int action;
            cout << "1. Save Data\n2. Load Data\nChoice: ";
            cin >> action;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (action == 1)
                save();
            else if (action == 2)
                load();
            else
                cout << "Invalid choice.\n";
            break;
        }

        case 9:
            save();
            cout << "Exiting system.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 9);
}