#include "KMeans.h"
#include "snailCommon.h"
#include "Factory.h"
#include "snailInterface.h"

using namespace snail;
using namespace snail::ClusteringAlgorithm;

CFactory<CKMeans> theCreator(K_MEANS);

CKMeans::CKMeans(void)
{
}

CKMeans::~CKMeans(void)
{
}

//****************************************************************************************************
//FUNCTION:
void CKMeans::clusterDataIntoGroups(const std::vector<std::vector<double>>& vOriginalDataset, const std::vector<int>& vFeatureIndexSet, int vNumGroups, std::vector<SCluster>& voClusters, double vAlpha, double vEpsilon, int vMaxIteration, double vThreshold)
{
	_ASSERTE((!vOriginalDataset.empty()) && (!vFeatureIndexSet.empty()));

	std::vector<std::vector<double>> Dataset;
	Dataset.resize(vOriginalDataset.size());
	for (int i = 0; i < vOriginalDataset.size(); ++i)
	{
		Dataset[i].resize(vFeatureIndexSet.size());
		for (int j = 0; j < vFeatureIndexSet.size(); ++j)
			Dataset[i][j] = vOriginalDataset[i][vFeatureIndexSet[j]];
	}

	std::vector<int> InitialCenterIndexSet;
	snail::generateRandomIntegerSetWithoutReplacement(0, Dataset.size() - 1, vNumGroups, InitialCenterIndexSet);
	voClusters.resize(vNumGroups);
	for (int i = 0; i < vNumGroups; ++i)
	{
		voClusters[i].m_Center = Dataset[InitialCenterIndexSet[i]];
		voClusters[i].setFeatureIndexSet(vFeatureIndexSet);
	}
	__updateClusterGroup(Dataset, vNumGroups, voClusters);
	
	double OldVariance = -1;
	double NewVariance = __getVariance(voClusters);
	int NumItr = 0;
	while (NumItr++ < vMaxIteration && (fabs(NewVariance - OldVariance) >= vThreshold))
	{
		for (int j = 0; j < vNumGroups; ++j)
			voClusters[j].m_Center = __getMeans(voClusters[j].m_ClusterSamples);
		
		OldVariance = NewVariance;
		NewVariance = __getVariance(voClusters);

		__updateClusterGroup(Dataset, vNumGroups, voClusters);
	}
	std::cout << "Cluster finish with minimum object function value : " << NewVariance << std::endl;
	std::cout << "Number of iterations runs : " << NumItr << std::endl;
}

//****************************************************************************************************
//FUNCTION:
std::vector<double> CKMeans::__getMeans(const std::vector<std::vector<double>>& vm_ClusterSamples)
{
	std::vector<double> Means;
	int NumGroup = vm_ClusterSamples.size();
	Means.resize(vm_ClusterSamples[0].size());
	for (int j = 0; j < vm_ClusterSamples[j].size(); ++j)
	{
		for (int i = 0; i < NumGroup; ++i)
		{
			Means[j] += vm_ClusterSamples[i][j];
		}
		Means[j] /= NumGroup;
	}

	return Means;
}

//****************************************************************************************************
//FUNCTION:
void CKMeans::__updateClusterGroup(const std::vector<std::vector<double>>& vDataset, int vNumGroups, std::vector<SCluster>& voClusters)
{
	for (int j = 0; j < vNumGroups; ++j)
		voClusters[j].m_ClusterSamples.clear();

	for (int i = 0; i < vDataset.size(); ++i)
	{
		double Distance = FLT_MAX;
		int CenterIndex = 0;
		for (int j = 0; j < vNumGroups; ++j)
		{
			double CurrentDistance = calculateEuclideanDistance(vDataset[i], voClusters[j].m_Center);
			if (CurrentDistance < Distance)
			{
				CenterIndex = j;
				Distance = CurrentDistance;
			}
		}
		(voClusters[CenterIndex].m_ClusterSamples).push_back(vDataset[i]);
	}
}

//****************************************************************************************************
//FUNCTION:
double CKMeans::__getVariance(std::vector<SCluster>& voClusters)
{
	double Variance = 0.0;
	for (int i = 0; i < voClusters.size(); ++i)
		for (int j = 0; j < voClusters[i].m_ClusterSamples.size(); ++j)
			Variance += calculateEuclideanDistance(voClusters[i].m_ClusterSamples[j], voClusters[i].m_Center);

	return Variance;
}