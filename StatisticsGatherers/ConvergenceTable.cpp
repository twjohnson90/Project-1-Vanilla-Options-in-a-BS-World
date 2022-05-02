
#include "ConvergenceTable.h"

void ConvergenceTable::GetDataFromPath(double Data) {

	InnerObject->GetDataFromPath(Data);
	++PathsDone;

	if (PathsDone == PowerOfTwo) {

		std::vector<std::vector<double>> CurrentResults
		(InnerObject->ComputeStatisticSoFar());

		for (int i = 0;i<CurrentResults.size();++i) {
			ResultsSoFar.push_back(CurrentResults[i]);
		}
		PowerOfTwo *= 2;
	}
};
std::vector <std::vector<double>> ConvergenceTable::ComputeStatisticSoFar() const
{

	// need to compute statistic for final path if isn't power of 2
	if (PathsDone * 2 != PowerOfTwo) {
		// cannot add to ResultsSoFar as want method to be const
		std::vector<std::vector<double>> tmp(ResultsSoFar);
		std::vector<std::vector<double>> CurrentResults
		(InnerObject->ComputeStatisticSoFar());

		for (int i = 0; i < CurrentResults.size(); ++i) {
			tmp.push_back(CurrentResults[i]);
		}
		
		return tmp;
	}

	return ResultsSoFar; // wasteful to create new vector if don't need it
};