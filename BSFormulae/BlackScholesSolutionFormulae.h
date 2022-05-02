#pragma once

#include "Parameter.h"

double ZeroCouponBond(const Parameter& r, double Time, double Maturity);

double Forward(const Parameter& d, double Exercise, const Parameter& r,
	 double Spot, double Strike, double Time);

double BlackScholesCall(const Parameter& d, double Exercise, const Parameter& r,
	double Spot, double Strike, double Time, const Parameter& vol);

double BlackScholesPut(const Parameter& d, double Exercise, const Parameter& r,
	double Spot, double Strike, double Time, const Parameter& vol);

double BlackScholesDigitalCall(const Parameter& d, double Exercise, const Parameter& r,
	double Spot, double Strike, double Time, const Parameter& vol);

double BlackScholesDigitalPut(const Parameter& d, double Exercise, const Parameter& r,
	double Spot, double Strike, double Time, const Parameter& vol);

double BlackScholesCallSpread(const Parameter& d, double Exercise, 
	const Parameter& r, double Spot, double Strike, double Time, 
	const Parameter& vol, double epsilion);