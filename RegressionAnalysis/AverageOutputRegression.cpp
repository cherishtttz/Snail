#include "AverageOutputRegression.h"
#include <numeric>
#include "Factory.h"
#include "RegressionAnalysisCommon.h"

using namespace snailRegression;

snail::CFactory<CAverageOutputRegression> theCreator(AVERAGE_OUTPUT_REGRESSION);

BOOST_CLASS_EXPORT_GUID(CAverageOutputRegression, "CAverageOutputRegression");

CAverageOutputRegression::CAverageOutputRegression()
{}

CAverageOutputRegression::~CAverageOutputRegression()
{}

//****************************************************************************************************
//FUNCTION:
void CAverageOutputRegression::trainV(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput)
{
	_ASSERTE(!vInput.empty() && vInput.size() == vOutput.size());

	m_SingleInputSize = vInput[0].size();
	m_PredictValue = std::accumulate(vOutput.begin(), vOutput.end(), 0.0) / vOutput.size();
}

//****************************************************************************************************
//FUNCTION:
double CAverageOutputRegression::predictV(const std::vector<double>& vInput) const
{
	_ASSERTE(vInput.size() == m_SingleInputSize);

	return m_PredictValue;
}