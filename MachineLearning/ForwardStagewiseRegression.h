#pragma once
#include "BaseRegression.h"

namespace machineLearning
{
	namespace RegressionAnalysis
	{
		class CForwardStagewiseRegression : public IBaseLinearRegression
		{
		public:
			CForwardStagewiseRegression();
			~CForwardStagewiseRegression();

			virtual void trainV(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput) override;
			virtual double predictV(const std::vector<double>& vInput) const override;

		private:
			std::pair<int, double> __findCorrelatedMostFeatureIndex(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput);
			double __calculateCurrentRSS(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput);
			double __sign(double vNum);
			void __updateOutput(const std::vector<std::vector<double>>& vInput, int vIndex, double vStageSize, std::vector<double>& vOutput);

			std::vector<double> m_Coefficients;
			double m_StageStepSize = 0.1;
			int m_MaxIter = INT_MAX - 1;
			double m_Threshold = 0.01; //NOTES : for quicker to converge, set threshold a bigger value, may be local optimum
			double m_RSS = 0.0;

			template <typename TArchieve>
			void serialize(TArchieve& vAr, const unsigned int vVersion)
			{
				vAr & boost::serialization::base_object<IBaseLinearRegression>(*this);
				vAr & m_Coefficients;
				//NOTES : ignored non-sense members for prediction
			}

			friend class boost::serialization::access;
		};
	}
}