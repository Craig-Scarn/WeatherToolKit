#include "WeatherBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>
#include <iostream>

WeatherBook::WeatherBook(std::string filename) {
    hourlyLogs = CSVReader::readCSV(filename);
}


std::vector<Candlestick> WeatherBook::getCandlestickPerYear() {


    //assosiate 1 string with a list of strings - https://www.youtube.com/watch?v=aEgG4pidcKU
    std::map<std::string, std::vector<double>> tempsPerYear;
    for (const auto& entry : hourlyLogs) {
        std::string year = entry.timestamp.substr(0, 4);
        tempsPerYear[year].push_back(entry.AT_temperature);
    }

    std::vector<Candlestick> candlestickBook;

    std::string year{};
    double open{ };
    for (auto pair : tempsPerYear) {
        double high{ };
        double low{ };
        double avg{ };
        
        year = pair.first;

        for (auto temps : pair.second) {
            avg += temps;
            if (temps > high) {
                high = temps;
            }
            if (temps < low) {
                low = temps;
            }
        }
        avg = avg / pair.second.size();
        candlestickBook.push_back(Candlestick(year + "-01-01", open, high, low, avg));
        open = avg;
    }

    //for (Candlestick candle : candlestickBook) {
    //    std::cout << candle.year << " " << candle.open << " " << candle.high << " " << candle.low << " " << candle.close <<  std::endl;
    //}

    return candlestickBook;
}
//filter years
std::vector<Candlestick> WeatherBook::getCandlestickPerYear(std::string startYear, std::string endYear) {

    //associate 1 string with a list of strings - https://www.youtube.com/watch?v=aEgG4pidcKU
    std::map<std::string, std::vector<double>> tempsPerYear;
    for (const auto& entry : hourlyLogs) {
        std::string year = entry.timestamp.substr(0, 4);
        tempsPerYear[year].push_back(entry.AT_temperature);
    }

    std::vector<Candlestick> candlestickBook;

    std::string year{};
    double open{ };
    for (auto pair : tempsPerYear) {
        double high{ };
        double low{ };
        double avg{ };
        // skip loading these dates
        if (std::stoi(startYear) > std::stoi(pair.first) || std::stoi(endYear) < std::stoi(pair.first)) {
            continue;
        }

        year = pair.first;

        for (auto temps : pair.second) {
            avg += temps;
            if (temps > high) {
                high = temps;
            }
            if (temps < low) {
                low = temps;
            }
        }
        //std::cout << year << " " << high << " " << low << std::endl;
        avg = avg / pair.second.size();
        candlestickBook.push_back(Candlestick(year + "-01-01", open, high, low, avg));
        open = avg;
    }

    for (Candlestick candle : candlestickBook) {
        std::cout << candle.year << " " << candle.open << " " << candle.high << " " << candle.low << " " << candle.close <<  std::endl;
    }

    return candlestickBook;
}
// Filter by coutry
// All my code - not he use of map and overloaded functions
std::vector<Candlestick> WeatherBook::getCandlestickPerYear(std::string coutry) {
    //assosiate 1 string with a list of strings - https://www.youtube.com/watch?v=aEgG4pidcKU
    std::map<std::string, std::vector<double>> tempsPerYear;

    std::string coutryOption;
    if (coutry == "1") {
        for (const auto& entry : hourlyLogs) {
            std::string year = entry.timestamp.substr(0, 4);
            tempsPerYear[year].push_back(entry.AT_temperature);
        }
    }
    else if (coutry == "2") {
        for (const auto& entry : hourlyLogs) {
            std::string year = entry.timestamp.substr(0, 4);
            tempsPerYear[year].push_back(entry.BE_temperature);
        }
    }
    else if (coutry == "3") {
        for (const auto& entry : hourlyLogs) {
            std::string year = entry.timestamp.substr(0, 4);
            tempsPerYear[year].push_back(entry.BG_temperature);
        }
    }
    //default to AT_temperature
    else {
        for (const auto& entry : hourlyLogs) {
            std::string year = entry.timestamp.substr(0, 4);
            tempsPerYear[year].push_back(entry.AT_temperature);
        }
    }

    std::vector<Candlestick> candlestickBook;

    std::string year{};
    double open{ };
    for (auto pair : tempsPerYear) {
        double high{ };
        double low{ };
        double avg{ };

        year = pair.first;

        for (auto temps : pair.second) {
            avg += temps;
            if (temps > high) {
                high = temps;
            }
            if (temps < low) {
                low = temps;
            }
        }
        //std::cout << year << " " << high << " " << low << std::endl;
        avg = avg / pair.second.size();
        candlestickBook.push_back(Candlestick(year + "-01-01", open, high, low, avg));
        open = avg;
    }
    return candlestickBook;
}


// My code - take special not oh the map I used for uniuqe years
void WeatherBook::plotCandlestick() {
    std::map<std::string, std::vector<double>> tempsPerYear;
    for (const auto& entry : hourlyLogs) {
        std::string year = entry.timestamp.substr(0, 4);
        tempsPerYear[year].push_back(entry.AT_temperature);
    }

    std::vector<Candlestick> candlestickBook;

    std::string year{};
    
    double open{ };
    for (auto pair : tempsPerYear) {
        double high{ };
        double low{ };
        double avg{ };

        year = pair.first;

        for (auto temps : pair.second) {
            avg += temps;
            if (temps > high) {
                high = temps;
            }
            if (temps < low) {
                low = temps;
            }
        }

        avg = avg / pair.second.size();
        candlestickBook.push_back(Candlestick(year + "-01-01", open, high, low, avg));
        open = avg;
    }
}

