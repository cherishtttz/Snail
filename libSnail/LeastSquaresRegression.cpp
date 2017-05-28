#include "LeastSquaresRegression.h"
#include <Eigen/Dense>
#include <numeric>
#include "Factory.h"
#include "snailCommon.h"

using namespace snail;
using namespace snail::RegressionAnalysis;

CFactory<CLeastSquaresRegression> theCreator(LEAST_SQUARES_REGRESSION);

BOOST_CLASS_EXPORT_GUID(CLeastSquaresRegression, "CLeastSquaresRegression");

CLeastSquaresRegression::CLeastSquaresRegression()
{}

CLeastSquaresRegression::~CLeastSquaresRegression()
{}

//****************************************************************************************************
//FUNCTION:
void CLeastSquaresRegression::trainV(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput)
{
	_ASSERTE(!vInput.empty() && vInput.size() == vOutput.size());

	int NumInputs = vInput[0].size();
	int NumSamples = vInput.size();
	//Ax = B
	Eigen::MatrixXd Mat(NumInputs + 1, NumInputs + 1);
	for (auto Row = 0; Row < NumInputs; ++Row)
	{
		//(0,0) -> (n-1,n-1)
		for (auto Col = 0; Col < NumInputs; ++Col)
		{
			double Sum = 0.0;
			for (auto i = 0; i < NumSamples; ++i)
				Sum += vInput[i][Row] * vInput[i][Col];
			Mat(Row, Col) = Sum;
		}
		//(n,0)->(n,n-1)
		double Sum = 0.0;
		for (auto i = 0; i < NumSamples; ++i)
			Sum += vInput[i][Row];
		Mat(NumInputs, Row) = Sum;
	}
	//(0,n)->(n,n)
	for (auto Row = 0; Row < NumInputs + 1; ++Row)
		Mat(Row, NumInputs) = NumInputs;

	Eigen::VectorXd b(NumInputs + 1);
	//(0,n+1)->(n-1,n+1)
	for (auto Row = 0; Row < NumInputs; ++Row)
	{
		double Sum = 0;
		for (auto i = 0; i < NumSamples; ++i)
			Sum += vOutput[i] * vInput[i][Row];
		b(Row) = Sum;
	}
	//(n,n+1)
	b(NumInputs) = std::accumulate(vOutput.begin(), vOutput.end(), 0.0);

	Eigen::VectorXd LinearParameter = (Mat.transpose() * Mat).ldlt().solve(Mat.transpose() * b);
	m_Coefficients.clear();
	for (auto i = 0; i < NumInputs; ++i)
		m_Coefficients.push_back(LinearParameter(i));
	m_Bias = LinearParameter[NumInputs];
}

//****************************************************************************************************
//FUNCTION:
double CLeastSquaresRegression::predictV(const std::vector<double>& vInput) const
{
	_ASSERTE(vInput.size() == m_Coefficients.size());

	double PredictResult = 0.0;
	for (auto Index = 0; Index < vInput.size(); ++Index)
		PredictResult += vInput[Index] * m_Coefficients[Index];
	return PredictResult + m_Bias;
}