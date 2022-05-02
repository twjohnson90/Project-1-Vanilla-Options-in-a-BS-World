#pragma once

#include "PayOff.h"

#include <memory>

class VanillaOption {
	using UniPtrPayOff = std::unique_ptr<PayOff>;
private:
	double Exercise;
	UniPtrPayOff PayOffPtr;
public:
	VanillaOption(double T_, const PayOff& ThePayOff)
		: Exercise(T_), PayOffPtr(ThePayOff.clone()) {};

	double GetExercise() const {
		return Exercise;
	}
	double GetPayOff(double Spot) const {
		return (* PayOffPtr)(Spot);
	}
};

