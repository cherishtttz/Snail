//***************************************************************************
//** Implementation of insert sort and its relative improvement shell sort
//** -concrete steps: refers to Sedgewick, Robert in 1986:
//**	step = pow(4, k) + 3 * pow(2, k-1) + 1
//** -complexity: O(pow(n, 4/3)) using above steps sequence
//** -Test:
//**		array size:			100000
//**		array type:			integer
//**		number of runs:		5
//**		insert sort cost:	2020 ms(average)
//**		shell sort cost:	15 ms(average)
//** -Evaluate: shell sort speed up [2020 / 15 = 135] times faster				
//***************************************************************************
#pragma once
#include <vector>

void initSteps(std::vector<int>& voSteps, unsigned int vArraySize)
{
	if (vArraySize >= 1)
	{
		voSteps.push_back(1);
		for (int k = 1; ; ++k)
		{
			int step = static_cast<int>(pow(4, k)) + 3 * static_cast<int>(pow(2, k - 1)) + 1;
			if (step >= vArraySize) return;
			voSteps.push_back(step);
		}
	}
}

template <typename T>
void shellSort(T* vArray, unsigned int vArraySize)
{
	if (vArraySize == 0) return;
	std::vector<int> Steps;
	initSteps(Steps, vArraySize);

	for (auto step = Steps.rbegin(); step != Steps.rend(); ++step)
	{
		for (int i = *step; i < vArraySize; ++i)
		{
			T ToInsert = vArray[i];
			int k = i - *step;
			for (; k >= 0 && vArray[k] > ToInsert; k -= *step)
			{
				vArray[k + *step] = vArray[k];
			}
			vArray[k + *step] = ToInsert;
		}
	}
}

template <typename T>
void insertSort(T* vArray, unsigned int vArraySize)
{
	if (vArraySize == 0) return;

	for (int i = 1; i < vArraySize; ++i)
	{
		T ToInsert = vArray[i];
		int k = i - 1;
		for (; k >= 0 && vArray[k] > ToInsert; k -= 1)
		{
			vArray[k + 1] = vArray[k];
		}
		vArray[k + 1] = ToInsert;
	}
}
