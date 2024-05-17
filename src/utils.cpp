#include "event/event.h"
#include <string>
#include <cmath>

int timeStringToInt(std::string t) {
    return (t[0] - '0') * 600
            + (t[1] - '0') * 60
            + (t[3] - '0') * 10
            + (t[4] - '0');
}

std::string timeIntToString(int t) {
    int hours = t / 60;
    int minutes = t - hours * 60;
    return (hours < 10 ? "0" : "") 
            + std::to_string(hours) 
            + ":" 
            + (minutes < 10 ? "0" : "") 
            + std::to_string(minutes);
}

bool validatePositiveInt(double num) {
    if (std::ceil(num) != std::trunc(num) || std::ceil(num) <= 0) {
        return false;
    }
    return true;
}


bool validateTime(std::string time) {
    if (time.size() != 5 ||
        time[2] != ':' || 
        time[0] < '0' || time[0] > '2' ||
        (time[0] == '2' && time[1] > '3') || 
        time[1] < '0' || time[1] > '9' ||
        time[3] < '0' || time[3] > '5' ||
        time[4] < '0' || time[4] > '9'
    ) {
        return false;
    }
    return true;
}

bool validateClientName(std::string name) {
    for (auto &ch : name) {
        if (!(
            (ch >= '0' && ch <= '9') || 
            (ch >= 'a' && ch <= 'z') || 
            ch == '_' || 
            ch == '-'
        )) {
            return false;
        }
    }
    return true;
}