#pragma once
#include "BaseRegression.h"
#include <map>

namespace snail
{
	namespace RegressionAnalysis
	{
		class CForwardStepwiseRegression : public IBaseLinearRegression
		{
		public:
			CForwardStepwiseRegression();
			~CForwardStepwiseRegression();

			virtual void trainV(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput) override;
			virtual double predictV(const std::vector<double>& vInput) const override;

		private:
			void __initialize(int vSingleInputSize);
			void __generateCorrelationMap(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput);
			int	 __getCurrentMostCorrelatedFeatureIndex();

			std::vector<double> m_Coefficients;
			std::vector<int> m_IndexesSet;
			std::map<double, int> m_CorrelationMap;
			std::map<double, int>::reverse_iterator m_Itr;

			template <typename TArchieve>
			void serialize(TArchieve& vAr, const unsigned int vVersion)
			{
				vAr & boost::serialization::base_object<IBaseLinearRegression>(*this);
				vAr & m_Coefficients;
				//NOTES : ignored non-sense members for prediction.
			}

			friend class boost::serialization::access;
		};
	}
}