#pragma once

#include "Parameter.h"
#include "VanillaOption.h"
#include "StatisticsGatherer.h"
#include "RandomNumberGenerator.h"

#include <vector>
#include <memory>

class VanillaEngine {
public:
	VanillaEngine(const Parameter& r)
		: rptr(r.clone()) {};
	virtual ~VanillaEngine() {};

	void RunSimulation(const VanillaOption& TheProduct, StatisticsGatherer&
		StatsGatherer, unsigned long long, unsigned int);
	virtual void CheckDimension(unsigned int) = 0;
	virtual double GetFinalSpot(double, unsigned int) = 0; // non-const as effects RNG
protected:
	std::unique_ptr<Parameter> rptr;
};

class BlackScholesVanillaEngine : public VanillaEngine {
public:
	BlackScholesVanillaEngine(const Parameter& d, const Parameter& r, double
		Spot, const Parameter& vol, const RandomNumberGenerator& Generator)
		: dptr(d.clone()), VanillaEngine(r), InitialLogSpot(log(Spot)), 
		volptr(vol.clone()), GeneratorPtr(Generator.clone()) {};
	~BlackScholesVanillaEngine() override {};

	void CheckDimension(unsigned int) override;
	double GetFinalSpot(double, unsigned int) override;
private:
	std::unique_ptr<Parameter> dptr, volptr;
	double InitialLogSpot;
	std::unique_ptr<RandomNumberGenerator> GeneratorPtr;
	std::vector<double> Draws;
};