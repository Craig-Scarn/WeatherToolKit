#include "CSVReader.h"
#include <iostream>
#include <fstream>

CSVReader::CSVReader() {

}
// Code coppied from MerkelMain and adapted to my needs
std::vector<WeatherEntry> CSVReader::readCSV(std::string csvFilename) {
	std::vector<WeatherEntry> entries;
	std::ifstream csvFile{ csvFilename };
	std::string line;

	if (csvFile.is_open()) {
		while (std::getline(csvFile, line)) {
			//std::cout << line << std::endl;
			try {
				WeatherEntry obe = stringsToOBE(tokenise(line, ','));
				
				entries.push_back(obe);
			}
			catch (const std::exception& e)
			{
				std::cout << "CSVReader::readCSV bad data" << std::endl;
			}
		}
	}
	std::cout << "Entry size " << entries.size() << std::endl;
	return entries;
}

// Code copied exactly from MerkelMain it chops the lines read from code and tokenizes it into parts
std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
	std::vector<std::string> tokens;
	signed int start, end;
	std::string token;
	start = csvLine.find_first_not_of(separator, 0);
	do {
		end = csvLine.find_first_of(separator, start);
		if (start == csvLine.length() || start == end) break;
		if (end >= 0) token = csvLine.substr(start, end - start);
		else token = csvLine.substr(start, csvLine.length() - start);
		tokens.push_back(token);
		start = end + 1;
	} while (end > 0);

	return tokens;
}

// code adapted from MerkelMain
// This function creates objects of WeatherEntries 
WeatherEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
	double AT_tempreature;
	double BE_temperature;
	double BG_temperature;

	try {
		AT_tempreature = std::stod(tokens[1]);
		BE_temperature = std::stod(tokens[4]);
		BG_temperature = std::stod(tokens[7]);
	}
	catch (const std::exception& e) {
		std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[0] << tokens[1] << std::endl;
		throw;
	}

	WeatherEntry obe{ tokens[0],
			AT_tempreature,
			BE_temperature,
			BG_temperature
	};

	return obe;
}