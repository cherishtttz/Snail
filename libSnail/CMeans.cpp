#include "CMeans.h"
#include <numeric>
#include <algorithm>
#include "snailCommon.h"
#include "Factory.h"
#include "snailInterface.h"

using namespace snail;
using namespace snail::ClusteringAlgorithm;

CFactory<CCMeans> theCreator(C_MEANS);

CCMeans::CCMeans()
{

}

CCMeans::~CCMeans()
{

}

//****************************************************************************************************
//FUNCTION:
void CCMeans::clusterDataIntoGroups(const std::vector<std::vector<double>>& vOriginalDataset, const std::vector<int>& vFeatureIndexSet, int vNumGroups, std::vector<SCluster>& voClusters, double vAlpha /* = 1.0 */, double vEpsilon /* = 0.0 */, int vMaxIteration /* = 100 */, double vThreshold /* = 0.01 */)
{
	std::vector<std::vector<double>> Subset;
	_selectSubDataset(vOriginalDataset, vFeatureIndexSet, Subset);
	std::vector<int> CenterIndex;
	snail::generateRandomIntegerSetWithoutReplacement(0, Subset.size() - 1, vNumGroups, CenterIndex);
	std::vector<std::vector<double>> Centers;
	for (auto Itr : CenterIndex)
		Centers.push_back(Subset[Itr]);
	std::vector<std::vector<double>> FCM;
	FCM.resize(Subset.size());
	for (auto &Itr : FCM) Itr.resize(vNumGroups, 0.0);

	__updateFCM(Subset, Centers, vAlpha, vEpsilon, FCM);

	double PreObj = -FLT_MAX;
	int NumItr = 0;
	while (true)
	{
		__updateCenters(Subset, FCM, vAlpha, Centers);
		__updateFCM(Subset, Centers, vAlpha, vEpsilon, FCM);

		double CurrentObj = __calculateObjectFunctionVal(Subset, FCM, Centers, vAlpha);
		if (std::abs(PreObj - CurrentObj) < vThreshold || NumItr++ >= vMaxIteration)
			break;
		PreObj = CurrentObj;
	}
	std::cout << "Cluster finish with minimum object function value : " << PreObj << std::endl;
	std::cout << "Number of iterations runs : " << NumItr << std::endl;
	__fetchClusterResults(vOriginalDataset, Centers, FCM, vFeatureIndexSet, voClusters);
}

//****************************************************************************************************
//FUNCTION:
void CCMeans::__updateFCM(const std::vector<std::vector<double>>& vDataset, const std::vector<std::vector<double>>& vCenters, double vAlpha, double vEpsilon, std::vector<std::vector<double>>& voFCM)
{
	_ASSERTE(!voFCM.empty());
	unsigned int Row = voFCM.size(), Col = voFCM[0].size();
	for (unsigned int i = 0; i < Row; ++i)
	{
		for (unsigned int j = 0; j < Col; ++j)
		{
			double Sum = 0.0;
			double Dij = calculateEuclideanDistance(vDataset[i], vCenters[j]);
			for (unsigned int l = 0; l < Col; ++l)
			{
				double Dil = calculateEuclideanDistance(vDataset[i], vCenters[l]);
				Sum += std::pow((Dij + vEpsilon) / (Dil + vEpsilon), 2.0 / (vAlpha - 1.0));
			}
			voFCM[i][j] = 1.0 / Sum;
		}
	}
}

//****************************************************************************************************
//FUNCTION:
void CCMeans::__updateCenters(const std::vector<std::vector<double>>& vDataset, const std::vector<std::vector<double>>& vFCM, double vAlpha, std::vector<std::vector<double>>& voCenters)
{
	std::vector<double> SumUjAlpha;
	unsigned int NumInstance = vFCM.size(), NumCenters = voCenters.size(), DataDim = vDataset[0].size();
	SumUjAlpha.resize(NumCenters, 0.0);
	for (unsigned int j = 0; j < NumCenters; ++j)
	{
		std::for_each(voCenters[j].begin(), voCenters[j].end(), [](double &data) { data = 0.0; });
		for (unsigned int i = 0; i < NumInstance; ++i)
		{
			double UijAlpha = std::pow(vFCM[i][j], vAlpha);
			for (unsigned int Dim = 0; Dim < DataDim; ++Dim)
				voCenters[j][Dim] += UijAlpha * vDataset[i][Dim];
			SumUjAlpha[j] += UijAlpha;
		}
		for (unsigned int Dim = 0; Dim < DataDim; ++Dim)
			voCenters[j][Dim] /= SumUjAlpha[j];
	}
}

//****************************************************************************************************
//FUNCTION:
double CCMeans::__calculateObjectFunctionVal(const std::vector<std::vector<double>>& vDataset, const std::vector<std::vector<double>>& vFCM, const std::vector<std::vector<double>>& vCenters, double vAlpha)
{
	double Obj = 0.0;
	unsigned int NumClusters = vCenters.size(), NumInstances = vDataset.size();
	for (unsigned int j = 0; j < NumClusters; ++j)
	{
		for (unsigned int i = 0; i < NumInstances; ++i)
		{
			Obj += std::pow(vFCM[i][j], vAlpha) * std::pow(calculateEuclideanDistance(vDataset[i], vCenters[j]), 2.0);
		}
	}
	return Obj;
}

//****************************************************************************************************
//FUNCTION:
void CCMeans::__fetchClusterResults(const std::vector<std::vector<double>>& vOriginalDataset, const std::vector<std::vector<double>>& vCenters, const std::vector<std::vector<double>>& vFCM, const std::vector<int>& vFeatureIndex, std::vector<SCluster>& voClusters)
{
	voClusters.clear();
	voClusters.resize(vCenters.size());
	for (unsigned int i = 0; i < vCenters.size(); ++i)
	{
		voClusters[i].setCenter(vCenters[i]);
		voClusters[i].setFeatureIndexSet(vFeatureIndex);
	}
	for (unsigned int i = 0; i < vFCM.size(); ++i)
	{
		int ClusterIndexToBelong = std::max_element(vFCM[i].begin(), vFCM[i].end()) - vFCM[i].begin();
		voClusters[ClusterIndexToBelong].addSamples2Cluster(vOriginalDataset, i);
	}
}