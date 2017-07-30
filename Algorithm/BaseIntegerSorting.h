#pragma once
#include "BaseProduct.h"
#include <vector>

namespace algorithm
{
	namespace SortingAlgorithm
	{
		class IBaseIntegerSorting : public snail::CBaseProduct
		{
		public:
			virtual ~IBaseIntegerSorting() {}
	
			virtual void sortIntegersSetV(std::vector<int>& voIntegersSet) = 0;
	
		protected:
			IBaseIntegerSorting() {}
		};
	}
}