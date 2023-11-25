#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <vector>

class EventLocation {
private:
    int* seatsPerRow;
    int maxSeats;
    int numRows;
    int numZones;

public:
    EventLocation(int maxSeats, int numRows, int numZones, const int* seatsPerRow);
    EventLocation(const EventLocation& other);
    ~EventLocation();

    int getMaxSeats() const;
    int getNumRows() const;
    int getNumZones() const;
    const int* getSeatsPerRow() const;

    void display() const;

    // Overloaded operators
    int operator[](int index) const;
    EventLocation& operator=(const EventLocation& other);
    friend std::ostream& operator<<(std::ostream& os, const EventLocation& location);
    bool operator==(const EventLocation& other) const;
};

EventLocation::EventLocation(int maxSeats, int numRows, int numZones, const int* seatsPerRow)
    : maxSeats(maxSeats), numRows(numRows), numZones(numZones) {
    // Allocate memory for seatsPerRow and copy values
    this->seatsPerRow = new int[numRows];
    for (int i = 0; i < numRows; ++i) {
        this->seatsPerRow[i] = seatsPerRow[i];
    }
}

EventLocation::EventLocation(const EventLocation& other)
    : maxSeats(other.maxSeats), numRows(other.numRows), numZones(other.numZones) {
    // Allocate memory for seatsPerRow and copy values
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
        return -1;  // You can throw an exception instead if you prefer
    }
}

EventLocation& EventLocation::operator=(const EventLocation& other) {
    if (this != &other) {  // self-assignment check
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

class Event {
private:
    char* eventName;
    char* eventDate;
    char* eventTime;

public:
    static const int MAX_STRING_LENGTH = 50;

    Event(const char* eventName, const char* eventDate, const char* eventTime);
    Event(const Event& other);
    ~Event();

    const char* getEventName() const;
    const char* getEventDate() const;
    const char* getEventTime() const;

    void display() const;

    // Overloaded operators
    Event& operator=(const Event& other);
    friend std::ostream& operator<<(std::ostream& os, const Event& event);
    bool operator==(const Event& other) const;
};

Event::Event(const char* eventName, const char* eventDate, const char* eventTime) {
    this->eventName = new char[MAX_STRING_LENGTH];
    this->eventDate = new char[MAX_STRING_LENGTH];
    this->eventTime = new char[MAX_STRING_LENGTH];

    strncpy(this->eventName, eventName, MAX_STRING_LENGTH);
    strncpy(this->eventDate, eventDate, MAX_STRING_LENGTH);
    strncpy(this->eventTime, eventTime, MAX_STRING_LENGTH);
}

Event::Event(const Event& other) {
    eventName = new char[MAX_STRING_LENGTH];
    eventDate = new char[MAX_STRING_LENGTH];
    eventTime = new char[MAX_STRING_LENGTH];

    strncpy(eventName, other.eventName, MAX_STRING_LENGTH);
    strncpy(eventDate, other.eventDate, MAX_STRING_LENGTH);
    strncpy(eventTime, other.eventTime, MAX_STRING_LENGTH);
}

Event::~Event() {
    delete[] eventName;
    delete[] eventDate;
    delete[] eventTime;
}

const char* Event::getEventName() const {
    return eventName;
}

const char* Event::getEventDate() const {
    return eventDate;
}

const char* Event::getEventTime() const {
    return eventTime;
}

void Event::display() const {
    std::cout << "Event: Name=" << eventName
        << ", Date=" << eventDate
        << ", Time=" << eventTime << std::endl;
}

Event& Event::operator=(const Event& other) {
    if (this != &other) {  // self-assignment check
        strncpy(eventName, other.eventName, MAX_STRING_LENGTH);
        strncpy(eventDate, other.eventDate, MAX_STRING_LENGTH);
        strncpy(eventTime, other.eventTime, MAX_STRING_LENGTH);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Event& event) {
    os << "Event: Name=" << event.eventName
        << ", Date=" << event.eventDate
        << ", Time=" << event.eventTime;
    return os;
}

bool Event::operator==(const Event& other) const {
    return strncmp(eventName, other.eventName, MAX_STRING_LENGTH) == 0 &&
        strncmp(eventDate, other.eventDate, MAX_STRING_LENGTH) == 0 &&
        strncmp(eventTime, other.eventTime, MAX_STRING_LENGTH) == 0;
}

class Ticket {
private:
    static int nextTicketId;
    int ticketId;
    char* ticketType;

public:
    Ticket(const char* ticketType);
    ~Ticket();

    int getTicketId() const;
    const char* getTicketType() const;

    void display() const;

    // Overloaded operators
    Ticket& operator=(const Ticket& other);
    friend std::ostream& operator<<(std::ostream& os, const Ticket& ticket);
    bool operator==(const Ticket& other) const;
};

int Ticket::nextTicketId = 1;

Ticket::Ticket(const char* ticketType) {
    this->ticketType = new char[Event::MAX_STRING_LENGTH];
    strncpy(this->ticketType, ticketType, Event::MAX_STRING_LENGTH);

    this->ticketId = nextTicketId++;
}

Ticket::~Ticket() {
    delete[] ticketType;
}

int Ticket::getTicketId() const {
    return ticketId;
}

const char* Ticket::getTicketType() const {
    return ticketType;
}

void Ticket::display() const {
    std::cout << "Ticket ID=" << ticketId << ", Type=" << ticketType << std::endl;
}

Ticket& Ticket::operator=(const Ticket& other) {
    if (this != &other) {  // self-assignment check
        strncpy(ticketType, other.ticketType, Event::MAX_STRING_LENGTH);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Ticket& ticket) {
    os << "Ticket ID=" << ticket.ticketId << ", Type=" << ticket.ticketType;
    return os;
}

bool Ticket::operator==(const Ticket& other) const {
    return ticketId == other.ticketId &&
        strncmp(ticketType, other.ticketType, Event::MAX_STRING_LENGTH) == 0;
}

void displayMenu() {
    std::cout << "\nMENU\n";
    std::cout << "1. Enter Event Location Characteristics\n";
    std::cout << "2. Enter Event Characteristics\n";
    std::cout << "3. Generate and Validate Tickets\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    EventLocation location(0, 0, 0, nullptr);
    Event event("", "", "");
    Ticket ticket("");

    int choice;
    int* seatsPerRow = nullptr;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter maxSeats, numRows, numZones: ";
            int maxSeats, numRows, numZones;
            std::cin >> maxSeats >> numRows >> numZones;

            if (location.getSeatsPerRow() != nullptr) {
                delete[] location.getSeatsPerRow();
            }

            seatsPerRow = new int[numRows];
            std::cout << "Enter seats per row: ";
            for (int i = 0; i < numRows; ++i) {
                std::cin >> seatsPerRow[i];
            }

            location = EventLocation(maxSeats, numRows, numZones, seatsPerRow);
            break;

        case 2:
            char name[Event::MAX_STRING_LENGTH];
            char date[Event::MAX_STRING_LENGTH];
            char time[Event::MAX_STRING_LENGTH];

            std::cout << "Enter event name: ";
            std::cin >> name;

            std::cout << "Enter event date: ";
            std::cin >> date;

            std::cout << "Enter event time: ";
            std::cin >> time;

            event = Event(name, date, time);
            break;

        case 3:
            std::cout << "Enter ticket type: ";
            char type[Event::MAX_STRING_LENGTH];
            std::cin >> type;

            ticket = Ticket(type);

            std::cout << "Generated Ticket: ";
            ticket.display();
            break;

        case 4:
            std::cout << "Exiting...\n";
            break;

        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
