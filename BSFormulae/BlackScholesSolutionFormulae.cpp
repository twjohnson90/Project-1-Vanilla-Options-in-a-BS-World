
#include "BlackScholesSolutionFormulae.h"
#include "NormalFunctions.h"

#include <cmath>

double ZeroCouponBond(double Maturity, const Parameter& r, double Time) {
	auto x = r.Integral(Time, Maturity);
	return exp(-x);
}

double Forward(const Parameter& d, double Exercise, const Parameter& r,
	double Spot, double Strike, double Time) {

	auto x = d.Integral(Time, Exercise);
	auto y = r.Integral(Time, Exercise);

	return exp(-x) * Spot - Strike * exp(-y);
}

double BlackScholesCall(const Parameter& d, double Exercise, const Parameter& r,
	double Spot, double Strike, double Time, const Parameter& vol) {

	auto d1 = (log(Spot / Strike) + r.Integral(Time, Exercise)
		- d.Integral(Time, Exercise) + 0.5 * vol.IntegralSquare(Time, Exercise))
		/ (sqrt(vol.IntegralSquare(Time, Exercise)));
	auto d2 = d1 - sqrt(vol.IntegralSquare(Time, Exercise));

	return exp(-d.Integral(Time, Exercise)) * Spot * CumulativeNormal(d1)
		- Strike * exp(-r.Integral(Time, Exercise))*CumulativeNormal(d2);
}

double BlackScholesPut(const Parameter& d, double Exercise, const Parameter& r,
	double Spot, double Strike, double Time, const Parameter& vol) {

	return BlackScholesCall(d, Exercise, r, Spot, Strike, Time, vol)
		- Forward(d, Exercise, r, Spot, Strike, Time);
}

double BlackScholesDigitalCall(const Parameter& d, double Exercise,
	const Parameter& r, double Spot, double Strike, double Time,
	const Parameter& vol) {

	auto d1 = (log(Spot / Strike) + r.Integral(Time, Exercise)
		- d.Integral(Time, Exercise) + 0.5 * vol.IntegralSquare(Time, Exercise))
		/ (sqrt(vol.IntegralSquare(Time, Exercise)));
	auto d2 = d1 - sqrt(vol.IntegralSquare(Time, Exercise));

	return exp(-r.Integral(Time, Exercise)) * CumulativeNormal(d2);
}

double BlackScholesDigitalPut(const Parameter& d, double Exercise,
	const Parameter& r, double Spot, double Strike, double Time,
	const Parameter& vol) {

	return ZeroCouponBond(Exercise, r, Time) - BlackScholesDigitalCall(d, 
		Exercise, r, Spot, Strike, Time, vol);
}

double BlackScholesCallSpread(const Parameter& d, double Exercise,
	const Parameter& r, double Spot, double Strike, double Time,
	const Parameter& vol, double epsilon) {

	return (BlackScholesCall(d, Exercise, r, Spot, Strike - epsilon, Time, vol) -
		BlackScholesCall(d, Exercise, r, Spot, Strike + epsilon, Time, vol))
		/ (2 * epsilon);
}