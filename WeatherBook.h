#pragma once
#include <vector>
#include <string>
#include "WeatherEntry.h"
#include "Candlestick.h"

class WeatherBook
{
public:
	WeatherBook(std::string filename);
	std::vector<Candlestick> getCandlestickPerYear();
	std::vector<Candlestick> getCandlestickPerYear(std::string startYear, std::string endYear);
	std::vector<Candlestick> getCandlestickPerYear(std::string coutry);
	void plotCandlestick();
	//std::vector<Candlestick> predictAverageMove(std::vector<Candlestick>);
	
private:
	std::vector<WeatherEntry> hourlyLogs;
	
};

