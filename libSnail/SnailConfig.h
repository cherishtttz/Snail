#pragma once
#include <unordered_map>
#include <string>
#include <typeinfo>
#include <boost/any.hpp>

namespace snail
{
	enum EAttributeType
	{
		TYPE_BOOL = 0,
		TYPE_CHAR,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_DOUBLE,
		TYPE_STRING
	};

	class CSnailConfig
	{
	public:
		CSnailConfig();
		virtual ~CSnailConfig();

		template <typename T>
		T getAttribute(const std::string& vAttributeSig)
		{
			_ASSERTE(!vAttributeSig.empty());
			if (m_AttributeSigTypeRegistryMap.count(vAttributeSig) == 0)
			{
				_Log("Attribute [" + vAttributeSig + "] not registered, please use if after registering.\n");
				_ASSERTE(false);
			}
			if (m_AttributeMap.count(vAttributeSig) == 0)
			{
				_Log("");
				_ASSERTE(false);
			}
			if (typeid(T).name() != m_AttributeMap[vAttributeSig].type().name())
			{
				_Log("Attribute type does not match pre-registered type : " + m_AttributeMap[vAttributeSig].type().name() + ".\n");
				_ASSERTE(false);
			}

			return boost::any_cast<T>(m_AttributeMap[vAttributeSig]);
		}

	protected:
		virtual void _registerAttributeTypeV(const std::string& vAttributeSig, EAttributeType vAttributeType) {}

	private:
		std::unordered_map<std::string, EAttributeType> m_AttributeSigTypeRegistryMap;
		std::unordered_map<std::string, boost::any> m_AttributeMap;
	};
}