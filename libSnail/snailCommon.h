#pragma once
#include <string>
#include <vector>

namespace snail
{
	double calculateEuclideanDistance(const std::vector<double>& v1, const std::vector<double>& v2);
	double calculateEuclideanDistance(const std::vector<double>& v1, const std::vector<double>& v2, const std::vector<int>& vUsingFeatureIndexSet);

	namespace SortingAlgorithm
	{
		const std::string COUNTING_SORT = "COUNTING_SORT";
		const std::string RADIX_SORT = "RADIX_SORT";
		const std::string BUCKET_SORT = "BUCKET_SORT";
		const std::string QUICK_SORT = "QUICK_SORT";
	}

	namespace RegressionAnalysis
	{
		const std::string AVERAGE_OUTPUT_REGRESSION = "AVERAGE_OUTPUT_REGRESSION";
		const std::string LEAST_SQUARES_REGRESSION = "LEAST_SQUARES_REGRESSION";
		const std::string FORWARD_STEPWISE_REGRESSION = "FORWARD_STEPWISE_REGRESSION";
		const std::string FORWARD_STAGEWISE_REGRESSION = "FORWARD_STAGEWISE_REGRESSION";
	}

	namespace ClusteringAlgorithm
	{
		const std::string K_MEANS = "K_MEANS";
		const std::string C_MEANS = "C_MEANS";
	}
}