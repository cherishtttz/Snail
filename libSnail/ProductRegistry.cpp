#include "ProductRegistry.h"

using namespace snail;

//****************************************************************************************************
//FUNCTION:
CBaseProduct* CProductRegistry::createProduct(const std::string& vSig)
{
	_ASSERTE(!vSig.empty() && m_Registry.find(vSig) != m_Registry.end());
	return m_Registry[vSig]();
}

//****************************************************************************************************
//FUNCTION:
void CProductRegistry::registerCreator(const std::string& vSig, ProductCreator vCreator)
{
	_ASSERTE(!vSig.empty());
	if (m_Registry.find(vSig) != m_Registry.end())
	{
		_Log("Warning : product [" + vSig + "] has already been registered.");
	}
	m_Registry[vSig] = vCreator;
}