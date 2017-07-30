#pragma once
#include <vector>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>
#include "BaseProduct.h"

namespace machineLearning
{
	namespace RegressionAnalysis
	{
		class IBaseLinearRegression : public snail::CBaseProduct
		{
		public:
			virtual ~IBaseLinearRegression() {}

			virtual void trainV(const std::vector<std::vector<double>>& vInput, const std::vector<double>& vOutput) = 0;
			virtual double predictV(const std::vector<double>& vInput) const = 0;

		protected:
			IBaseLinearRegression() {};

		private:
			template <typename TArchieve>
			void serialize(TArchieve& vAr, const unsigned int vVersion)
			{

			}

			friend class boost::serialization::access;
		};
		BOOST_SERIALIZATION_ASSUME_ABSTRACT(IBaseLinearRegression);
	}
}