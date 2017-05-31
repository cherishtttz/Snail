#include <memory>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "../libSnail/snailInterface.h"
#include "../libSnail/snailMacro.h"
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
	//_crtBreakAlloc = 278;
#endif
}

int g_NumOfSamples = 10, g_NumOfInput = 10;
double g_Min = 0.0, g_Max = 10.0;

//****************************************************************************************************
//FUNCTION:
void generateTrainingSet(std::vector<std::vector<double>>& voInput, std::vector<double>& voOutput)
{
	voInput.resize(g_NumOfSamples);
	voOutput.resize(g_NumOfSamples);
	for (auto i = 0; i < g_NumOfSamples; ++i)
	{
		voInput[i].resize(g_NumOfInput);
		for (auto &Itr : voInput[i]) Itr = snail::generateRandomFloatNumber(g_Min, g_Max);
		voOutput[i] = snail::generateRandomFloatNumber(g_Min, g_Max);
	}
}

//****************************************************************************************************
//FUNCTION:
void testLinearRegressionModel(std::vector<std::vector<double>>& vInput, std::vector<double>& vOutput, const std::string& vSig)
{
	clock_t TrainBegin = clock();
	snail::RegressionAnalysis::IBaseLinearRegression* pLinearRegression = snail::RegressionAnalysis::snailTrainLinearRegressionModel(vInput, vOutput, vSig);
	clock_t TrainEnd = clock();
	std::cout << "Training regression model [" << vSig << "] complete in " << (TrainEnd - TrainBegin) / CLOCKS_PER_SEC << " seconds.\n";
	snail::RegressionAnalysis::evaluateLinearRegressionModel(vInput, vOutput, pLinearRegression);
	_Delete_If_Not_Empty(pLinearRegression);
}

void main()
{
	installMemoryLeakDetector();
	try
	{
		std::vector<std::vector<double>> Input;
		std::vector<double> Output;
		generateTrainingSet(Input, Output);
		testLinearRegressionModel(Input, Output, snail::RegressionAnalysis::FORWARD_STAGEWISE_REGRESSION);
		testLinearRegressionModel(Input, Output, snail::RegressionAnalysis::AVERAGE_OUTPUT_REGRESSION);
		testLinearRegressionModel(Input, Output, snail::RegressionAnalysis::LEAST_SQUARES_REGRESSION);
		testLinearRegressionModel(Input, Output, snail::RegressionAnalysis::FORWARD_STEPWISE_REGRESSION);
	}
	catch (const std::exception&)
	{
		_Log("The program is terminated due to unexpected error.");
	}

	system("pause");
}