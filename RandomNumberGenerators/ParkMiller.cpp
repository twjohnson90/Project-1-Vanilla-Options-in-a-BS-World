#include "ParkMiller.h"

long ParkMiller::GetOneRandomInteger() {

	static const int a = 16807;
	static const int m = 2147483647;
	static const int q = 127773;
	static const int r = 2836;
	
	long k = Seed / q;
	long SeedModq = Seed - k * q;

	Seed = a * SeedModq - r * k;
	if (Seed < 0)
		Seed += m;

	return Seed;
}

void ParkMiller::SetSeed(long Seed_) {
	if (Seed_ == 0) // 0 Seed just gives 0 on repeat
		Seed_ = 1;
	Seed = Seed_;
}

unsigned long ParkMiller::Max() {
	return 2147483647 - 1;
}

unsigned long ParkMiller::Min() {
	return 1;
}