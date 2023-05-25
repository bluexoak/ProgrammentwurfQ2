#include <iostream>
#include <map>
#include <algorithm>
#include "init.h"
#include "Flugzeug.h"
#include "Zeitpunkt.h"
#include "distance.h"

void flugzeugVerfolgung();
void entfernungsMessung();
void kollisionsWarner();

std::map<std::string, Flugzeug> flugzeugMap;

int main() 
{
   std::cout << "Daten werden eingelesen, bitte warten:" << std::endl;
    std::string filename = "flightdata.csv";
    if (!readCSV(filename, flugzeugMap)) 
    {
        return 1;
    }
   std::cout << "Einlesen fertig!" << std::endl;
    while(1)
    {
        int auswahl = 0;
        std::cout << "Waehlen Sie eine der folgenden Optionen: " << std::endl
            << "    1 - Flugzeugverfolgung" << std::endl
            << "    2 - Entfernungsmessung" << std::endl
            << "    3 - Kollisionswarnung" << std::endl
            << "    4 - Programm schliessen" << std::endl
            << "Ihre Eingabe: ";
        std::cin >> auswahl;
        switch (auswahl)
        {
            case 1:
                flugzeugVerfolgung();
                break;
            case 2:
                entfernungsMessung();
                break;
            case 3:
                kollisionsWarner();
                break;
            case 4:
                return 0;
            default:
                std::cout << "Keine gueltige Eingabe" << std::endl;
                break;
        }
    }

   // Beispielverwendung: Daten für ein bestimmtes Flugzeug ausgeben
   std::string gesuchtesCallsign = "JIA5151";
   bool flugzeugGefunden = false;
   for (const auto& pair : flugzeugMap) 
   {
      const std::string& callsign = pair.first;
      if (callsign.find(gesuchtesCallsign) != std::string::npos) 
      {
         const Flugzeug& gefundenesFlugzeug = pair.second;
         gefundenesFlugzeug.printDaten();
         flugzeugGefunden = true;
      }
   }

   if (!flugzeugGefunden) 
   {
      std::cout << "Flugzeug mit Callsign " << gesuchtesCallsign << " wurde nicht gefunden." << std::endl;
   }

   return 0;
}

void flugzeugVerfolgung()
{
   std::string gesuchtesCallsign;
   std::cout << "Bitte geben sie ein Callsign ein: ";
   std::cin >> gesuchtesCallsign;
   bool flugzeugGefunden = false;
   for (const auto& pair : flugzeugMap) 
   {
      const std::string& callsign = pair.first;
      if (callsign.find(gesuchtesCallsign) != std::string::npos) 
      {
         const Flugzeug& gefundenesFlugzeug = pair.second;
         gefundenesFlugzeug.printDaten();
         flugzeugGefunden = true;
      }
   }

   if (!flugzeugGefunden) 
   {
      std::cout << "Flugzeug mit Callsign " << gesuchtesCallsign << " wurde nicht gefunden." << std::endl;
   }

}

void entfernungsMessung()
{
    std::map<int, Zeitpunkt> daten1, daten2;
    std::string cs1, cs2;
    std::cout << "Bitte geben Sie das Callsign des ersten Flugzeuges ein: ";
    std::cin >> cs1;
    bool flugzeug1Gefunden = false;
    for (const auto& pair : flugzeugMap) 
    {
        const std::string& callsign = pair.first;
        if (callsign.find(cs1) != std::string::npos) 
        {
            const Flugzeug& gefundenesFlugzeug1 = pair.second;
            flugzeug1Gefunden = true;
            daten1 = gefundenesFlugzeug1.returnDaten();
        }
    }
    if (!flugzeug1Gefunden) 
    {
        std::cout << "Flugzeug mit Callsign " << cs1 << " wurde nicht gefunden. Erbitte erneute Eingabe." << std::endl;
        entfernungsMessung();
    }
    std::cout << "Bitte geben Sie das Callsign des zweiten Flugzeuges ein: ";
    std::cin >> cs2;
    bool flugzeug2Gefunden = false;
    for (const auto& pair : flugzeugMap) 
    {
        const std::string& callsign = pair.first;
        if (callsign.find(cs2) != std::string::npos) 
        {
            const Flugzeug& gefundenesFlugzeug2 = pair.second;
            flugzeug2Gefunden = true;
            daten2 = gefundenesFlugzeug2.returnDaten();
        }
    }
    if (!flugzeug2Gefunden) 
    {
        std::cout << "Flugzeug mit Callsign " << cs2 << " wurde nicht gefunden. Erbitte erneute Eingabe." << std::endl;
        entfernungsMessung();
    }
    auto itm1 = daten1.begin();
    auto itm2 = daten2.begin();
    while(itm1 != daten1.end())
    {
        while(itm2 != daten2.end())
        {
            if(itm1->first == itm2->first)
            {
                while(itm1 != daten1.end() && itm2 != daten2.end())
                {
                    std::cout << "Zum Zeitpunkt " << itm1->first << " beträgt die Entfernung: " << distance(itm1->second.lat, itm1->second.lon, itm2->second.lat, itm2->second.lon) << std::endl;
                    ++itm1;
                    ++itm2;
                }
            }
            else
            {
                ++itm2; // Aktualisiere den Iterator itm2, auch wenn die Schlüssel nicht übereinstimmen
            }
        }
         
    }
}

std::vector<std::string> findNearestFlugzeuge(const std::string& targetCallsign, const std::map<std::string, Flugzeug>& flugzeugMap) {
    std::vector<std::string> nearestFlugzeuge;
    std::vector<std::pair<std::string, double>> distanceVector;

    // Überprüfe, ob das Ziel-Flugzeug in der Map existiert
    auto targetFlugzeugIter = flugzeugMap.find(targetCallsign);
    if (targetFlugzeugIter == flugzeugMap.end()) {
        std::cout << "Flugzeug nicht gefunden: " << targetCallsign << std::endl;
        return nearestFlugzeuge;
    }

    const Flugzeug& targetFlugzeug = targetFlugzeugIter->second;
    const std::map<int, Zeitpunkt>& targetZeitpunkte = targetFlugzeug.returnDaten();

    // Durchlaufe die Flugzeuge in der Map
    for (const auto& pair : flugzeugMap) {
        const std::string& callsign = pair.first;
        const Flugzeug& flugzeug = pair.second;

        // Überspringe das Ziel-Flugzeug selbst
        if (callsign == targetCallsign) {
            continue;
        }

        double minDistance = std::numeric_limits<double>::max();

        // Durchlaufe die Zeitpunkte des aktuellen Flugzeugs
        for (const auto& targetPair : targetZeitpunkte) {
            int targetZeit = targetPair.first;
            const Zeitpunkt& targetZeitpunkt = targetPair.second;

            // Überprüfe, ob das aktuelle Flugzeug den Zeitpunkt enthält
            auto zeitpunktIter = flugzeug.returnDaten().find(targetZeit);
            if (zeitpunktIter != flugzeug.returnDaten().end()) {
                const Zeitpunkt& zeitpunkt = zeitpunktIter->second;
                double currentDistance = distance(targetZeitpunkt.lat, targetZeitpunkt.lon, zeitpunkt.lat, zeitpunkt.lon);

                // Aktualisiere den minimalen Abstand, falls erforderlich
                if (currentDistance < minDistance) {
                    minDistance = currentDistance;
                }
            }
        }

        distanceVector.push_back(std::make_pair(callsign, minDistance));
    }

    // Sortiere den Abstand nach aufsteigender Reihenfolge
    std::sort(distanceVector.begin(), distanceVector.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.second < rhs.second;
    });

    // Extrahiere die Flugzeug-Callsigns der 5 nächstgelegenen Flugzeuge
    for (size_t i = 0; i < std::min(distanceVector.size(), static_cast<size_t>(5)); ++i) {
        nearestFlugzeuge.push_back(distanceVector[i].first);
    }

    return nearestFlugzeuge;
}

void kollisionsWarner()
{
    std::string cs;
    cout << "Geben Sie das callsign ein, für das Sie den Kollisions-Warner ausführen wollen: ";
    cin >> cs;
    cout << "Die fünf " << cs << " am nächsten Flugzeuge sind: ";
    auto itv = findNearestFlugzeuge(cs, flugzeugMap).begin();
    while(itv != findNearestFlugzeuge(cs, flugzeugMap).end())
    {
        cout << *itv;
        ++itv;
    }
}