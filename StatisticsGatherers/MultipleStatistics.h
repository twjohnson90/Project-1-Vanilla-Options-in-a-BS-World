#pragma once

#include "StatisticsGatherer.h"

class MultipleStatistics : public StatisticsGatherer {
public:
	MultipleStatistics(const 
		std::vector<std::unique_ptr<StatisticsGatherer>>&);
	MultipleStatistics(const MultipleStatistics&);
	~MultipleStatistics() override {};

	std::unique_ptr<StatisticsGatherer> clone() const override;

	void GetDataFromPath(double Data) override;
	std::vector<std::vector<double>> ComputeStatisticSoFar() const override;
private:
	std::vector<std::unique_ptr<StatisticsGatherer>> InnerObjectsPtr;
};