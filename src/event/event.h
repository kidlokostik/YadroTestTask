#ifndef _EVENT_H
#define _EVENT_H
#include <string>

struct Event {
    std::string time, clientName;
    int tableNumber;
    short id;
    const char* errMsg;
    Event(){};
    Event(std::string, const char*);
    Event(std::string, short);
    Event(std::string, short, std::string);
    Event(std::string, short, std::string, int);
    ~Event(){};
};

std::ostream& operator<<(std::ostream&, const Event);

std::istream& operator>>(std::istream&, Event&);
#endif