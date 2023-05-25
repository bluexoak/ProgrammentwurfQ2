#include "Flugzeug.h"
#include <iostream>
#include <iomanip>
#include <vector>

Flugzeug::Flugzeug(const std::string& callsign)
    : callsign(callsign) {}

void Flugzeug::addZeitpunkt(int zeit, const Zeitpunkt& zeitpunkt) {
    daten[zeit] = zeitpunkt;
}

void Flugzeug::printDaten() const 
{
   std::cout << "Die Daten zu dem Flugzeug sind: " << std::endl;
    for (const auto& zeitpunkt : daten) 
    {
        std::cout << "Zeit: " << std::setw(10) << std::left << zeitpunkt.second.zeit
                  << "Lat: " << std::setw(10) << std::left << zeitpunkt.second.lat
                  << "Lon: " << std::setw(10) << std::left << zeitpunkt.second.lon
                  << "Am Boden: " << (zeitpunkt.second.amBoden ? "Ja" : "Nein") << std::endl;
    }
}


std::map<int, Zeitpunkt> Flugzeug::returnDaten() const
{
    return daten;
}

std::string Flugzeug::getCallsign() const
{
    return callsign;
}
