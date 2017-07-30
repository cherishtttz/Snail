#pragma 
#include "BaseIntegerSorting.h"

namespace algorithm
{
	namespace SortingAlgorithm
	{
		class CQuickSort : public IBaseIntegerSorting
		{
		public:
			CQuickSort();
			~CQuickSort();

			virtual void sortIntegersSetV(std::vector<int>& voIntegersSet) override;

		private:
			void __sortIntegersSet(const int vRangeFrom, const int vRangeTo, std::vector<int>& voIntegersSet);
		};
	}
}