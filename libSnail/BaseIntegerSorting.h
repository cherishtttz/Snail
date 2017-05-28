#pragma once
#include "BaseProduct.h"
#include <vector>

namespace snail
{
	namespace SortingAlgorithm
	{
		class IBaseIntegerSorting : public CBaseProduct
		{
		public:
			virtual ~IBaseIntegerSorting() {}
	
			virtual void sortIntegersSetV(std::vector<int>& voIntegersSet) = 0;
	
		protected:
			IBaseIntegerSorting() {}
		};
	}
}