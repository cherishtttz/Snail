#pragma once
#include "BaseIntegerSorting.h"

namespace snail
{
	namespace SortingAlgorithm
	{
		class CBucketSort : public IBaseIntegerSorting
		{
		public:
			CBucketSort() {}
			~CBucketSort() {}
	
			virtual void sortIntegersSetV(std::vector<int>& voIntegersSet) override;
		};
	}
}