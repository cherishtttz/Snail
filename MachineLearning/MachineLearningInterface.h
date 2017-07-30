#pragma once
#include "MachineLearningEXPORT.h"
#include "BaseRegression.h"
#include "BaseCluster.h"

namespace machineLearning
{
	namespace RegressionAnalysis
	{
		MACHINE_LEARNING_API IBaseLinearRegression* snailTrainLinearRegressionModel(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput, const std::string& vModelSig);
		MACHINE_LEARNING_API void evaluateLinearRegressionModel(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput, const IBaseLinearRegression* vModel);
	}

	namespace ClusteringAlgorithm
	{
		MACHINE_LEARNING_API void clusterDataIntoGroups(const std::vector<std::vector<double>>& vOriginalDataset, const std::vector<int>& vFeatureIndexSet, int vNumGroups, const std::string& vClusterAlgorithm, std::vector<SCluster>& voClusters, double vAlpha = 2.1, double vEpsilon = 0.00000001, int vMaxIteration = 100, double vThreshold = 0.000000000001);
	}
}