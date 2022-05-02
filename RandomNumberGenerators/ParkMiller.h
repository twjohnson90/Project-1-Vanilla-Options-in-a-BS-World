#pragma once

class ParkMiller {
public:
	ParkMiller(long Seed_)
		: Seed(Seed_) {}

	long GetOneRandomInteger();
	void SetSeed(long Seed_);
	unsigned long Max(); // need for rescaling to specified range
	unsigned long Min();
private:
	long Seed;
};