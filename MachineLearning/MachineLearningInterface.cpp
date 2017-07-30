#include "MachineLearningInterface.h"
#include "snailInterface.h"
#include <numeric>

using namespace machineLearning;

//****************************************************************************************************
//FUNCTION:
void ClusteringAlgorithm::clusterDataIntoGroups(const std::vector<std::vector<double>>& vOriginalDataset, const std::vector<int>& vFeatureIndexSet, int vNumGroups, const std::string& vClusterAlgorithm, std::vector<SCluster>& voClusters, double vAlpha /*= 2.1*/, double vEpsilon /*= 0.00000001*/, int vMaxIteration /*= 100*/, double vThreshold /*= 0.000000000001*/)
{
	_ASSERTE(!vClusterAlgorithm.empty() && vNumGroups >= 1 && !vFeatureIndexSet.empty() && !vOriginalDataset.empty());
	int MaxColumn = vOriginalDataset[0].size();
	for (auto Itr : vFeatureIndexSet)
		_ASSERTE(Itr >= 0 && Itr < MaxColumn);

#ifdef DEBUG
	_Log("Arguments checking passed.");
#endif

	std::shared_ptr<IBaseCluster> pClusterAlgorithm = std::shared_ptr<IBaseCluster>(dynamic_cast<IBaseCluster*>(snail::snailCreateProduct(vClusterAlgorithm)));

	voClusters.clear();
	pClusterAlgorithm->clusterDataIntoGroups(vOriginalDataset, vFeatureIndexSet, vNumGroups, voClusters, vAlpha, vEpsilon, vMaxIteration, vThreshold);
}

//****************************************************************************************************
//FUNCTION:
RegressionAnalysis::IBaseLinearRegression* RegressionAnalysis::snailTrainLinearRegressionModel(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput, const std::string& vModelSig)
{
	_ASSERTE(!vInput.empty() && vInput.size() == vOutput.size() && !vModelSig.empty());

	RegressionAnalysis::IBaseLinearRegression* pRegressionModel = dynamic_cast<IBaseLinearRegression*>(snail::snailCreateProduct(vModelSig));
	pRegressionModel->trainV(vInput, vOutput);

	return pRegressionModel;
}

//****************************************************************************************************
//FUNCTION:
void RegressionAnalysis::evaluateLinearRegressionModel(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput, const IBaseLinearRegression* vModel)
{
	_ASSERTE(!vInput.empty() && vInput.size() == vOutput.size() && vModel);
	double RSS = 0.0;
	std::vector<double> DifferSet;
	for (auto i = 0; i < vOutput.size(); ++i)
	{
		double PredictResult = vModel->predictV(vInput[i]);
		std::cout << "Predict the " << i + 1 << " th sample, original = " << vOutput[i] << ", predict value = " << PredictResult << ".\n";
		DifferSet.push_back(std::abs(vOutput[i] - PredictResult));
		RSS += std::pow(std::abs(vOutput[i] - PredictResult), 2.0);
	}
	std::cout << "Minimum error : " << *std::min_element(DifferSet.begin(), DifferSet.end()) << "\n";
	std::cout << "Maximum error : " << *std::max_element(DifferSet.begin(), DifferSet.end()) << "\n";
	std::cout << "Average error : " << std::accumulate(DifferSet.begin(), DifferSet.end(), 0.0) / DifferSet.size() << "\n";
	std::cout << "Rss reached value : " << RSS << "\n\n";
}