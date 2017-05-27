#pragma once

namespace snail
{
	//NOTES : not working with multi-threads
	template<class T>
	class CSingleTon
	{
	public:
		static T* getInstance()
		{
			if (m_pInstance == nullptr)
			{
				m_pInstance = new T;
				atexit(destroyInstance);
			}
	
			_ASSERTE(m_pInstance != nullptr);
	
			return m_pInstance;
		}
	
	protected:
		CSingleTon() {}
		~CSingleTon() {}
	
	private:
		static T* m_pInstance;
	
		static void destroyInstance()
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	};
	
	template<class T> 
	T* CSingleTon<T>::m_pInstance = nullptr;
}