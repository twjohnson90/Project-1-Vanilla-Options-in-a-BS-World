#pragma once

#include <string>
#include <iostream>
#include <fstream>

template<class f> 
// requisites: f has function-like syntax
void OutputPlottingData(const f& TheFunction, double LowerBound, double UpperBound,
	const std::string& Title, const std::string& xLabel, const std::string& yLabel)
	// function to out put graphing data of f to txt file to be read by python
{
	std::string FileName = Title + ".txt";
	std::ofstream ost{ FileName };
	ost << Title << std::endl << xLabel << std::endl << yLabel << std::endl;
	
	double x = LowerBound;
	while (x <= UpperBound + 0.1) {
		ost << x << '\t' << TheFunction(x) << std::endl;
		x += 0.1;
	}

}