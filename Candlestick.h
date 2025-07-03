#pragma once
#include <string>

// Constructor as of requirments
class Candlestick
{
public:
	Candlestick(std::string _year, double _open, double _high, double _low, double _close);

	std::string year;
	double open;
	double high;
	double low;
	double close;
};

