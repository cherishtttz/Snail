#include "QuickSort.h"
#include "Factory.h"
#include "AlgorithmCommon.h"
#include "snailInterface.h"

using namespace algorithm::SortingAlgorithm;

snail::CFactory<CQuickSort> theCreator(QUICK_SORT);

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
	if (snail::isInBetween<int>(vRangeTo, 0, voIntegersSet.size()) && snail::isInBetween<int>(vRangeFrom, 0, vRangeTo))
	{
		if (vRangeTo - vRangeFrom <= 1)
		{
			if (voIntegersSet[vRangeFrom] > voIntegersSet[vRangeTo])
				snail::swapTwoIntegers(voIntegersSet[vRangeFrom], voIntegersSet[vRangeTo]);
			return;
		}
		int Pivot = voIntegersSet[vRangeTo];
		int WallIndex = vRangeFrom - 1;
		for (auto i = vRangeFrom; i < vRangeTo; ++i)
		{
			if (voIntegersSet[i] < Pivot) snail::swapTwoIntegers(voIntegersSet[i], voIntegersSet[++WallIndex]);
		}
		snail::swapTwoIntegers(voIntegersSet[vRangeTo], voIntegersSet[++WallIndex]);

		__sortIntegersSet(vRangeFrom, WallIndex - 1, voIntegersSet);
		__sortIntegersSet(WallIndex + 1, vRangeTo, voIntegersSet);
	}
}