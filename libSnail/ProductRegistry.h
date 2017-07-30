#pragma once
#include <map>
#include <string>
#include <memory>
#include "SingleTon.h"
#include "snailMacro.h"
#include "snailEXPORTS.h"

namespace snail
{
	class CBaseProduct;

	typedef CBaseProduct*(*ProductCreator)();

	class SNAIL_API CProductRegistry : public CSingleTon<CProductRegistry>
	{
	public:
		~CProductRegistry() {}

		CBaseProduct* createProduct(const std::string& vSig);
		void registerCreator(const std::string& vSig, ProductCreator vCreator);

	private:
		CProductRegistry() {}
		std::map<std::string, ProductCreator> m_Registry;

		friend class CSingleTon<CProductRegistry>;
	};
}