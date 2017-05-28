#pragma once
#include "BaseCluster.h"

namespace snail
{
	namespace ClusteringAlgorithm
	{
		class CCMeans : public IBaseCluster
		{
		public:
			CCMeans();
			~CCMeans();

			virtual void clusterDataIntoGroups(const std::vector<std::vector<double>>& vOriginalDataset, const std::vector<int>& vFeatureIndexSet, int vNumGroups, std::vector<SCluster>& voClusters, double vAlpha = 2.1, double vEpsilon = 0.00000001, int vMaxIteration = 100, double vThreshold = 0.000000000001) override;

		private:
			void __updateFCM(const std::vector<std::vector<double>>& vDataset, const std::vector<std::vector<double>>& vCenters, double vAlpha, double vEpsilon, std::vector<std::vector<double>>& voFCM);
			void __updateCenters(const std::vector<std::vector<double>>& vDataset, const std::vector<std::vector<double>>& vFCM, double vAlpha, std::vector<std::vector<double>>& voCenters);
			double __calculateObjectFunctionVal(const std::vector<std::vector<double>>& vDataset, const std::vector<std::vector<double>>& vFCM, const std::vector<std::vector<double>>& vCenters, double vAlpha);
			void __fetchClusterResults(const std::vector<std::vector<double>>& vOriginalDataset, const std::vector<std::vector<double>>& vCenters, const std::vector<std::vector<double>>& vFCM, const std::vector<int>& vFeatureIndex, std::vector<SCluster>& voClusters);
		};
	}
}