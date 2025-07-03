#pragma once
#include <string>
#include <vector>
#include "WeatherEntry.h"
#include "CSVReader.h"
#include "WeatherBook.h"


class WeatherMain
{
public:
	WeatherMain();
	void init();
	int getUserInput();

private:
	void printMenu();
	void printHelp();
	void processUserOption(int userOption);
	void printCandlestickData();
	void plotGraph();
	void drawBoarder();
	void filter();
	//void plotGraphfilterYear(std::string startYear,std::string endYear);
	//Creates vector of data with timestamps and weather entries for Austria
	//std::vector<WeatherEntry> hourlyLogs = CSVReader::readCSV("weather_data.csv");
	//constructor with all weather data
	WeatherBook weatherBook{ "weather_data.csv" };
	std::vector<Candlestick> candlestickBook;
};

