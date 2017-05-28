#pragma once
#include "snailEXPORTS.h"
#include <string>
#include <vector>
#include "ProductRegistry.h"
#include "BaseRegression.h"
#include "BaseCluster.h"

namespace snail
{
	SNAIL_DLL_EXPORT bool		isFileExsit(const std::string& vFilePath);
	SNAIL_DLL_EXPORT int		generateRandomIntegerNumber(const int vRangeFrom, const int vRangeTo);
	SNAIL_DLL_EXPORT void		generateRandomIntegerSetWithoutReplacement(const int vMin, const int vMax, const int vSize, std::vector<int>& voIntegerSet);
	SNAIL_DLL_EXPORT double		generateRandomFloatNumber(const double vRangeFrom, const double vRangeTo);
	SNAIL_DLL_EXPORT bool		snailReadDatasetFromFile(const std::string& vDataFile, std::vector<std::vector<double>>& voDataset, bool vHeader = false);
	SNAIL_DLL_EXPORT CBaseProduct* snailCreateProduct(const std::string& vSig);

	namespace SortingAlgorithm
	{
		SNAIL_DLL_EXPORT void snailSortIntegersSet(std::vector<int>& voIntegersSet, const std::string& vAlgorithmSig);
	}

	namespace ClusteringAlgorithm
	{
		SNAIL_DLL_EXPORT void clusterDataIntoGroups(const std::vector<std::vector<double>>& vOriginalDataset, const std::vector<int>& vFeatureIndexSet, int vNumGroups, const std::string& vClusterAlgorithm, std::vector<SCluster>& voClusters, double vAlpha = 2.1, double vEpsilon = 0.00000001, int vMaxIteration = 100, double vThreshold = 0.000000000001);
	}

	namespace RegressionAnalysis
	{
		SNAIL_DLL_EXPORT IBaseLinearRegression* snailTrainLinearRegressionModel(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput, const std::string& vModelSig);
		SNAIL_DLL_EXPORT void evaluateLinearRegressionModel(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput, const IBaseLinearRegression* vModel);
	}
}