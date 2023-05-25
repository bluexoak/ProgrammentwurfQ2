//Niklas Noll
#ifndef INIT_H
#define INIT_H

#include <vector>
#include <string>
#include <map>
#include "Flugzeug.h"

std::vector<std::string> splitString(const std::string& line, char delimiter);
std::string toLowercase(const std::string& str);
bool readCSV(const std::string& filename, std::map<std::string, Flugzeug>& flugzeugMap);


#endif  // INIT_H