#pragma once

#include <vector>
#include <memory>

class StatisticsGatherer {
public:
	virtual ~StatisticsGatherer() {};

	virtual std::unique_ptr<StatisticsGatherer> clone() const = 0;

	virtual void GetDataFromPath(double Data) = 0;
	virtual std::vector<std::vector<double>>
		ComputeStatisticSoFar() const = 0;
};

class Mean : public StatisticsGatherer {
private:
	double RunningSum;
	unsigned long long PathsDone;
public:
	Mean()
		:RunningSum(0.0), PathsDone(0) {};
	~Mean() override {};

	std::unique_ptr<StatisticsGatherer> clone() const override {
		return std::make_unique<Mean>(*this);
	}

	void GetDataFromPath(double Data) override {
		RunningSum += Data;
		++PathsDone;
	}
	std::vector<std::vector<double>> ComputeStatisticSoFar() const override {

		std::vector<std::vector<double>> Results(1);
		Results[0].resize(1);
		Results[0][0] = RunningSum / PathsDone;
		return Results;
	}
};