#pragma once
#include "BaseProduct.h"
#include "ProductRegistry.h"

namespace snail
{
	template <typename TProduct>
	class CFactory
	{
	public:
		CFactory(const std::string& vProductSig)
		{
			CProductRegistry::getInstance()->registerCreator(vProductSig, &CFactory<TProduct>::__productCreationFunc);
		}
		~CFactory() {}

	private:
		static CBaseProduct* __productCreationFunc()
		{
			return reinterpret_cast<CBaseProduct*>(new TProduct);
		}
	};
}