#pragma once

#include "StatisticsGatherer.h"

class ConvergenceTable : public StatisticsGatherer {
public:
	ConvergenceTable(const StatisticsGatherer& InnerObjec_)
		:InnerObject(InnerObjec_.clone()), PathsDone(0), PowerOfTwo(2) {};
	ConvergenceTable(const ConvergenceTable& Original) // need for clone method
		: InnerObject(Original.InnerObject->clone()),
		PathsDone(Original.PathsDone), PowerOfTwo(Original.PowerOfTwo),
		ResultsSoFar(Original.ResultsSoFar) {};
	~ConvergenceTable() override {};

	std::unique_ptr<StatisticsGatherer> clone() const override {
		return std::make_unique<ConvergenceTable>(*this);
	}

	void GetDataFromPath(double Data) override;
	std::vector<std::vector<double>> ComputeStatisticSoFar() const override;
private:
	std::unique_ptr<StatisticsGatherer> InnerObject;
	unsigned long long PathsDone;
	unsigned long long PowerOfTwo;
	std::vector <std::vector<double>> ResultsSoFar;
};
