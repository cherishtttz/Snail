#pragma once
#include "snailEXPORTS.h"
#include <string>
#include "ProductRegistry.h"

namespace snail
{
	SNAIL_DLL_EXPORT int		generateRandomIntegerNumber(const int vRangeFrom, const int vRangeTo);
	SNAIL_DLL_EXPORT double		generateRandomFloatNumber(const double vRangeFrom, const double vRangeTo);
	SNAIL_DLL_EXPORT CBaseProduct* snailCreateProduct(const std::string& vSig);
}