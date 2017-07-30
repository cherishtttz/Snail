#include <memory>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "MachineLearningInterface.h"
#include "MachineLearningCommon.h"
#include "snailInterface.h"

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
	//_crtBreakAlloc = 278;
#endif
}

void main()
{
	installMemoryLeakDetector();
	try
	{
		std::vector<std::vector<double>> DataTable;
		if (snail::snailReadDatasetFromFile("../Dataset/Iris_no_header_no_lable.csv", DataTable, false))
		{
			std::vector<int> FeatureIndexSet{ 0,1,2,3 };
			std::vector<machineLearning::ClusteringAlgorithm::SCluster> Clusters;
			machineLearning::ClusteringAlgorithm::clusterDataIntoGroups(DataTable, FeatureIndexSet, 3, machineLearning::ClusteringAlgorithm::K_MEANS, Clusters);
			//NOTES : 对每一个DataTable中的数据进行测试，在所有聚类中，离某聚类近即属于该类
			{
				//Cluster Summary : 结果稳定并且和书中 experiments 的结果几乎一样
				std::cout << "Number of clusters : " << Clusters.size() << std::endl;
				for (unsigned int i = 0; i < Clusters.size(); ++i)
					std::cout << "Size of Cluster " << i << " : " << Clusters[i].getSizeOfCluster() << std::endl;
			}
		}
	}
	catch (const std::exception&)
	{
		_Log("Error : The program is terminated due to unexpected error.");
	}

	system("pause");
}