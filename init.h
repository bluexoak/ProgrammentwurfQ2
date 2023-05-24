//Niklas Noll
#ifndef INIT_H
#define INIT_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "Flugzeug.h"
#include "Zeitpunkt.h"

std::vector<Flugzeug> init(const std::string& csvDatei);
std::vector<std::string> splitString(const std::string& str, char delimiter);
std::string toLowerCase(const std::string& str);

#endif // INIT_H
