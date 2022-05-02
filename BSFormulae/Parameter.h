#pragma once

class Parameter {
public:
	Parameter() {};
	virtual ~Parameter() {};

	virtual Parameter* clone() const = 0;

	virtual double Integral(double t_1, double t_2) const = 0;
	virtual double IntegralSquare(double t_1, double t_2) const = 0;
};

class ConstantParameter : public Parameter {
private:
	double Constant;
	double ConstantSquared;
public:
	ConstantParameter(double C)
		: Constant(C), ConstantSquared(C* C) {};
	~ConstantParameter() override {};

	ConstantParameter* clone() const override
	{
		return new ConstantParameter(*this);
	};

	double Integral(double t_1, double t_2) const override
	{
		return (t_2 - t_1) * Constant;
	};
	double IntegralSquare(double t_1, double t_2) const override {
		return (t_2 - t_1) * ConstantSquared;
	};
};

