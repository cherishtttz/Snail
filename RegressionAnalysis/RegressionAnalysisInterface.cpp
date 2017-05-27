#include "RegressionAnalysisInterface.h"
#include <numeric>
#include "BaseRegression.h"
#include "snailInterface.h"

using namespace snailRegression;

//****************************************************************************************************
//FUNCTION:
IBaseLinearRegression* snailRegression::snailTrainLinearRegressionModel(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput, const std::string& vModelSig)
{
	_ASSERTE(!vInput.empty() && vInput.size() == vOutput.size() && !vModelSig.empty());

	IBaseLinearRegression* pRegressionModel = dynamic_cast<IBaseLinearRegression*>(snail::snailCreateProduct(vModelSig));
	pRegressionModel->trainV(vInput, vOutput);

	return pRegressionModel;
}

//****************************************************************************************************
//FUNCTION:
void snailRegression::evaluateLinearRegressionModel(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput, const IBaseLinearRegression* vModel)
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