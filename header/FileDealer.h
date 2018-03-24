#pragma once
/*Utility functions to read and write files*/


#include <fstream>
#include <set>

bool WriteSetToFile(std::string filename, std::set<std::string> extensionSet);
std::set<std::string> ReadSetFromFile(std::string filename);