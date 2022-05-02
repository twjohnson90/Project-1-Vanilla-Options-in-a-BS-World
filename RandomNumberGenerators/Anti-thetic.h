#pragma once

#include "RandomNumberGenerator.h"

class AntiThetic : public RandomNumberGenerator {
public:
	AntiThetic(const
		RandomNumberGenerator& InnerGenerator_)
		: RandomNumberGenerator(InnerGenerator_),
		InnerGenerator(InnerGenerator_.clone()) {
		
		DrawAntiThetic = false;
		PreviousDraw.resize(GetDimensionality());
	}
	AntiThetic(const AntiThetic& Original)
		: RandomNumberGenerator(Original), 
		InnerGenerator(Original.InnerGenerator ? 
			Original.InnerGenerator->clone() : nullptr),
		DrawAntiThetic(Original.DrawAntiThetic), 
		PreviousDraw(Original.PreviousDraw) {};
	~AntiThetic() override {};

	std::unique_ptr<RandomNumberGenerator> clone() const override {
		if (this) {
			return std::make_unique<AntiThetic>(*this);
		}
		else return nullptr;
	}

	void SetDimensionality(unsigned long long) override;
	void SetSeed(unsigned int) override;

	void GetUniformDraw(std::vector<double>& Draws) override;
private:
	std::unique_ptr<RandomNumberGenerator> InnerGenerator;
	bool DrawAntiThetic;
	std::vector<double> PreviousDraw;
};

