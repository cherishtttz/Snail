#pragma once
#include "BaseIntegerSorting.h"

namespace snail
{
	namespace SortingAlgorithm
	{
		class CRadixSort : public IBaseIntegerSorting
		{
		public:
			CRadixSort() {}
			~CRadixSort() {}
			
			virtual void sortIntegersSetV(std::vector<int>& voIntegersSet) override;
		};
	}
}