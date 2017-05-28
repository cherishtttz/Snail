#pragma once
#include <vector>
#include "BaseProduct.h"
#include "snailCommon.h"

namespace snail
{
	namespace ClusteringAlgorithm
	{
		struct SCluster
		{
			std::vector<double> m_Center;
			double m_Variance;
			std::vector<int> m_FeatureIndexSet;
			std::vector<std::vector<double>> m_ClusterSamples;
	
			SCluster() : m_Variance(0.0) {}
	
			//****************************************************************************************************
			//FUNCTION:
			unsigned int getSizeOfCluster() const
			{
				return m_ClusterSamples.size();
			}
	
			//****************************************************************************************************
			//FUNCTION:
			void setCenter(const std::vector<double>& vCenter)
			{
				m_Center.resize(vCenter.size());
				for (unsigned int i = 0; i < m_Center.size(); ++i)
					m_Center[i] = vCenter[i];
			}
	
			//****************************************************************************************************
			//FUNCTION:
			void setFeatureIndexSet(const std::vector<int>& vFeatureIndexSet)
			{
				m_FeatureIndexSet = vFeatureIndexSet;
			}
	
			//****************************************************************************************************
			//FUNCTION:
			void addSamples2Cluster(const std::vector<std::vector<double>>& vDataset, unsigned int vIndex)
			{
				_ASSERTE(vIndex < vDataset.size());
				m_ClusterSamples.push_back(vDataset[vIndex]);
			}
	
			//****************************************************************************************************
			//FUNCTION:
			bool isSampleBelongs2Me(const std::vector<double>& vSample) const
			{
				return std::find(m_ClusterSamples.begin(), m_ClusterSamples.end(), vSample) != m_ClusterSamples.end();
			}
	
			//****************************************************************************************************
			//FUNCTION:
			double distance2Center(const std::vector<double>& vSample) const
			{
				_ASSERTE(!m_ClusterSamples.empty() && vSample.size() == m_ClusterSamples[0].size());
				std::vector<double> SubSample;
				for (auto Itr : m_FeatureIndexSet)
					SubSample.push_back(m_FeatureIndexSet[Itr]);
				return calculateEuclideanDistance(SubSample, m_Center);
			}
		};
	
		class IBaseCluster : public CBaseProduct
		{
		public:
			virtual ~IBaseCluster() {}
	
			virtual void clusterDataIntoGroups(const std::vector<std::vector<double>>& vOriginalDataset, const std::vector<int>& vFeatureIndexSet, int vNumGroups, std::vector<SCluster>& voClusters, double vAlpha = 2.1, double vEpsilon = 0.00000001, int vMaxIteration = 100, double vThreshold = 0.000000000001) = 0;
		protected:
			IBaseCluster() {}
	
			//****************************************************************************************************
			//FUNCTION:
			void _selectSubDataset(const std::vector<std::vector<double>>& vOriginalDataset, const std::vector<int>& vFeatureIndexSet, std::vector<std::vector<double>>& voSubset)
			{
				voSubset.clear();
				unsigned int Row = vOriginalDataset.size(), Col = vFeatureIndexSet.size();
				voSubset.resize(Row);
				for (unsigned int i = 0; i < Row; ++i)
				{
					voSubset[i].resize(Col);
					for (unsigned int k = 0; k < Col; ++k)
					{
						voSubset[i][k] = vOriginalDataset[i][vFeatureIndexSet[k]];
					}
				}
			}
		};
	}
}