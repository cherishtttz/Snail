#pragma once
#include "BaseRegression.h"

namespace snailRegression
{
	class CLeastSquaresRegression : public IBaseLinearRegression
	{
	public:
		CLeastSquaresRegression();
		~CLeastSquaresRegression();

		virtual void trainV(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput) override;
		virtual double predictV(const std::vector<double>& vInput) const override;

	private:
		std::vector<double> m_Coefficients;
		double m_Bias = 0.0;

		template <typename TArchieve>
		void serialize(TArchieve& vAr, const unsigned int vVersion)
		{
			vAr & boost::serialization::base_object<IBaseLinearRegression>(*this);
			vAr & m_Coefficients;
			vAr & m_Bias;
		}

		friend class boost::serialization::access;
	};
}