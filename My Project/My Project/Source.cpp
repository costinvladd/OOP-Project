#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <vector>

class EventLocation {   //This is the EventLocation class representing the characteristics of the event location
private:
    int* seatsPerRow; //A dynamically allocated array
    int maxSeats;
    int numRows; //Statically defined numerical values
    int numZones;

public:
    EventLocation(int maxSeats, int numRows, int numZones, const int* seatsPerRow); //Constructor for initializing the event location.
    EventLocation(const EventLocation& other); //Copy constructor for creating a copy of an existing event location
    ~EventLocation(); //Destructor for cleaning up dynamically allocated memory

    int getMaxSeats() const;
    int getNumRows() const; //Accessor functions
    int getNumZones() const;
    const int* getSeatsPerRow() const;

    void display() const; //Method to display the details of the event location

    // Overloaded operators
    int operator[](int index) const;
    EventLocation& operator=(const EventLocation& other);
    friend std::ostream& operator<<(std::ostream& os, const EventLocation& location);
    bool operator==(const EventLocation& other) const;
};

EventLocation::EventLocation(int maxSeats, int numRows, int numZones, const int* seatsPerRow)
    : maxSeats(maxSeats), numRows(numRows), numZones(numZones) {
    this->seatsPerRow = new int[numRows]; //Allocating memory for seatsPerRow and copying values
    for (int i = 0; i < numRows; ++i) {
        this->seatsPerRow[i] = seatsPerRow[i];
    }
}

EventLocation::EventLocation(const EventLocation& other)
    : maxSeats(other.maxSeats), numRows(other.numRows), numZones(other.numZones) {
    this->seatsPerRow = new int[numRows];
    for (int i = 0; i < numRows; ++i) {
        this->seatsPerRow[i] = other.seatsPerRow[i];
    }
}

EventLocation::~EventLocation() {
    delete[] seatsPerRow;
}

int EventLocation::getMaxSeats() const {
    return maxSeats;
}

int EventLocation::getNumRows() const {
    return numRows;
}

int EventLocation::getNumZones() const {
    return numZones;
}

const int* EventLocation::getSeatsPerRow() const {
    return seatsPerRow;
}

void EventLocation::display() const {
    std::cout << "Event Location: Max Seats=" << maxSeats
        << ", Num Rows=" << numRows
        << ", Num Zones=" << numZones << std::endl;
    std::cout << "Seats per Row: ";
    for (int i = 0; i < numRows; ++i) {
        std::cout << seatsPerRow[i] << " ";
    }
    std::cout << std::endl;
}

int EventLocation::operator[](int index) const {
    if (index >= 0 && index < numRows) {
        return seatsPerRow[index];
    }
    else {
        // Handle out of bounds access
        std::cerr << "Error: Index out of bounds." << std::endl;
        return -1;  
    }
}

EventLocation& EventLocation::operator=(const EventLocation& other) {
    if (this != &other) {  
        maxSeats = other.maxSeats;
        numRows = other.numRows;
        numZones = other.numZones;

        delete[] seatsPerRow;

        seatsPerRow = new int[numRows];
        for (int i = 0; i < numRows; ++i) {
            seatsPerRow[i] = other.seatsPerRow[i];
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const EventLocation& location) {
    os << "Event Location: Max Seats=" << location.maxSeats
        << ", Num Rows=" << location.numRows
        << ", Num Zones=" << location.numZones << std::endl;
    os << "Seats per Row: ";
    for (int i = 0; i < location.numRows; ++i) {
        os << location.seatsPerRow[i] << " ";
    }
    os << std::endl;
    return os;
}

bool EventLocation::operator==(const EventLocation& other) const {
    return maxSeats == other.maxSeats &&
        numRows == other.numRows &&
        numZones == other.numZones &&
        std::equal(seatsPerRow, seatsPerRow + numRows, other.seatsPerRow);
}

int main() {
    EventLocation location(0, 0, 0, nullptr);
    Event event("", "", "");
    Ticket ticket("");

    
    return 0;
}
