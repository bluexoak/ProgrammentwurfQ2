#ifndef FLUGZEUG_H
#define FLUGZEUG_H

#include <map>
#include <string>
#include <vector>
#include "Zeitpunkt.h"

class Flugzeug 
{
    private:
        std::string callsign;
        std::map<int, Zeitpunkt> daten;
    public:
        Flugzeug() = default;
        Flugzeug(const std::string& callsign);
        void addZeitpunkt(int zeit, const Zeitpunkt& zeitpunkt);
        void printDaten() const;
        std::map<int, Zeitpunkt> returnDaten() const;
        std::string getCallsign() const;
        std::map<int, std::vector<Flugzeug>> getNearestFlugzeuge(const std::string& callsign) const;

};

#endif // FLUGZEUG_H