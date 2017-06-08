#include "QuickSort.h"
#include "Factory.h"
#include "snailCommon.h"
#include "snailInterface.h"

using namespace snail;
using namespace snail::SortingAlgorithm;

CFactory<CQuickSort> theCreator(QUICK_SORT);

CQuickSort::CQuickSort()
{
}

CQuickSort::~CQuickSort()
{
}

//*********************************************************************
//FUNCTION:
void CQuickSort::sortIntegersSetV(std::vector<int>& voIntegersSet)
{
	if (voIntegersSet.size() <= 1) return;
	__sortIntegersSet(0, voIntegersSet.size() - 1, voIntegersSet);
}

//*********************************************************************
//FUNCTION:
void CQuickSort::__sortIntegersSet(const int vRangeFrom, const int vRangeTo, std::vector<int>& voIntegersSet)
{
	if (isInBetween<int>(vRangeTo, 0, voIntegersSet.size()) && isInBetween<int>(vRangeFrom, 0, vRangeTo))
	{
		if (vRangeTo - vRangeFrom <= 1)
		{
			if (voIntegersSet[vRangeFrom] > voIntegersSet[vRangeTo])
				swapTwoIntegers(voIntegersSet[vRangeFrom], voIntegersSet[vRangeTo]);
			return;
		}
		int Pivot = voIntegersSet[vRangeTo];
		int WallIndex = vRangeFrom - 1;
		for (auto i = vRangeFrom; i < vRangeTo; ++i)
		{
			if (voIntegersSet[i] < Pivot) swapTwoIntegers(voIntegersSet[i], voIntegersSet[++WallIndex]);
		}
		swapTwoIntegers(voIntegersSet[vRangeTo], voIntegersSet[++WallIndex]);

		__sortIntegersSet(vRangeFrom, WallIndex - 1, voIntegersSet);
		__sortIntegersSet(WallIndex + 1, vRangeTo, voIntegersSet);
	}
}