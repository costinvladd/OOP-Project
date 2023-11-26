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
    if (index >= 0 && index < numRows) { //// Validation for out of bounds access
        return seatsPerRow[index];
    }
    else {
        
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

// Definition of the Event class
class Event {
private:
    char* eventName;
    char* eventDate;
    char* eventTime;

public:
    static const int MAX_STRING_LENGTH = 50;

    // Constructor: initializes an Event with the given name, date, and time
    Event(const char* eventName, const char* eventDate, const char* eventTime);

    // Copy constructor: creates a copy of another Event
    Event(const Event& other);

    // Destructor: cleans up dynamically allocated memory
    ~Event();

    // Getter methods for accessing event details
    const char* getEventName() const;
    const char* getEventDate() const;
    const char* getEventTime() const;

    // Display method: Prints the details of the event
    void display() const;

    // Overloaded assignment operator: assigns the values of another Event
    Event& operator=(const Event& other);

    // Overloaded operator <<: allows printing an Event to an ostream
    friend std::ostream& operator<<(std::ostream& os, const Event& event);

    // Overloaded  operator = : checks if two Events are equal
    bool operator==(const Event& other) const;
};

// Constructor implementation
Event::Event(const char* eventName, const char* eventDate, const char* eventTime) {
    // Allocating memory for the character arrays and copying values
    this->eventName = new char[MAX_STRING_LENGTH];
    this->eventDate = new char[MAX_STRING_LENGTH];
    this->eventTime = new char[MAX_STRING_LENGTH];

    strncpy(this->eventName, eventName, MAX_STRING_LENGTH);
    strncpy(this->eventDate, eventDate, MAX_STRING_LENGTH);
    strncpy(this->eventTime, eventTime, MAX_STRING_LENGTH);
}

// Copy constructor implementation
Event::Event(const Event& other) {
   
    eventName = new char[MAX_STRING_LENGTH];
    eventDate = new char[MAX_STRING_LENGTH];
    eventTime = new char[MAX_STRING_LENGTH];

    strncpy(eventName, other.eventName, MAX_STRING_LENGTH);
    strncpy(eventDate, other.eventDate, MAX_STRING_LENGTH);
    strncpy(eventTime, other.eventTime, MAX_STRING_LENGTH);
}

// Destructor implementation
Event::~Event() {
    // Deallocating memory for the character arrays
    delete[] eventName;
    delete[] eventDate;
    delete[] eventTime;
}

// Getter methods
const char* Event::getEventName() const {
    return eventName;
}

const char* Event::getEventDate() const {
    return eventDate;
}

const char* Event::getEventTime() const {
    return eventTime;
}

// Display methods 
void Event::display() const {
    std::cout << "Event: Name=" << eventName
        << ", Date=" << eventDate
        << ", Time=" << eventTime << std::endl;
}

// Overloaded operator =
Event& Event::operator=(const Event& other) {
    if (this != &other) {  // Check for self-assignment
        strncpy(eventName, other.eventName, MAX_STRING_LENGTH);
        strncpy(eventDate, other.eventDate, MAX_STRING_LENGTH);
        strncpy(eventTime, other.eventTime, MAX_STRING_LENGTH);
    }
    return *this;
}

// Overloaded operator <<
std::ostream& operator<<(std::ostream& os, const Event& event) {
    os << "Event: Name=" << event.eventName
        << ", Date=" << event.eventDate
        << ", Time=" << event.eventTime;
    return os;
}

// Overloaded operator ==
bool Event::operator==(const Event& other) const {
    return strncmp(eventName, other.eventName, MAX_STRING_LENGTH) == 0 &&
        strncmp(eventDate, other.eventDate, MAX_STRING_LENGTH) == 0 &&
        strncmp(eventTime, other.eventTime, MAX_STRING_LENGTH) == 0;
}


int main() {
    EventLocation location(0, 0, 0, nullptr);
    Event event("", "", "");


    
    return 0;
}
