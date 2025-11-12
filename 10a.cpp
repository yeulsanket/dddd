#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;


struct Booking {
    int bookingID;
    string passengerName;
    string flightNo;
    string date;
    string seatNo;
};

void addBooking() {
    Booking b;
    cout << "\nEnter Booking Details:\n";
    cout << "Booking ID: ";
    cin >> b.bookingID;
    cin.ignore();
    cout << "Passenger Name: ";
    getline(cin, b.passengerName);
    cout << "Flight No: ";
    getline(cin, b.flightNo);
    cout << "Date (DD/MM/YYYY): ";
    getline(cin, b.date);
    cout << "Seat No: ";
    getline(cin, b.seatNo);


    ofstream dataFile("bookings.dat", ios::app | ios::binary);
    ofstream indexFile("index.dat", ios::app);

    if (!dataFile || !indexFile) {
        cout << "❌ Error opening file!\n";
        return;
    }

    streampos pos = dataFile.tellp();

    // Write booking data
    dataFile.write((char*)&b, sizeof(b));

    // Write index entry: Booking_ID → position
    indexFile << b.bookingID << " " << pos << endl;

    dataFile.close();
    indexFile.close();
    cout << "✅ Booking added successfully!\n";
}

// Function to search a booking by Booking_ID
void searchBooking() {
    int searchID;
    cout << "\nEnter Booking ID to search: ";
    cin >> searchID;

    // Load index into map
    ifstream indexFile("index.dat");
    ifstream dataFile("bookings.dat", ios::binary);

    if (!indexFile || !dataFile) {
        cout << "❌ Error opening files!\n";
        return;
    }

    map<int, streampos> indexMap;
    int id;
    streampos pos;

    while (indexFile >> id >> pos) {
        indexMap[id] = pos;
    }

    // Search ID in map
    if (indexMap.find(searchID) != indexMap.end()) {
        dataFile.seekg(indexMap[searchID]);
        Booking b;
        dataFile.read((char*)&b, sizeof(b));

        cout << "\n✅ Booking Found:\n";
        cout << "Booking ID: " << b.bookingID << endl;
        cout << "Passenger Name: " << b.passengerName << endl;
        cout << "Flight No: " << b.flightNo << endl;
        cout << "Date: " << b.date << endl;
        cout << "Seat No: " << b.seatNo << endl;
    } else {
        cout << "❌ Booking ID not found.\n";
    }

    indexFile.close();
    dataFile.close();
}

// Function to display all bookings
void displayAll() {
    ifstream dataFile("bookings.dat", ios::binary);
    if (!dataFile) {
        cout << "❌ No bookings found.\n";
        return;
    }

    Booking b;
    cout << "\n📋 All Flight Bookings:\n";
    cout << "-------------------------------------------------------------\n";
    cout << "ID\tPassenger Name\tFlight No\tDate\t\tSeat No\n";
    cout << "-------------------------------------------------------------\n";

    while (dataFile.read((char*)&b, sizeof(b))) {
        cout << b.bookingID << "\t" << b.passengerName << "\t"
             << b.flightNo << "\t" << b.date << "\t" << b.seatNo << endl;
    }

    dataFile.close();
}

int main() {
    int choice;

    do {
        cout << "\n===== ✈️ FLIGHT BOOKING SYSTEM (Indexed Sequential File) =====\n";
        cout << "1. Add Booking\n";
        cout << "2. Search by Booking ID\n";
        cout << "3. Display All Bookings\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBooking();
            break;
        case 2:
            searchBooking();
            break;
        case 3:
            displayAll();
            break;
        case 4:
            cout << "👋 Exiting system...\n";
            break;
        default:
            cout << "❌ Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}