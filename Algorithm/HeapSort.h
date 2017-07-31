#pragma once

template <typename T>
void swap(T& v1, T& v2)
{
	T Temp = v1;
	v1 = v2;
	v2 = Temp;
}

template <typename T>
void heapify(T* vArray, unsigned int vArraySize)
{
	_ASSERTE(vArray);
	if (vArraySize <= 1) return;

	int LastParent = (vArraySize - 1) / 2;
	while (LastParent >= 0)
	{
		siftDown(vArray, LastParent, vArraySize);
		--LastParent;
	}
}

template <typename T>
void siftDown(T* vArray, unsigned int vStart, unsigned int vArraySize)
{
	_ASSERTE(vArray);
	if (vArraySize <= 1 || vStart >= vArraySize) return;
	int MyLeftChildIndex = 2 * vStart + 1, MyRightChildIndex = 2 * vStart + 2;
	if (MyLeftChildIndex < vArraySize && vArray[MyLeftChildIndex] > vArray[vStart])
	{
		swap(vArray[MyLeftChildIndex], vArray[vStart]);
		siftDown(vArray, MyLeftChildIndex, vArraySize);
	}
	if (MyRightChildIndex < vArraySize && vArray[MyRightChildIndex] > vArray[vStart])
	{
		swap(vArray[MyRightChildIndex], vArray[vStart]);
		siftDown(vArray, MyRightChildIndex, vArraySize);
	}
}

template <typename T>
void heapSort(T* vArray, unsigned int vSize)
{
	_ASSERTE(vArray);
	if (vSize <= 1) return;

	//** Initialize: natural complete binary tree, need to know, for element with index = i
	//** - parent index : floor((i-1)/2)
	//** - left child index : 2 * i + 1
	//** - right child index : 2 * i + 2

	//** 1st step: heapify()
	heapify(vArray, vSize);

	//** 2nd step: 
	//** 1. swap first and last element in unsorted range
	//** 2. sift down to adjust heap
	//** 3. repeat 1,2 until vSize = 1
	while (vSize > 1)
	{
		swap(vArray[0], vArray[vSize - 1]);
		--vSize;
		siftDown(vArray, 0, vSize);
	}
}
