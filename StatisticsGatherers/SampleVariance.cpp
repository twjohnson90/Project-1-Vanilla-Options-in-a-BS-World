
#include "SampleVariance.h"

std::unique_ptr<StatisticsGatherer> SampleVariance::clone() const {
	return std::make_unique<SampleVariance>(*this);
}

void SampleVariance::GetDataFromPath(double Data) {
	RunningSum += Data;
	RunningSumSquares += Data * Data;
	++PathsDone;
}
std::vector<std::vector<double>> SampleVariance::ComputeStatisticSoFar() const {

	std::vector<std::vector<double>> Results(1);
	Results[0].resize(1);
	Results[0][0] = (RunningSumSquares-(RunningSum*RunningSum)/PathsDone)/(PathsDone-1);
	return Results;
}