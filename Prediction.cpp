#include "Prediction.h"

// All my code
std::vector<Candlestick> Prediction::predictAverageMove(std::vector<Candlestick> candleStickBook) {
	
	double closePrediction{};
	double lowPrediction{};
	double highPrediction{};
	double openPrediction{ candleStickBook[candleStickBook.size() - 1].close };
	int yearPrediction{ std::stoi(candleStickBook[candleStickBook.size() - 1].year) + 1 };
	std::string newYearPrediction = std::to_string(yearPrediction);
	newYearPrediction = newYearPrediction + "-01-01";
	for (Candlestick c : candleStickBook) {
		highPrediction += c.high;
		lowPrediction += c.low;
		closePrediction += c.close;
	}
	highPrediction = highPrediction / candleStickBook.size();
	lowPrediction = highPrediction / candleStickBook.size();
	closePrediction = closePrediction / candleStickBook.size();
	
	candleStickBook.push_back(Candlestick(newYearPrediction, openPrediction, highPrediction, lowPrediction, closePrediction));

	return candleStickBook;
}