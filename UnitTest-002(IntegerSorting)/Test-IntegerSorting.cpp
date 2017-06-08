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
		int SizeVec = 10000;
		std::vector<int> IntegersSet;
		for (auto Itr = 0; Itr < SizeVec; ++Itr)
		{
			IntegersSet.clear();
			for (auto i = 0; i < SizeVec; ++i) IntegersSet.push_back(snail::generateRandomIntegerNumber(0, 100000));
			const std::string SortingAlgorithm = snail::SortingAlgorithm::QUICK_SORT;
			snail::SortingAlgorithm::snailSortIntegersSet(IntegersSet, SortingAlgorithm);
			if (!isIntegersSetInIncreaseOrder(IntegersSet))
			{
				std::cout << "Test failed using [" + SortingAlgorithm + "].\n\n";
				break;
			}
			if (Itr == SizeVec - 1)
				std::cout << "Test passed using [" + SortingAlgorithm + "].\n\n";
		}
	}
	catch (const std::exception&)
	{
		_Log("The program is terminated due to unexpected error.");
	}

	system("pause");
}