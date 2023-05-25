#include "Flugzeug.h"
#include "distance.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

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

std::map<int, std::vector<Flugzeug>> Flugzeug::getNearestFlugzeuge(const std::string& callsign) const {
   std::map<int, std::vector<Flugzeug>> nearestFlugzeuge;
   const Flugzeug& currentFlugzeug = *this;

   for (const auto& pair : daten) {
      int zeit = pair.first;
      const Zeitpunkt& zeitpunkt = pair.second;

      std::vector<std::pair<double, const Flugzeug*>> distances;
      for (const auto& otherPair : currentFlugzeug.daten) {
         if (otherPair.first != zeit) {
            const Zeitpunkt& otherZeitpunkt = otherPair.second;
            long double distance = 0;
            distance = distance::distance(zeitpunkt.lat, zeitpunkt.lon, otherZeitpunkt.lat, otherZeitpunkt.lon);
            distances.push_back(std::make_pair(static_cast<double>(distance), &currentFlugzeug));
         }
      }

      std::sort(distances.begin(), distances.end());

      std::vector<Flugzeug> nearest;
      for (int i = 0; i < std::min(5, static_cast<int>(distances.size())); ++i) {
         nearest.push_back(*distances[i].second);
      }

      nearestFlugzeuge[zeit] = nearest;
   }

   return nearestFlugzeuge;
}

