#ifndef __COMMON_MEMORYPOOL_H__
#define __COMMON_MEMORYPOOL_H__

#include "Common/CommonGlobal.h"
#include "Common/Thread/Mutex.h"
#include <boost/pool/singleton_pool.hpp>

namespace Common
{
    template <class T>
    class CMemoryAlloc
    {
    public:
        // 构造函数
        CMemoryAlloc();
        ~CMemoryAlloc();

    public:
        // 由内存池分配
        void* Malloc();

        // 由内存池释放
        void Free(void* p);

    private:
        boost::pool<> m_pool;     // 内存池
        mutable DSMutex m_mutex;  // 锁
    };

	// 构造函数
	template <class T>
	CMemoryAlloc<T>::CMemoryAlloc()
		: m_pool(sizeof(T))
	{}

	template <class T>
	CMemoryAlloc<T>::~CMemoryAlloc()
	{
	}

	// 由内存池分配
	template <class T>
	void* CMemoryAlloc<T>::Malloc()
	{
		DSMutexLock lock(m_mutex);
		return m_pool.malloc();
	}

	// 由内存池释放
	template <class T>
	void CMemoryAlloc<T>::Free(void* p)
	{
		DSMutexLock lock(m_mutex);
		m_pool.free(p);
	}

    /** @class class CMemoryPool
     * 
     *  @brief 自定义内存池
     * 
     */
    template <class T, class U = CMemoryAlloc<T> >
    class CMemoryPool
    {
    public:
        CMemoryPool()
        {}

        // 分配内存，必须使用Free进行释放
        void* Malloc();
        // 释放内存
        void Free(void* p);
    private:
        U m_allocMemery;
    };

	// 分配内存，必须使用Free进行释放
	template <class T, class U>
	void* CMemoryPool<T, U>::Malloc()
	{
		void* p = m_allocMemery.Malloc();
		if (NULL == p)
		{
			throw std::bad_alloc();
		}

		return p;
	}

	// 释放内存
	template <class T, class U>
	void CMemoryPool<T, U>::Free(void* p)
	{
		if (NULL != p)
		{
			m_allocMemery.Free(p);
		}
	}
}

#define DECLARE_MEMORYPOOL(class_type) \
    public: \
        static void* operator new(size_t) \
        { \
            return memorypool.Malloc(); \
        } \
        static void operator delete(void* p) \
        { \
            memorypool.Free(p); \
        } \
    private: \
        static Common::CMemoryPool<class_type> memorypool;

#define DEFINE_MEMORYPOOL(class_type) \
    Common::CMemoryPool<class_type> class_type::memorypool;

#endif
