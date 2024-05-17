#include "event.h"
#include <string>
#include <fstream>

std::ostream& operator<<(std::ostream& out, const Event e) {
    out << e.time << ' ' << e.id;

    switch (e.id) {
    case 2:
    case 12: out << ' ' << e.clientName << ' ' << e.tableNumber; break;
    case 13: out << ' ' << e.errMsg; break;
    default: out << ' ' << e.clientName; break;
    }

    return out; 
}

std::istream& operator>>(std::istream& in, Event& e) {
    in >> e.time >> e.id >> e.clientName;

    if (e.id == 2) {
        in >> e.tableNumber;
    }

    return in; 
}

Event::Event(std::string time, short id) {
    this->time = time;
    this->id = id;
}

Event::Event(std::string time, const char* errMsg) {
    this->time = time;
    this->id = 13;
    this->errMsg = errMsg;
}

Event::Event(std::string time, short id, std::string clientName) {
    this->time = time;
    this->id = id;
    this->clientName = clientName;
}

Event::Event(std::string time, short id, std::string clientName, int tableNumber) {
    this->time = time;
    this->id = id;
    this->clientName = clientName;
    this->tableNumber = tableNumber;
}