#include "snailInterface.h"
#include <random>
#include <numeric>
#include <unordered_map>
#include <corecrt_io.h>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "BaseIntegerSorting.h"

using namespace snail;
using namespace snail::SortingAlgorithm;
using namespace snail::ClusteringAlgorithm;
using namespace snail::RegressionAnalysis;

//****************************************************************************************************
//FUNCTION:
bool snail::isFileExsit(const std::string& vFilePath)
{
	_ASSERTE(!vFilePath.empty());
	return access(vFilePath.c_str(), 0) == 0;
}

//****************************************************************************************************
//FUNCTION:
int snail::generateRandomIntegerNumber(const int vRangeFrom, const int vRangeTo)
{
	static std::random_device RandomGenerator;
	std::uniform_int_distribution<int> UDistribution;
	UDistribution = vRangeFrom > vRangeTo ? std::uniform_int_distribution<int>(vRangeTo, vRangeFrom) : std::uniform_int_distribution<int>(vRangeFrom, vRangeTo);
	return UDistribution(RandomGenerator);
}

//****************************************************************************************************
//FUNCTION:
void snail::generateRandomIntegerSetWithoutReplacement(const int vMin, const int vMax, const int vSize, std::vector<int>& voIntegerSet)
{
	_ASSERTE(vMin <= vMax && vSize > 0 && vSize <= (vMax - vMin + 1));
	std::unordered_map<int, bool> GeneratedNumbers;
	voIntegerSet.clear();
	while (voIntegerSet.size() != vSize)
	{
		int RandomInt = generateRandomIntegerNumber(vMin, vMax);
		if (GeneratedNumbers.count(RandomInt) == 0)
		{
			GeneratedNumbers[RandomInt] = true;
			voIntegerSet.push_back(RandomInt);
		}
	}
}

//****************************************************************************************************
//FUNCTION:
double snail::generateRandomFloatNumber(const double vRangeFrom, const double vRangeTo)
{
	static std::random_device RandomGenerator;
	std::uniform_real_distribution<double> UDistribution;
	UDistribution = vRangeFrom > vRangeTo ? std::uniform_real_distribution<double>(vRangeTo, vRangeFrom) : std::uniform_real_distribution<double>(vRangeFrom, vRangeTo);
	return UDistribution(RandomGenerator);
}

//****************************************************************************************************
//FUNCTION:
bool snail::snailReadDatasetFromFile(const std::string& vDataFile, std::vector<std::vector<double>>& voDataSet, bool vHeader /*= false*/)
{
	_ASSERTE(!vDataFile.empty());
	voDataSet.clear();
	std::ifstream DataFile(vDataFile);
	if (DataFile.is_open())
	{
		std::string Line;

		if (vHeader)
		{
			getline(DataFile, Line);
			_Log("Ignore header of [" + vDataFile + "] by default.\n");
		}
		while (getline(DataFile, Line))
		{
			std::vector<std::string> InstanceString;
			boost::split(InstanceString, Line, boost::is_any_of(", "));

			std::vector<double> Instance;
			Instance.resize(InstanceString.size());
			int Count = 0;
			std::for_each(Instance.begin(), Instance.end(), [&InstanceString, &Count](double &vData) { vData = std::atof(InstanceString[Count++].c_str()); });
			if (voDataSet.size() && Instance.size() != voDataSet[0].size())
			{
				DataFile.close();
				return false;
			}
			voDataSet.push_back(Instance);
		}
		DataFile.close();
		return true;
	}
	else
	{
		_Log("Failed to open file [" + vDataFile + "], check file path.\n");
		return false;
	}
}

//****************************************************************************************************
//FUNCTION:
CBaseProduct* snail::snailCreateProduct(const std::string& vSig)
{
	_ASSERTE(!vSig.empty());
	return CProductRegistry::getInstance()->createProduct(vSig);
}

//****************************************************************************************************
//FUNCTION:
void snail::SortingAlgorithm::snailSortIntegersSet(std::vector<int>& voIntegersSet, const std::string& vAlgorithmSig)
{
	_ASSERTE(!voIntegersSet.empty() && !vAlgorithmSig.empty());
	std::shared_ptr<IBaseIntegerSorting> pSortAlgorithm = std::shared_ptr<IBaseIntegerSorting>(dynamic_cast<IBaseIntegerSorting*>(snailCreateProduct(vAlgorithmSig)));
	pSortAlgorithm->sortIntegersSetV(voIntegersSet);
}

//****************************************************************************************************
//FUNCTION:
void snail::ClusteringAlgorithm::clusterDataIntoGroups(const std::vector<std::vector<double>>& vOriginalDataset, const std::vector<int>& vFeatureIndexSet, int vNumGroups, const std::string& vClusterAlgorithm, std::vector<SCluster>& voClusters, double vAlpha /*= 2.1*/, double vEpsilon /*= 0.00000001*/, int vMaxIteration /*= 100*/, double vThreshold /*= 0.000000000001*/)
{
	_ASSERTE(!vClusterAlgorithm.empty() && vNumGroups >= 1 && !vFeatureIndexSet.empty() && !vOriginalDataset.empty());
	int MaxColumn = vOriginalDataset[0].size();
	for (auto Itr : vFeatureIndexSet)
		_ASSERTE(Itr >= 0 && Itr < MaxColumn);

#ifdef DEBUG
	_Log("Arguments checking passed.");
#endif

	std::shared_ptr<IBaseCluster> pClusterAlgorithm = std::shared_ptr<IBaseCluster>(dynamic_cast<IBaseCluster*>(snailCreateProduct(vClusterAlgorithm)));

	voClusters.clear();
	pClusterAlgorithm->clusterDataIntoGroups(vOriginalDataset, vFeatureIndexSet, vNumGroups, voClusters, vAlpha, vEpsilon, vMaxIteration, vThreshold);
}

//****************************************************************************************************
//FUNCTION:
IBaseLinearRegression* snail::RegressionAnalysis::snailTrainLinearRegressionModel(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput, const std::string& vModelSig)
{
	_ASSERTE(!vInput.empty() && vInput.size() == vOutput.size() && !vModelSig.empty());

	IBaseLinearRegression* pRegressionModel = dynamic_cast<IBaseLinearRegression*>(snailCreateProduct(vModelSig));
	pRegressionModel->trainV(vInput, vOutput);

	return pRegressionModel;
}

//****************************************************************************************************
//FUNCTION:
void snail::RegressionAnalysis::evaluateLinearRegressionModel(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput, const IBaseLinearRegression* vModel)
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