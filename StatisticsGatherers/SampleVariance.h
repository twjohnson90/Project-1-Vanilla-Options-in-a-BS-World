#pragma once

#include "StatisticsGatherer.h"

class SampleVariance : public StatisticsGatherer {
public:
	SampleVariance() {};
	~SampleVariance() override {};

	std::unique_ptr<StatisticsGatherer> clone() const override;

	void GetDataFromPath(double Data) override;
	std::vector<std::vector<double>> ComputeStatisticSoFar() const override;
private:
	double RunningSum{ 0 };
	double RunningSumSquares{ 0 };
	unsigned long long PathsDone{ 0 };
};
