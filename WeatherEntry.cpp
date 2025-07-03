#include "WeatherEntry.h"
#include <string>

// Note the overloaded constructors
WeatherEntry::WeatherEntry(std::string _timestamp, double _AT_tempreture) : timestamp(_timestamp), AT_temperature(_AT_tempreture) {

}
WeatherEntry::WeatherEntry(std::string _timestamp, double _AT_tempreture, double _BE_temperature) : timestamp(_timestamp), AT_temperature(_AT_tempreture), BE_temperature(_BE_temperature){

}
WeatherEntry::WeatherEntry(std::string _timestamp, double _AT_tempreture, double _BE_temperature, double _BG_temperature) :
	timestamp(_timestamp), AT_temperature(_AT_tempreture), BE_temperature(_BE_temperature), BG_temperature(_BG_temperature){

}