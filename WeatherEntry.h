#pragma once
#include <string>

class WeatherEntry
{
public:
	WeatherEntry(std::string _timestamp, double _AT_tempreture);
	WeatherEntry(std::string _timestamp, double _AT_tempreture, double BE_temperature);
	WeatherEntry(std::string _timestamp, double _AT_tempreture, double _BE_temperature, double _BG_temperature);

	std::string timestamp;
	double AT_temperature;
	double BE_temperature;
	double BG_temperature;
};

