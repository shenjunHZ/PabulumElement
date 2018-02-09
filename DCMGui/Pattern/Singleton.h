/*
 *@file   Singleton.h
 *@brief  供界面库使用的单件类
 * 
 *@author cc
 *@date   2014-07-19
 *
 */

#ifndef __DSGUI_SINGLETON_H__
#define __DSGUI_SINGLETON_H__

#include <QMutex>

namespace DSGUI
{
	/**  类名：DSSingleton
	  *  说明：单件类
	 **/
	template <class T>
	class DSSingleton
	{
	public:
		// 获取单件
		static T& Instance();

	protected:
		// 构造
		DSSingleton() {}
		// 析够
		virtual ~DSSingleton() {}
	};

	/** @fn	    inline T& DSSingleton<T>::Instance()
	 *  @brief	获取单件
	 *  @param	void
	 *  @return	T 返回单件
	 */
	template <class T>
	inline T& DSSingleton<T>::Instance()
	{
        static std::auto_ptr<T> s_ptrInstance;
		static QMutex m_mutexInstance;

		if (s_ptrInstance.get() == NULL)
		{
            // 避免创建两个
			QMutexLocker locker(&m_mutexInstance); 
            // 多线程保护
			if (s_ptrInstance.get() == NULL)
			{
				s_ptrInstance = std::auto_ptr<T>(new T);
			}
		}

		return *s_ptrInstance.get();
	}
}

#endif
