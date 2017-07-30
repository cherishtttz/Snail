#pragma once
#include "BaseCluster.h"

namespace machineLearning
{
	namespace ClusteringAlgorithm
	{
		class CKMeans : public IBaseCluster
		{
		public:
			CKMeans(void);
			~CKMeans(void);

			virtual void clusterDataIntoGroups(const std::vector<std::vector<double>>& vOriginalDataset, const std::vector<int>& vFeatureIndexSet, int vNumGroups, std::vector<SCluster>& voClusters, double vAlpha /* = 1.0 */, double vEpsilon /* = 0.0 */, int vMaxIteration /* = 100 */, double vThreshold /* = 0.01 */);

		private:
			std::vector<double> __getMeans(const std::vector<std::vector<double>>& vClusterGroup);
			void __updateClusterGroup(const std::vector<std::vector<double>>& vDataset, int vNumGroups, std::vector<SCluster>& voClusters);
			double __getVariance(std::vector<SCluster>& voClusters);
		};
	}
}