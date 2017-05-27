#pragma once
#include <map>
#include <string>
#include "SingleTon.h"
#include "snailMacro.h"
#include "snailEXPORTS.h"

namespace snail
{
	class CBaseProduct;

	typedef CBaseProduct*(*ProductCreator)();

	class SNAIL_DLL_EXPORT CProductRegistry : public CSingleTon<CProductRegistry>
	{
	public:
		CProductRegistry() {}
		~CProductRegistry() {}

		CBaseProduct* createProduct(const std::string& vSig);
		void registerCreator(const std::string& vSig, ProductCreator vCreator);

	private:
		std::map<std::string, ProductCreator> m_Registry;
	};
}