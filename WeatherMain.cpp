#include "WeatherMain.h"
#include "CSVReader.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include "Prediction.h"

WeatherMain::WeatherMain() {

}

// Got from MerkelMain - initialise the application
void WeatherMain::init() {
	int input;

	// Constructor loads a CandlestickBook
	candlestickBook = weatherBook.getCandlestickPerYear();
	filter();
	while (true) {
		printMenu();
		input = getUserInput();
		processUserOption(input);		
	}
	

}

// Got from MerkelMain
void WeatherMain::printMenu() {
	std::cout << "==============================================================" << std::endl;
	// Print menu
	std::cout << "1: Print help " << std::endl;
	// print stats
	std::cout << "2: Print candlestick data" << std::endl;
	// plot graph
	std::cout << "3: Plot candlestick text graph" << std::endl;
	// filter data per year
	std::cout << "4: Filter data per year" << std::endl;
	// filter by coutry
	std::cout << "5: Change country" << std::endl;
	// prediction
	std::cout << "6: Predict data for next year for currenct dataset" << std::endl;
	std::cout << "==============================================================" << std::endl;
}

// Got from MerkelMain
int WeatherMain::getUserInput() {
	int userOption = 0;
	std::string line;
	//std::cout << "Type in 1-3" << std::endl;
	std::getline(std::cin, line);
	try {
		userOption = std::stoi(line);
	}
	catch (const std::exception& e) {
		std::cout << "WeatherMain::getUserInput() Incorrect input" << std::endl;
	}
	std::cout << "You chose: " << userOption << std::endl;
	return userOption;
}

// Got from MerkelMain
void WeatherMain::printHelp()
{
	std::cout << "Help - tool kit for processing weather data " << std::endl;
}

// Got from MerkelMain
void WeatherMain::processUserOption(int userOption)
{
	if (userOption == 0) // bad input
	{
		std::cout << "Invalid choice. Choose 1-6" << std::endl;
	}
	if (userOption == 1)
	{
		printHelp();
	}
	if (userOption == 2)
	{
		printCandlestickData();
	}
	if (userOption == 3) {
		plotGraph();
	}
	if (userOption == 4)
	{
		// add some error handling for inputs here
		std::string yearSelectionStart{ candlestickBook[0].year.substr(0,4) };
		std::string yearSelectionEnd{ candlestickBook[candlestickBook.size() -1].year.substr(0,4)};

		std::cout << "Enter start year between " << yearSelectionStart << " and " << yearSelectionEnd << std::endl;
		std::string startYear;
		std::string endYear;
		std::getline(std::cin, startYear);
		std::cout << "Enter end year between " << yearSelectionStart << " and " << yearSelectionEnd << std::endl;
		std::getline(std::cin, endYear);
		try {
			int temp = std::stoi(startYear);
			int temp2 = std::stoi(endYear);
			candlestickBook = weatherBook.getCandlestickPerYear(startYear, endYear);
			
		}
		catch (const std::exception& e) {
			std::cout << "Bad input in userOption 4, select a year between " << yearSelectionStart << " and " << yearSelectionEnd << std::endl;
		}
			
	}
	if (userOption == 5) {
		filter();
	}
	if (userOption == 6) {
		candlestickBook = Prediction::predictAverageMove(candlestickBook);
		printCandlestickData();
		plotGraph();
	}
}

// Print data in CandleStickBook (by default the fill data set will laod) 
// All my code but got insparation from a udamy cours on how to alighn data
void WeatherMain::printCandlestickData() {

	// Allign and fill https://kasperskylab.udemy.com/course/beginning-c-plus-plus-programming/learn/lecture/10154724#overview
	const int fieldWidth1{ 12 };
	const int fieldWidth2{ 10 };
	std::cout << std::setw(fieldWidth1) << std::left 
		<< "Date" << std::setw(fieldWidth2) << std::left <<
		"Open" << std::setw(fieldWidth2) << std::left << 
		"High" << std::setw(fieldWidth2) << std::left << 
		"Low" << std::setw(fieldWidth2) << std::left << 
	    "Close" << std::setw(fieldWidth2) << std::left << std::endl;

	for (Candlestick candle : candlestickBook) {
		std::cout << std::setw(fieldWidth1) << std::left << candle.year << 
			std::setw(fieldWidth2) << std::left << candle.open << 
			std::setw(fieldWidth2) << std::left << candle.high << 
			std::setw(fieldWidth2) << std::left << candle.low << 
			std::setw(fieldWidth2) << std::left << candle.close << std::endl;
	}
}

// All my code
void WeatherMain::plotGraph() {

	double plotHeigh{};
	double plotLow{};
	for (const auto entry : candlestickBook) {
		if (entry.high > plotHeigh) {
			plotHeigh = entry.high;
		}
		if (entry.low < plotLow) {
			plotLow = entry.low;
		}
	}
	//std::cout << plotHeigh << " " << static_cast<int>(plotHeigh) << " " << plotLow << std::endl;
	int buffer{ 2 };
	plotHeigh = static_cast<int>(plotHeigh) + buffer;
	plotLow = static_cast<int>(plotLow) - buffer ;
	std::string candlePlotText = "[|]";
	std::string stickPlotText = " | ";
	drawBoarder();

	std::cout << std::endl;
	std::cout << "Candle from low to high is represented by: " << candlePlotText << std::endl;
	std::cout << "Sick from low to high is represented by: " << stickPlotText << std::endl;
	drawBoarder();
	std::cout << std::endl;
	for (int j = plotHeigh; j >= plotLow; j-=1) {
		std::cout << std::setw(8) << std::left << j;
		for (int i = 0; i < candlestickBook.size(); ++i) {
			if (j >= 0) {
				if (candlestickBook[i].high >= j) {
					if ((std::round(candlestickBook[i].open) <= j && std::round(candlestickBook[i].close) >= j) || (std::round(candlestickBook[i].open) >= j && std::round(candlestickBook[i].close) <= j)) {
						std::cout << std::setw(5) << std::left << candlePlotText;
					}
					else {
						std::cout << std::setw(5) << std::left << stickPlotText;
					}
					
				}
				else {
					std::cout << std::setw(5) << std::left << "";
				}
			}
			else {
				if (candlestickBook[i].low <= j) {
					if ((std::round(candlestickBook[i].open) >= j && std::round(candlestickBook[i].close) <= j) || (std::round(candlestickBook[i].open) <= j && std::round(candlestickBook[i].close) >= j)) {
						std::cout << std::setw(5) << std::left << candlePlotText;
					}
					else {
						std::cout << std::setw(5) << std::left << stickPlotText;
					}
					
				}
				else {
					std::cout << std::setw(5) << std::left << "";
				}
			}
		}
		std::cout << std::endl;
	}
	drawBoarder();
	std::cout << std::endl; 
	std::cout << std::setw(8) << std::left << "Temps";
	for (int i = 0; i < candlestickBook.size(); ++i) {
			std::cout << std::setw(5) << std::left << candlestickBook[i].year.substr(0, 4);
	}
	std::cout << std::endl;
	drawBoarder();
	std::cout << std::endl;
	
}

// All my code
void WeatherMain::drawBoarder() {
	for (int i = 0; i < candlestickBook.size() + 1; ++i) {
		std::cout << "-----";
	}
}

// All my code
void WeatherMain::filter() {
	// add some error handling for inputs here
	std::cout << "More coutries can be added on request..." << std::endl;
	std::cout << "Select coutry:" << std::endl;
	std::cout << "1: Austria" << std::endl;
	std::cout << "2: Belgium" << std::endl;
	std::cout << "3: Bulgaria" << std::endl;
	std::string coutryOption;
	std::getline(std::cin, coutryOption);
	if (coutryOption == "1" || coutryOption == "2" || coutryOption == "3") {
		candlestickBook = weatherBook.getCandlestickPerYear(coutryOption);
	}
	else {
		std::cout << "Incorrect input numeric number." << std::endl;
	}
}