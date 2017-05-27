#include "snailInterface.h"
#include <random>

using namespace snail;

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
double snail::generateRandomFloatNumber(const double vRangeFrom, const double vRangeTo)
{
	static std::random_device RandomGenerator;
	std::uniform_real_distribution<double> UDistribution;
	UDistribution = vRangeFrom > vRangeTo ? std::uniform_real_distribution<double>(vRangeTo, vRangeFrom) : std::uniform_real_distribution<double>(vRangeFrom, vRangeTo);
	return UDistribution(RandomGenerator);
}

//****************************************************************************************************
//FUNCTION:
CBaseProduct* snail::snailCreateProduct(const std::string& vSig)
{
	_ASSERTE(!vSig.empty());
	return CProductRegistry::getInstance()->createProduct(vSig);
}