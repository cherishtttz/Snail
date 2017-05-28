#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include "../libSnail/snailInterface.h"
#include "../libSnail/snailCommon.h"

//FUNCTION: detect the memory leak in DEBUG mode
void installMemoryLeakDetector()
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	//_CRTDBG_LEAK_CHECK_DF: Perform automatic leak checking at program exit through a call to _CrtDumpMemoryLeaks and generate an error 
	//report if the application failed to free all the memory it allocated. OFF: Do not automatically perform leak checking at program exit.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//the following statement is used to trigger a breakpoint when memory leak happens
	//comment it out if there is no memory leak report;
	//_crtBreakAlloc = 30372;
#endif
}

//****************************************************************************************************
//FUNCTION:
bool isIntegersSetInIncreaseOrder(const std::vector<int>& vSet)
{
	if (vSet.size() < 2) return true;
	for (auto i = 1; i < vSet.size(); ++i)
		if (vSet[i] < vSet[i - 1]) return false;
	return true;
}

void main()
{
	installMemoryLeakDetector();

	try
	{
		std::vector<int> IntegersSet{ 2,1,45,23,7,100 };
		const std::string SortingAlgorithm = snail::SortingAlgorithm::COUNTING_SORT;
		snail::SortingAlgorithm::snailSortIntegersSet(IntegersSet, SortingAlgorithm);
		//std::sort(IntegersSet.begin(), IntegersSet.end());
		std::cout << "Is [" << SortingAlgorithm << "] works : " << isIntegersSetInIncreaseOrder(IntegersSet) << "\n\n";
	}
	catch (const std::exception&)
	{
		_Log("The program is terminated due to unexpected error.");
	}

	system("pause");
}