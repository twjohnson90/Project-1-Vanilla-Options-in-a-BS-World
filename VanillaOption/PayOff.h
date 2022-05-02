#pragma once

#include <algorithm>

class PayOff {
public:
	virtual ~PayOff() {};

	virtual PayOff* clone() const = 0;

	virtual double operator()(double Spot) const = 0;
};

class PayOffCall : public PayOff {
private:
	double Strike;
public:
	PayOffCall(double K)
		: Strike(K) {};
	~PayOffCall() override {};

	PayOffCall* clone() const override {
		return new PayOffCall(*this);
	}

	virtual double operator()(double Spot) const override {
		return std::max(Spot - Strike, 0.0);
	}
};
