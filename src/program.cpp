#include "event/event.h"
#include "utils.cpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <queue>

std::stringstream ss;

std::stringstream& runProgram(char* inputFile) {
    std::ifstream inFile(inputFile);

    if (!inFile.is_open()) {
        throw "Файл не открывается!";
    }

    int tablesNumber, busyTablesNumber, cost;
    double tmpTablesNumber;
    inFile >> tmpTablesNumber;

    if (!validatePositiveInt(tmpTablesNumber)) {
        throw tmpTablesNumber;
    }
    tablesNumber = int(tmpTablesNumber);
    busyTablesNumber = 0;

    std::pair<std::string, std::string>* tables = new std::pair<std::string, std::string>[tablesNumber];
    std::pair<int, int>* tablesRevenue = new std::pair<int, int>[tablesNumber];
    for (int i = 0; i < tablesNumber; ++i) {
        tables[i] = std::make_pair("", "");
        tablesRevenue[i] = std::make_pair(0, 0);
    }

    // N = 0 - клиент пришёл / ожидает
    // N > 0 - клиент сидит за столом с номером N
    std::unordered_map<std::string, int> clientsState; 

    std::string sTime, eTime;
    inFile >> sTime >> eTime;
    if (!validateTime(sTime) || !validateTime(eTime)) {
        throw sTime + ' ' + eTime;
    }

    int startTime = timeStringToInt(sTime), endTime = timeStringToInt(eTime);
    if (endTime < startTime) {
        throw sTime + ' ' + eTime;
    }

    double tmpCost;
    inFile >> tmpCost;
    if (!validatePositiveInt(tmpCost)) {
        throw tmpCost;
    }
    cost = int(tmpCost);

    Event currentEvent;
    std::vector<Event> events;
    std::queue<std::string> waitingRoom; 

    std::string line;
    std::getline(inFile, line);
    while (std::getline(inFile, line, '\n')) {
        std::istringstream iss(line);

        std::string tmpTime, tmpClientName;
        double tmpID;
        if (!(iss >> tmpTime >> tmpID >> tmpClientName) ||
            !validateTime(tmpTime) || 
            !validateClientName(tmpClientName) || 
            !validatePositiveInt(tmpID) || 
            tmpID > 4) {
            throw line;
        }
        currentEvent = Event(tmpTime, (char)tmpID, tmpClientName);

        if (tmpID == (char)2) {
            int tmpTableNumber;
            if (!(iss >> tmpTableNumber) || 
                !validatePositiveInt(tmpTableNumber) || 
                tmpTableNumber > tablesNumber) {
                throw line;
            }
            currentEvent.tableNumber = tmpTableNumber;
        }
        if (iss >> tmpClientName) {
            throw line;
        }

        if (!events.empty() && events[events.size() - 1].time > currentEvent.time) {
            throw line;
        }

        events.push_back(currentEvent);
        switch (currentEvent.id) {
        case 1: {
            if (clientsState.find(currentEvent.clientName) != clientsState.end()) {
                events.push_back(Event(currentEvent.time, "YouShallNotPass"));
            } else if (timeStringToInt(currentEvent.time) < startTime || 
                       timeStringToInt(currentEvent.time) > endTime) {
                events.push_back(Event(currentEvent.time, "NotOpenYet"));
            } else {
                clientsState[currentEvent.clientName] = 0;
            }
            break;
        }
        case 2: {
            if (clientsState.find(currentEvent.clientName) == clientsState.end()) {
                events.push_back(Event(currentEvent.time, "ClientUnknown"));
            } else if (tables[currentEvent.tableNumber - 1].first != "") {
                events.push_back(Event(currentEvent.time, "PlaceIsBusy"));
            } else {
                int freeTableNumber = clientsState[currentEvent.clientName];
                int timeRange = timeStringToInt(currentEvent.time) 
                                    - timeStringToInt(tables[freeTableNumber - 1].second);
                    timeRange = (timeRange + 1440) % 1440;
                    tablesRevenue[freeTableNumber - 1].first += cost * (timeRange / 60 + (timeRange % 60 ? 1 : 0));
                    tablesRevenue[freeTableNumber - 1].second += timeRange;
                
                if (freeTableNumber > 0)
                    tables[freeTableNumber - 1] = std::make_pair("", "");
                else ++busyTablesNumber;

                tables[currentEvent.tableNumber - 1] = std::make_pair(
                    currentEvent.clientName,
                    currentEvent.time
                );
                clientsState[currentEvent.clientName] = currentEvent.tableNumber;
            }
            break;
        }
        case 3: {
            if (clientsState.find(currentEvent.clientName) == clientsState.end()) {
                events.push_back(Event(currentEvent.time, "ClientUnknown"));
            } else if (busyTablesNumber < tablesNumber) {
                events.push_back(Event(currentEvent.time, "ICanWaitNoLonger!"));
            } else if (waitingRoom.size() >= tablesNumber) {
                events.push_back(Event(currentEvent.time, 11, currentEvent.clientName));
            } else {
                waitingRoom.push(currentEvent.clientName);
            }
            break;
        }
        case 4: {
            if (clientsState.find(currentEvent.clientName) == clientsState.end()) {
                events.push_back(Event(currentEvent.time, "ClientUnknown"));
            } else {
                if (clientsState[currentEvent.clientName] > 0) {
                    int freeTableNumber = clientsState[currentEvent.clientName];

                    int timeRange = timeStringToInt(currentEvent.time) 
                                    - timeStringToInt(tables[freeTableNumber - 1].second);
                    timeRange = (timeRange + 1440) % 1440;
                    tablesRevenue[freeTableNumber - 1].first += cost * (timeRange / 60 + (timeRange % 60 ? 1 : 0));
                    tablesRevenue[freeTableNumber - 1].second += timeRange;

                    if (!waitingRoom.empty()) {
                        std::string newClient = waitingRoom.front();
                        waitingRoom.pop();
                        tables[freeTableNumber - 1] = std::make_pair(newClient, currentEvent.time);
                        clientsState[newClient] = freeTableNumber;
                        events.push_back(Event(currentEvent.time, 12, newClient, freeTableNumber));
                    } else {
                        tables[freeTableNumber - 1] = std::make_pair("", "");
                        --busyTablesNumber;
                    }
                }
                clientsState.erase(currentEvent.clientName);
            }
            break;
        }
        default:break;
        }
    }

    ss << sTime << '\n';
    for (Event &e : events) {
        ss << e << '\n';
    }
    std::vector<std::string> remainingClients;
    for (auto &client : clientsState) {
        remainingClients.push_back(client.first);

        if (client.second <= 0) continue;
        int timeRange = endTime
                        - timeStringToInt(tables[client.second - 1].second);
        timeRange = (timeRange + 1440) % 1440;
        tablesRevenue[client.second - 1].first += cost * (timeRange / 60 + (timeRange % 60 ? 1 : 0));
        tablesRevenue[client.second - 1].second += timeRange;
    }
    if (!remainingClients.empty()) {
        std::sort(remainingClients.begin(), remainingClients.end());
        ss << eTime << ' ' << 11;
        for (std::string &client : remainingClients) ss << ' ' << client;
        ss << '\n';
    }
    ss << eTime << '\n';

    for (int i = 0; i < tablesNumber; ++i) {
        ss << i + 1 << ' ' << tablesRevenue[i].first << ' ' << timeIntToString(tablesRevenue[i].second) << '\n';
    }

    return ss;
}