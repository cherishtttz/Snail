#include "ForwardStepwiseRgression.h"
#include "Factory.h"
#include "snailCommon.h"

using namespace snail;
using namespace snail::RegressionAnalysis;

CFactory<CForwardStepwiseRegression> theCreator(FORWARD_STEPWISE_REGRESSION);

BOOST_CLASS_EXPORT_GUID(CForwardStepwiseRegression, "CForwardStepwiseRegression");

CForwardStepwiseRegression::CForwardStepwiseRegression()
{}

CForwardStepwiseRegression::~CForwardStepwiseRegression()
{}

//****************************************************************************************************
//FUNCTION:
void CForwardStepwiseRegression::trainV(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput)
{
	_ASSERTE(!vInput.empty() && vInput.size() == vOutput.size());

	int FeatureSize = vInput[0].size();
	int NumSamples = vInput.size();

	__initialize(FeatureSize);
	__generateCorrelationMap(vInput, vOutput);

	int MostCorrectedFeatureIndex = __getCurrentMostCorrelatedFeatureIndex();
	double DotProduct = 0.0, ModuleX = 0.0;
	for (auto i = 0; i < NumSamples; ++i)
	{
		DotProduct += vInput[i][MostCorrectedFeatureIndex] * vOutput[i];
		ModuleX += pow(vInput[i][MostCorrectedFeatureIndex], 2);
	}
	m_Coefficients[MostCorrectedFeatureIndex] = DotProduct / ModuleX;

	std::vector<double> Residuals;
	Residuals.resize(NumSamples);
	while (!m_IndexesSet.empty())
	{
		for (auto j = 0; j < NumSamples; ++j)
		{
			double Yhat = 0.0;
			for (auto i = 0; i < FeatureSize; ++i)
				Yhat += vInput[j][i] * m_Coefficients[i];
			Residuals[j] = vOutput[j] - Yhat;
		}

		m_IndexesSet.erase(std::remove(m_IndexesSet.begin(), m_IndexesSet.end(), MostCorrectedFeatureIndex), m_IndexesSet.end());
		if (m_IndexesSet.size() != 0)
		{
			MostCorrectedFeatureIndex = __getCurrentMostCorrelatedFeatureIndex();
			double DotProduct = 0.0, ModuleX = 0.0;
			for (auto j = 0; j < NumSamples; ++j)
			{
				DotProduct += vInput[j][MostCorrectedFeatureIndex] * Residuals[j];
				ModuleX += pow(vInput[j][MostCorrectedFeatureIndex], 2);
			}
			m_Coefficients[MostCorrectedFeatureIndex] = DotProduct / ModuleX;
		}
	}
}

//****************************************************************************************************
//FUNCTION:
void CForwardStepwiseRegression::__initialize(int vSingleInputSize)
{
	_ASSERTE(vSingleInputSize > 0);

	m_Coefficients.resize(vSingleInputSize, 0.0);
	m_IndexesSet.resize(vSingleInputSize, 0);
	for (auto i = 0; i < vSingleInputSize; ++i)
	{
		m_IndexesSet[i] = i;
	}
}

//****************************************************************************************************
//FUNCTION:
void CForwardStepwiseRegression::__generateCorrelationMap(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput)
{
	_ASSERTE(!vInput.empty() && vInput.size() == vOutput.size());

	int vSingleInputSize = vInput[0].size();
	int NumSamples = vInput.size();
	for (auto Itr : m_IndexesSet)
	{
		double SumX = 0.0, SumY = 0.0, SumXY = 0.0, SumSquareX = 0.0, SumSquareY = 0.0;
		for (auto j = 0; j < NumSamples; ++j)
		{
			SumX += vInput[j][Itr];
			SumY += vOutput[j];
			SumXY += vInput[j][Itr] * vOutput[j];
			SumSquareX += pow(vInput[j][Itr], 2);
			SumSquareY += pow(vOutput[j], 2);
		}
		double PearsonCorrelation = ((NumSamples*SumXY) - (SumX*SumY)) / sqrt((NumSamples*SumSquareX) - pow(SumX, 2)) / sqrt((NumSamples*SumSquareY) - pow(SumY, 2));
		m_CorrelationMap[PearsonCorrelation] = Itr;
	}
	_ASSERTE(m_CorrelationMap.size() == vSingleInputSize);
	m_Itr = m_CorrelationMap.rbegin();
}

//****************************************************************************************************
//FUNCTION:
int CForwardStepwiseRegression::__getCurrentMostCorrelatedFeatureIndex()
{
	_ASSERTE(m_Itr != m_CorrelationMap.rend());

	return (m_Itr++)->second;
}

//****************************************************************************************************
//FUNCTION:
double CForwardStepwiseRegression::predictV(const std::vector<double>& vInput) const
{
	_ASSERTE(vInput.size() == m_Coefficients.size());

	double PredictResult = 0.0;
	for (auto i = 0; i < vInput.size(); ++i)
		PredictResult += vInput[i] * m_Coefficients[i];
	return PredictResult;
}