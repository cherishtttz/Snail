#pragma once
#include "BaseRegression.h"

namespace snailRegression
{
	class CAverageOutputRegression : public IBaseLinearRegression
	{
	public:
		CAverageOutputRegression();
		~CAverageOutputRegression();

		virtual void trainV(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput) override;
		virtual double predictV(const std::vector<double>& vInput) const override;

	private:
		unsigned int m_SingleInputSize = 0;
		double m_PredictValue = 0.0;

		template <typename TArchieve>
		void serialize(TArchieve& vAr, const unsigned int vVersion)
		{
			vAr & boost::serialization::base_object<IBaseLinearRegression>(*this);
			vAr & m_SingleInputSize;
			vAr & m_PredictValue;
		}

		friend class boost::serialization::access;
	};
}