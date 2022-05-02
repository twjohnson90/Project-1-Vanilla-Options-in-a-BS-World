#include "MultipleStatistics.h"

using namespace std;

MultipleStatistics::MultipleStatistics(const 
	vector<unique_ptr<StatisticsGatherer>>& InnerObjects)
{
	InnerObjectsPtr.resize(InnerObjects.size());
	for (int i = 0; i < InnerObjects.size(); ++i) {
		InnerObjectsPtr[i] = InnerObjects[i]->clone();
	}
}

MultipleStatistics::MultipleStatistics(const
	MultipleStatistics& Original)
{
	InnerObjectsPtr.resize(Original.InnerObjectsPtr.size());
	for (int i = 0; i < Original.InnerObjectsPtr.size(); ++i) {
		InnerObjectsPtr[i] = Original.InnerObjectsPtr[i]->clone();
	}
}

std::unique_ptr<StatisticsGatherer> MultipleStatistics::clone() const {
	return std::make_unique<MultipleStatistics>(*this);
}

void MultipleStatistics::GetDataFromPath(double Data) {
	for (auto& i : InnerObjectsPtr)
		i->GetDataFromPath(Data);
}

std::vector<std::vector<double>>
MultipleStatistics::ComputeStatisticSoFar() const {

	vector < vector<double> > Results(InnerObjectsPtr[0]->
		ComputeStatisticSoFar());

	for (int i = 0; i < Results.size(); ++i) {
		for (int k = 1; k < InnerObjectsPtr.size(); ++k) {
			vector<double> tmp = InnerObjectsPtr[k]->ComputeStatisticSoFar()[i];
			for (const auto& v : tmp ) {
				Results[i].push_back(v);
			}
		}
	}

	/*auto M = InnerObjectsPtr.size();
	std::vector<int> SizeOfInnerResults(M+1);
	for (int i = 1; i < M + 1; ++i) {
		SizeOfInnerResults[i] = InnerObjectsPtr[i - 1]->
			ComputeStatisticSoFar().size();
	}

	auto N = 0;
	for (const auto& i : SizeOfInnerResults)
		N += i;*/

	/*std::vector<std::vector<double>> ResultsSoFar;
	for (int i = 0; i < InnerObjectsPtr.size(); ++i) {
		for (const auto& v : InnerObjectsPtr[i]->ComputeStatisticSoFar()) {
			ResultsSoFar.push_back(v);
		}
	}*/

	/*auto k = 0;
	for (int i = 0; i < M; ++i) {
		k += SizeOfInnerResults[i];
		for (int j = k; j <= k + SizeOfInnerResults[i + 1] - 1; ++j) {



			ResultsSoFar[j] = InnerObjectsPtr[i]->ComputeStatisticSoFar()[j];
		}
	}*/

	return Results;
}