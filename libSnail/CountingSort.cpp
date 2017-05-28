#include "CountingSort.h"
#include "Factory.h"
#include "snailCommon.h"

using namespace snail;
using namespace SortingAlgorithm;

CFactory<CCountingSort> theCreator(COUNTING_SORT);

//****************************************************************************************************
//FUNCTION:
void CCountingSort::sortIntegersSetV(std::vector<int>& voIntegersSet)
{

}