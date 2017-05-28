#pragma once
#include "BaseIntegerSorting.h"

namespace snail
{
	namespace SortingAlgorithm
	{
		class CCountingSort : public IBaseIntegerSorting
		{
		public:
			CCountingSort() {}
			~CCountingSort() {}
	
			virtual void sortIntegersSetV(std::vector<int>& voIntegersSet) override;
		};
	}
}