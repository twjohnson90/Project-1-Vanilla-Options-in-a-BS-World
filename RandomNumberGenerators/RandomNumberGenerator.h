#pragma once

#include "ParkMiller.h"

#include <vector>
#include <memory>

class RandomNumberGenerator {
public:
	RandomNumberGenerator(unsigned int Dimensionality_)
		: Dimensionality(Dimensionality_) {}
	virtual ~RandomNumberGenerator() {};

	virtual std::unique_ptr<RandomNumberGenerator> clone() const = 0;

	inline unsigned long GetDimensionality() const;
	virtual void ResetDimensionality(unsigned int);
	virtual void SetSeed(unsigned int) = 0;

	virtual void GetUniformDraw(std::vector<double>&) = 0; // cannot be constant as will ultimately change the seed data member of whatever generator we use
	virtual void GetGaussianDraw(std::vector<double>&); // cannot be const as calls GetUniforms
	virtual void Reset() = 0;
	virtual void SkipPaths(unsigned int);
private:
	unsigned int Dimensionality;
};

class RandomParkMiller : public RandomNumberGenerator {
public:
	RandomParkMiller(unsigned int Dimensionality_, unsigned int Seed_);
	~RandomParkMiller() override {};

	std::unique_ptr<RandomNumberGenerator> clone() const override;

	void ResetDimensionality(unsigned int) override;
	void SetSeed(unsigned int) override;

	void GetUniformDraw(std::vector<double>&) override;
	void Reset() override;
	
private:
	ParkMiller InnerGenerator;
	unsigned int InitialSeed;   // need for resetting
	double RescaleFactor; // what need multiply to ensure in (0,1)
};