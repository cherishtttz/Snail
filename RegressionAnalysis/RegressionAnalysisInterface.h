#pragma once
#include "RegressionAnalysisExport.h"
#include <vector>
#include <string>
#include "BaseRegression.h"

namespace snailRegression
{
	SNAIL_REGRESSION_DLL_EXPORT IBaseLinearRegression* snailTrainLinearRegressionModel(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput, const std::string& vModelSig);
	SNAIL_REGRESSION_DLL_EXPORT void evaluateLinearRegressionModel(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput, const IBaseLinearRegression* vModel);
}