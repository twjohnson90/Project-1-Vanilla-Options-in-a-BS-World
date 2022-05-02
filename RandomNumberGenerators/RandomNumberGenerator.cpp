#include "RandomNumberGenerator.h"
#include "NormalFunctions.h"

using namespace std;

unsigned long RandomNumberGenerator::GetDimensionality() const {
	return Dimensionality;
	}

void RandomNumberGenerator::ResetDimensionality(unsigned int Dimensionality_) {
	Dimensionality = Dimensionality_;
	}

void RandomNumberGenerator::GetGaussianDraw(vector<double>& variates) {

	GetUniformDraw(variates);

	for (unsigned int i = 0; i < Dimensionality; ++i) {
		double x = variates[i];
		variates[i] = InverseCumulativeNormal(x);
	}

	}

RandomParkMiller::RandomParkMiller(unsigned int Dimensionality_, unsigned int Seed_)
	: RandomNumberGenerator(Dimensionality_), InnerGenerator(Seed_), InitialSeed(Seed_)
{
	RescaleFactor = 1.0 / (1.0 + InnerGenerator.Max());
}

void RandomParkMiller::ResetDimensionality(unsigned int Dimensionality_) {
	RandomNumberGenerator::ResetDimensionality(Dimensionality_);
	InnerGenerator.SetSeed(InitialSeed);
}

void RandomParkMiller::GetUniformDraw(vector<double>& variates) {

	for (unsigned long i = 0; i < GetDimensionality(); ++i)
		variates[i] = InnerGenerator.GetOneRandomInteger() * RescaleFactor;

}

void RandomParkMiller::SetSeed(unsigned int Seed_) {
	InnerGenerator.SetSeed(Seed_);
}

void RandomParkMiller::Reset() {
	InnerGenerator.SetSeed(InitialSeed);
}

unique_ptr<RandomNumberGenerator> RandomParkMiller::clone() const {
			return make_unique<RandomParkMiller>(*this);
}