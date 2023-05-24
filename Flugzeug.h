#ifndef FLUGZEUG_H
#define FLUGZEUG_H

#include <unordered_map>
#include <string>
#include "Zeitpunkt.h"

class Flugzeug {
public:
   Flugzeug() = default;
    Flugzeug(const std::string& callsign);
    void addZeitpunkt(int zeit, const Zeitpunkt& zeitpunkt);
    void printDaten() const;
    std::string getCallsign() const;

private:
    std::string callsign;
    std::unordered_map<int, Zeitpunkt> daten;
};

#endif // FLUGZEUG_H