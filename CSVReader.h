#pragma once
#include "WeatherBook.h"
#include "WeatherEntry.h"
#include <vector>
#include <string>


class CSVReader
{
public:
	CSVReader();
	static std::vector<WeatherEntry> readCSV(std::string csvFilename);
	static std::vector<std::string> tokenise(std::string csvLine, char separator);
	static WeatherEntry stringsToOBE(std::vector<std::string> tokens);
	
	//test constructor for hourlyLogs
	std::vector<WeatherEntry> hourlyLogs;
};

