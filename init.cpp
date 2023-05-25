//Niklas Noll
#include "init.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "Flugzeug.h"

std::vector<std::string> splitString(const std::string& line, char delimiter) 
{
   std::vector<std::string> tokens;
   std::istringstream iss(line);
   std::string token;
   while (std::getline(iss, token, delimiter)) 
   {
      tokens.push_back(token);
   }
   return tokens;
}

std::string toLowercase(const std::string& str) 
{
   std::string result = str;
   std::transform(result.begin(), result.end(), result.begin(), ::tolower);
   return result;
}

bool readCSV(const std::string& filename, std::map<std::string, Flugzeug>& flugzeugMap) 
{
   std::ifstream file(filename);
   if (!file) {
      std::cerr << "Fehler beim Öffnen der Datei." << std::endl;
      return false;
   }

   std::string header;
   std::getline(file, header); // Zeile mit Spaltennamen überspringen
   std::vector<std::string> spalten = splitString(header, ',');

   int timeIndex = -1;
   int latIndex = -1;
   int lonIndex = -1;
   int callsignIndex = -1;
   int onGroundIndex = -1;

   // Suche nach den Indizes der relevanten Spalten
   for (int i = 0; i < spalten.size(); i++) {
      if (spalten[i] == "time") {
         timeIndex = i;
      } else if (spalten[i] == "lat") {
         latIndex = i;
      } else if (spalten[i] == "lon") {
         lonIndex = i;
      } else if (spalten[i] == "callsign") {
         callsignIndex = i;
      } else if (spalten[i] == "onground") {
         onGroundIndex = i;
      }
   }

   if (timeIndex == -1 || latIndex == -1 || lonIndex == -1 || callsignIndex == -1 || onGroundIndex == -1) {
      std::cerr << "Nicht alle relevanten Spalten gefunden." << std::endl;
      return false;
   }

   std::string line;
   int zeilennummer = 2; // Zeilennummer für Fehlermeldung (beginnt bei 2, da Header bereits gelesen wurde)
   int auswahl = 1;
   int gross = 0;
   while (std::getline(file, line)) {
      std::vector<std::string> fields = splitString(line, ',');

      /*
      // Überprüfung, ob alle Spalten vorhanden sind
      if (fields.size() < spalten.size()) {
         std::cerr << "Nicht alle Spaltenwerte gefunden in Zeile " << zeilennummer << ": " << line << std::endl;
         continue;
      }
      */
      
      /*
      switch(auswahl)
      {
         case 1:
            std::cout << "Einlesen startet, bitte warten.";
            break;
         case 2:
            std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
                     << "Einlesen startet, bitte warten..";
            break;
         case 3:
            std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
                        << "Einlesen startet, bitte warten...";
               break;
         case 4:
            std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
            auswahl = 1;
            break;
      }
      */


      std::string callsign = fields[callsignIndex];

      // Überprüfung, ob das Flugzeug bereits in der Map existiert, andernfalls erstellen
      if (flugzeugMap.find(callsign) == flugzeugMap.end()) {
         flugzeugMap[callsign] = Flugzeug();
      }

      int zeit;
      try {
         zeit = std::stoi(fields[timeIndex]);
      } catch (const std::invalid_argument& e) {
         continue;
      }

      double lat, lon;
      try {
         lat = std::stod(fields[latIndex]);
         lon = std::stod(fields[lonIndex]);
      } catch (const std::invalid_argument& e) {
         continue;
      }

      bool amBoden = (toLowercase(fields[onGroundIndex]) == "true");

      Zeitpunkt zeitpunkt{zeit, lat, lon, amBoden};

      Flugzeug& flugzeug = flugzeugMap[callsign];
      flugzeug.addZeitpunkt(zeit, zeitpunkt);

      zeilennummer++;
      gross++;
      if(gross == 100000)
      {
         auswahl++;
         gross = 0;
      }

   }

   return true;
}
