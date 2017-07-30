#include "snailInterface.h"
#include <random>
#include <numeric>
#include <unordered_map>
#include <corecrt_io.h>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

//****************************************************************************************************
//FUNCTION:
bool snail::isFileExsit(const std::string& vFilePath)
{
	_ASSERTE(!vFilePath.empty());
	return access(vFilePath.c_str(), 0) == 0;
}

//*********************************************************************
//FUNCTION:
inline void snail::swapTwoIntegers(int& vA, int& vB)
{
	if (vA == vB) return;
	vA ^= vB;
	vB ^= vA;
	vA ^= vB;
}

//****************************************************************************************************
//FUNCTION:
int snail::generateRandomIntegerNumber(const int vRangeFrom, const int vRangeTo)
{
	static std::random_device RandomGenerator;
	std::uniform_int_distribution<int> UDistribution;
	UDistribution = vRangeFrom > vRangeTo ? std::uniform_int_distribution<int>(vRangeTo, vRangeFrom) : std::uniform_int_distribution<int>(vRangeFrom, vRangeTo);
	return UDistribution(RandomGenerator);
}

//****************************************************************************************************
//FUNCTION:
void snail::generateRandomIntegerSetWithoutReplacement(const int vMin, const int vMax, const int vSize, std::vector<int>& voIntegerSet)
{
	_ASSERTE(vMin <= vMax && vSize > 0 && vSize <= (vMax - vMin + 1));
	std::unordered_map<int, bool> GeneratedNumbers;
	voIntegerSet.clear();
	while (voIntegerSet.size() != vSize)
	{
		int RandomInt = generateRandomIntegerNumber(vMin, vMax);
		if (GeneratedNumbers.count(RandomInt) == 0)
		{
			GeneratedNumbers[RandomInt] = true;
			voIntegerSet.push_back(RandomInt);
		}
	}
}

//****************************************************************************************************
//FUNCTION:
double snail::generateRandomFloatNumber(const double vRangeFrom, const double vRangeTo)
{
	static std::random_device RandomGenerator;
	std::uniform_real_distribution<double> UDistribution;
	UDistribution = vRangeFrom > vRangeTo ? std::uniform_real_distribution<double>(vRangeTo, vRangeFrom) : std::uniform_real_distribution<double>(vRangeFrom, vRangeTo);
	return UDistribution(RandomGenerator);
}

//****************************************************************************************************
//FUNCTION:
bool snail::snailReadDatasetFromFile(const std::string& vDataFile, std::vector<std::vector<double>>& voDataSet, bool vHeader /*= false*/)
{
	_ASSERTE(!vDataFile.empty());
	voDataSet.clear();
	std::ifstream DataFile(vDataFile);
	if (DataFile.is_open())
	{
		std::string Line;

		if (vHeader)
		{
			getline(DataFile, Line);
			_Log("Ignore header of [" + vDataFile + "] by default.\n");
		}
		while (getline(DataFile, Line))
		{
			std::vector<std::string> InstanceString;
			boost::split(InstanceString, Line, boost::is_any_of(", "));

			std::vector<double> Instance;
			Instance.resize(InstanceString.size());
			int Count = 0;
			std::for_each(Instance.begin(), Instance.end(), [&InstanceString, &Count](double &vData) { vData = std::atof(InstanceString[Count++].c_str()); });
			if (voDataSet.size() && Instance.size() != voDataSet[0].size())
			{
				DataFile.close();
				return false;
			}
			voDataSet.push_back(Instance);
		}
		DataFile.close();
		return true;
	}
	else
	{
		_Log("Failed to open file [" + vDataFile + "], check file path.\n");
		return false;
	}
}

//****************************************************************************************************
//FUNCTION:
snail::CBaseProduct* snail::snailCreateProduct(const std::string& vSig)
{
	_ASSERTE(!vSig.empty());
	return snail::CProductRegistry::getInstance()->createProduct(vSig);
}

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