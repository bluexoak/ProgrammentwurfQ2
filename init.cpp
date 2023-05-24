//Niklas Noll
#include "init.h"
#include <algorithm>

std::vector<Flugzeug> init(const std::string& csvDatei) 
{
   std::vector<Flugzeug> flugzeuge;

   std::ifstream datei(csvDatei);
   if (!datei) 
   {
      std::cerr << "Fehler beim Öffnen der CSV-Datei." << std::endl;
      return flugzeuge;
   }

   // Zeile mit Spaltennamen überspringen
   std::string zeile;
   std::getline(datei, zeile);

   std::string callsign;
   int zeit;
   double lat;
   double lon;
   bool amBoden;

   while (std::getline(datei, zeile)) 
   {
      std::stringstream ss(zeile);
      std::getline(ss, callsign, ',');
      ss >> zeit;
      ss.ignore(); // Komma überspringen
      ss >> lat;
      ss.ignore();
      ss >> lon;
      ss.ignore();
      std::string amBodenStr;
      ss >> amBodenStr;
      amBoden = (amBodenStr == "True" || amBodenStr == "true");

      Zeitpunkt zeitpunkt{zeit, lat, lon, amBoden};

      // Flugzeug finden oder neu erstellen
      auto it = std::find_if(flugzeuge.begin(), flugzeuge.end(),
                              [&callsign](const Flugzeug& flugzeug) 
                              {
                                 return flugzeug.getCallsign() == callsign;
                              });
      if (it != flugzeuge.end()) 
      {
         it->addZeitpunkt(zeit, zeitpunkt);
      } 
      else 
      {
         Flugzeug flugzeug(callsign);
         flugzeug.addZeitpunkt(zeit, zeitpunkt);
         flugzeuge.push_back(flugzeug);
      }
   }

   return flugzeuge;
}

std::vector<std::string> splitString(const std::string& str, char delimiter) 
{
   std::vector<std::string> tokens;
   std::stringstream ss(str);
   std::string token;
   while (std::getline(ss, token, delimiter)) 
   {
      tokens.push_back(token);
   }
   return tokens;
}

std::string toLowerCase(const std::string& str) 
{
   std::string lowerStr = str;
   std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
   return lowerStr;
}