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