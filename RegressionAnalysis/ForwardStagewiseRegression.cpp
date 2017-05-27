#include "ForwardStagewiseRegression.h"
#include "Factory.h"
#include "RegressionAnalysisCommon.h"

using namespace snailRegression;

snail::CFactory<CForwardStagewiseRegression> theCreator(FORWARD_STAGEWISE_REGRESSION);

BOOST_CLASS_EXPORT_GUID(CForwardStagewiseRegression, "CForwardStagewiseRegression");

CForwardStagewiseRegression::CForwardStagewiseRegression()
{}

CForwardStagewiseRegression::~CForwardStagewiseRegression()
{}

//****************************************************************************************************
//FUNCTION:
void CForwardStagewiseRegression::trainV(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput)
{
	_ASSERTE(!vInput.empty() && vInput.size() == vOutput.size());

	std::vector<double> R = vOutput;
	m_Coefficients.resize(vInput[0].size(), 0.0);
	int IterationNum = 0;
	double CurrentRss = DBL_MAX;
	while ((IterationNum < m_MaxIter) && (std::abs(CurrentRss - m_RSS) > m_Threshold))
	{
		IterationNum++;
		m_RSS = CurrentRss;

		std::pair<int, double> MostCorrelatedFeature = __findCorrelatedMostFeatureIndex(vInput, R);
		double StageSize = m_StageStepSize * MostCorrelatedFeature.second;
		m_Coefficients[MostCorrelatedFeature.first] += StageSize;
		__updateOutput(vInput, MostCorrelatedFeature.first, StageSize, R);

		CurrentRss = __calculateCurrentRSS(vInput, vOutput);
	}

	if (IterationNum >= m_MaxIter)
	{
		std::cout << "Warning : Training process reached max iteration, model may not converged.\n";
	}
}

//****************************************************************************************************
//FUNCTION:
double CForwardStagewiseRegression::predictV(const std::vector<double>& vInput) const
{
	_ASSERTE(vInput.size() == m_Coefficients.size());

	double PredictResult = 0.0;
	for (auto i = 0; i < vInput.size(); ++i)
		PredictResult += vInput[i] * m_Coefficients[i];
	return PredictResult;
}

//****************************************************************************************************
//FUNCTION:
std::pair<int, double> CForwardStagewiseRegression::__findCorrelatedMostFeatureIndex(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput)
{
	int Index = -1;
	double Cor = -DBL_MAX;
	int NumSamples = vInput.size(), NumFeatures = vInput[0].size();
	for (auto i = 0; i < NumFeatures; ++i)
	{
		double TempCor = 0.0, SumXSquare = 0.0, SumYSquare = 0.0;
		for (auto k = 0; k < NumSamples; ++k)
		{
			TempCor += vInput[k][i] * vOutput[k];
			SumXSquare += std::pow(vInput[k][i], 2);
			SumYSquare += std::pow(vOutput[k], 2);
		}
		TempCor /= (std::pow(SumXSquare, 0.5) * std::pow(SumYSquare, 0.5));
		if (TempCor > Cor)
		{
			Cor = TempCor;
			Index = i;
		}
	}

	return std::make_pair(Index, Cor);
}

//****************************************************************************************************
//FUNCTION:
double CForwardStagewiseRegression::__calculateCurrentRSS(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput)
{
	double RSS = 0.0;
	for (auto i = 0; i < vInput.size(); ++i)
	{
		double PredictResult = predictV(vInput[i]);
		RSS += std::pow(std::abs(PredictResult - vOutput[i]), 2);
	}
	return RSS;
}

//****************************************************************************************************
//FUNCTION:
double CForwardStagewiseRegression::__sign(double vNum)
{
	if (vNum == 0.0) return 0.0;
	return vNum > 0.0 ? 1.0 : -1.0;
}

//****************************************************************************************************
//FUNCTION:
void CForwardStagewiseRegression::__updateOutput(const std::vector<std::vector<double>>& vInput, int vIndex, double vStageSize, std::vector<double>& vOutput)
{
	for (auto i = 0; i < vOutput.size(); ++i)
	{
		vOutput[i] -= vInput[i][vIndex] * vStageSize;
	}
}