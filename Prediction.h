#pragma once
#include "Candlestick.h"
#include <vector>
class Prediction
{
public:
	std::vector<Candlestick> prediction;
	static std::vector<Candlestick> predictAverageMove(std::vector<Candlestick> candlestickBook);

};

