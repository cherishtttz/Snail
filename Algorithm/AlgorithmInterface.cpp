#include "AlgorithmInterface.h"
#include <memory>
#include "QuickSort.h"
#include "snailInterface.h"

using namespace algorithm;

//****************************************************************************************************
//FUNCTION:
void SortingAlgorithm::snailSortIntegersSet(std::vector<int>& voIntegersSet, const std::string& vAlgorithmSig)
{
	_ASSERTE(!voIntegersSet.empty() && !vAlgorithmSig.empty());
	std::shared_ptr<IBaseIntegerSorting> pSortAlgorithm = std::shared_ptr<IBaseIntegerSorting>(dynamic_cast<IBaseIntegerSorting*>(snail::snailCreateProduct(vAlgorithmSig)));
	pSortAlgorithm->sortIntegersSetV(voIntegersSet);
}