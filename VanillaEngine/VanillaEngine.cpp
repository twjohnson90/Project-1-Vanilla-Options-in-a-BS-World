
#include "VanillaEngine.h"

#include <iostream>

using namespace std;

void VanillaEngine::RunSimulation(const VanillaOption& TheProduct,
	StatisticsGatherer& StatsGatherer, unsigned long long NumberPaths, 
	unsigned int NumberEulerSteps)
{
	CheckDimension(NumberEulerSteps);
	auto DiscountFactor = exp(-rptr->Integral(0, TheProduct.GetExercise()));
	
	for (int i = 1; i <= NumberPaths; ++i) {
		auto FinalSpotOnPath = GetFinalSpot(TheProduct.GetExercise(), 
			NumberEulerSteps);
		auto FinalProductValueOnPath = TheProduct.GetPayOff(FinalSpotOnPath);
		auto DiscountedValue = DiscountFactor * FinalProductValueOnPath;
		StatsGatherer.GetDataFromPath(DiscountedValue);
	}

}

void BlackScholesVanillaEngine::CheckDimension(unsigned int NumberEulerSteps)
{
	GeneratorPtr->SetDimensionality(NumberEulerSteps);
	Draws.resize(NumberEulerSteps);
}

double BlackScholesVanillaEngine::GetFinalSpot(double FinalTime, unsigned int
	NumberEulerSteps) {

	GeneratorPtr->GetGaussianDraw(Draws);

	double StepSize = (double) FinalTime / NumberEulerSteps;
	auto CurrentLogSpot = InitialLogSpot;

	auto ExpectationLogSpot = [&CurrentLogSpot, this](double LowerTime,
		double UpperTime) {
			return CurrentLogSpot + rptr->Integral(LowerTime, UpperTime)
				- dptr->Integral(LowerTime, UpperTime) - 0.5 * 
				volptr->IntegralSquare(LowerTime, UpperTime);
	};

	auto VarianceLogSpot = [this](double LowerTime,
		double UpperTime) {
			return volptr->IntegralSquare(LowerTime, UpperTime);
	};

	for (int i = 0; i < NumberEulerSteps; ++i) {
		//cout << ExpectationLogSpot(i * StepSize,
		//	(i + 1) * StepSize) << endl;
		CurrentLogSpot = ExpectationLogSpot(i * StepSize,
			(i + 1) * StepSize) + sqrt(VarianceLogSpot(i * StepSize,
				(i + 1) * StepSize)) * Draws[i];
		//CurrentLogSpot += rptr->Integral(i * StepSize,
		//	(i + 1) * StepSize);
	}

	//cout << CurrentLogSpot << endl;
	//cout << InitialLogSpot + rptr->Integral(0, FinalTime) << endl;

	return exp(CurrentLogSpot);
}


