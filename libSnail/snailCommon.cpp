#include "snailCommon.h"

//****************************************************************************************************
//FUNCTION:
double snail::calculateEuclideanDistance(const std::vector<double>& v1, const std::vector<double>& v2)
{
	_ASSERTE(v1.size() == v2.size());
	double Sum = 0.0;
	for (unsigned int i = 0; i < v1.size(); ++i)
		Sum += std::pow(std::abs(v1[i] - v2[i]), 2.0);
	return std::pow(Sum, 0.5);
}

//****************************************************************************************************
//FUNCTION:
double snail::calculateEuclideanDistance(const std::vector<double>& v1, const std::vector<double>& v2, const std::vector<int>& vUsingFeatureIndexSet)
{
	_ASSERTE(v1.size() == v2.size());
	std::vector<double> Sample1, Sample2;
	for (auto Itr : vUsingFeatureIndexSet)
	{
		_ASSERTE(Itr < v1.size());
		Sample1.push_back(v1[Itr]);
		Sample2.push_back(v2[Itr]);
	}
	return calculateEuclideanDistance(Sample1, Sample2);
}