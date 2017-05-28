#pragma once
#include <iostream>

#define _Swap_Two_Integers(vNum1, vNum2) { vNum1 ^= vNum2; vNum2 ^= vNum1; vNum1 ^= vNum2; }
#define _Log(vStr) { std::cout << vStr << std::endl; }
#define _Delete_If_Not_Empty(vP) { if (vP); delete(vP); vP = nullptr; }

namespace snail
{
	template <typename T>
	inline bool isInteger()
	{
		return typeid(T) == typeid(unsigned int) ||
			typeid(T) == typeid(int) ||
			typeid(T) == typeid(long int) ||
			typeid(T) == typeid(size_t);
	}
}