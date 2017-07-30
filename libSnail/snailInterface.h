#pragma once
#include "snailEXPORTS.h"
#include <string>
#include <vector>
#include "ProductRegistry.h"

namespace snail
{
	template <typename T>
	bool isInBetween(const T& vData, const T& vMin, const T& vMax);

	template <typename T>
	size_t getFirstGreaterElementIndex(const std::vector<T>& vVec, int vFrom, int vTo, const T& vVal);

	SNAIL_API bool		isFileExsit(const std::string& vFilePath);
	SNAIL_API void		swapTwoIntegers(int& vA, int& vB);
	SNAIL_API int		generateRandomIntegerNumber(const int vRangeFrom, const int vRangeTo);
	SNAIL_API void		generateRandomIntegerSetWithoutReplacement(const int vMin, const int vMax, const int vSize, std::vector<int>& voIntegerSet);
	SNAIL_API double	generateRandomFloatNumber(const double vRangeFrom, const double vRangeTo);
	SNAIL_API bool		snailReadDatasetFromFile(const std::string& vDataFile, std::vector<std::vector<double>>& voDataset, bool vHeader = false);
	SNAIL_API CBaseProduct* snailCreateProduct(const std::string& vSig);
	SNAIL_API double	calculateEuclideanDistance(const std::vector<double>& v1, const std::vector<double>& v2);
	SNAIL_API double	calculateEuclideanDistance(const std::vector<double>& v1, const std::vector<double>& v2, const std::vector<int>& vUsingFeatureIndexSet);
}

//*********************************************************************
//FUNCTION:
template <typename T>
inline bool snail::isInBetween(const T& vData, const T& vMin, const T& vMax)
{
	return vData >= vMin && vData <= vMax;
}

//*********************************************************************
//FUNCTION: NOT TESTED
template <typename T>
size_t snail::getFirstGreaterElementIndex(const std::vector<T>& vVec, int vFrom, int vTo, const T& vVal)
{
	_ASSERTE(isInBetween(vFrom, 0, vVec.size() - 1) && isInBetween(vTo, 0, vVec.size() - 1));
	return std::upper_bound(vVec.begin() + vFrom, vVec.begin() + vTo, vVal) - vVec.begin();
}