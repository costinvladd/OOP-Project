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

    int operator[](int index) const;
    EventLocation& operator=(const EventLocation& other);
    friend std::ostream& operator<<(std::ostream& os, const EventLocation& location);
    bool operator==(const EventLocation& other) const;
};

EventLocation::EventLocation(int maxSeats, int numRows, int numZones, const int* seatsPerRow)
    : maxSeats(maxSeats), numRows(numRows), numZones(numZones) {
    this->seatsPerRow = new int[numRows];
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
    } else {
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

class Event {
public:
    static const int MAX_STRING_LENGTH = 50;

private:
    char* eventName;
    char* eventDate;
    char* eventTime;

public:
    Event(const char* eventName, const char* eventDate, const char* eventTime);
    Event(const Event& other);
    ~Event();

    const char* getEventName() const;
    const char* getEventDate() const;
    const char* getEventTime() const;

    void display() const;

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
    if (this != &other) {
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

    virtual void display() const = 0;

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
    if (this != &other) {
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

class FootballTicket : public Ticket {
private:
    int stand;
    int row;
    int seat;

public:
    FootballTicket(const char* ticketType, int stand, int row, int seat);
    ~FootballTicket();

    int getStand() const;
    int getRow() const;
    int getSeat() const;

    void display() const override;
};

FootballTicket::FootballTicket(const char* ticketType, int stand, int row, int seat)
    : Ticket(ticketType), stand(stand), row(row), seat(seat) {}

FootballTicket::~FootballTicket() {}

int FootballTicket::getStand() const {
    return stand;
}

int FootballTicket::getRow() const {
    return row;
}

int FootballTicket::getSeat() const {
    return seat;
}

void FootballTicket::display() const {
    std::cout << "Football Ticket - " << *this << ", Stand=" << stand
              << ", Row=" << row << ", Seat=" << seat << std::endl;
}

int main() {
    return 0;
}
