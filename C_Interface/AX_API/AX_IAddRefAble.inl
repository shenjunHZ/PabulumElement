/*
* Copyright (c) 
* All rights reserved.
*
* 文件名称：AX_IAddRefAble.inl
* 文件标识：
* 摘要：计数指针，适用于多线程指针安全传递。
*
*
*/

inline AX_IAddRefAble::AX_IAddRefAble()
{
#if defined( AX_IADDREFABLE_IMPL_USE_ATOMIC )
	atomic_set( &m_ref, 0 );
#elif defined( AX_IADDREFABLE_IMPL_USE_MUTEX )
	m_ref = 0;
#else
	m_ref = 0;
#endif
}

inline AX_IAddRefAble::~AX_IAddRefAble()
{
}

inline int
AX_IAddRefAble::addRef(void)
{
	int ret;
#if defined( AX_IADDREFABLE_IMPL_USE_ATOMIC )
	ret = atomic_inc( &m_ref );
#elif defined( AX_IADDREFABLE_IMPL_USE_MUTEX )
	m_mutex.acquire();
	ret = (++m_ref);
	m_mutex.release();
#else
	ret = (++m_ref);
#endif

	return ret;
}

inline int
AX_IAddRefAble::release(void)
{
	int ret;
#if defined( AX_IADDREFABLE_IMPL_USE_ATOMIC )
	ret = atomic_dec( &m_ref );
#elif defined( AX_IADDREFABLE_IMPL_USE_MUTEX )
	m_mutex.acquire();
	ret = (--m_ref);
	m_mutex.release();
#else
	ret = (--m_ref);
#endif

	//if ret < 0, the user program must check why. and prevent it.
	if (ret <= 0)
	{
		delete this;
		return 0;
	}

	return ret;
}

inline int AX_IAddRefAble::release_without_delete()
{
	int ret;
#if defined( AX_IADDREFABLE_IMPL_USE_ATOMIC )
	ret = atomic_dec( &m_ref );
#elif defined( AX_IADDREFABLE_IMPL_USE_MUTEX )
	m_mutex.acquire();
	ret = (--m_ref);
	m_mutex.release();
#else
	ret = (--m_ref);
#endif

	return ret;
}

/* linux下的atomic_t系列函数似乎不能保证线程同步，重新实现
inline AX_IAddRefAble::AX_IAddRefAble()
{
#if defined(_WIN32) || defined (_WIN64)
	_ref = 0;
#else
	_ref.counter = 0;
#endif
}

inline AX_IAddRefAble::~AX_IAddRefAble()
{

}

inline int
AX_IAddRefAble::addRef(void)
{
#if defined(_WIN32) || defined (_WIN64)
	return InterlockedIncrement(&_ref);
#else
	return atomic_inc_return(&_ref);
#endif
}

inline int
AX_IAddRefAble::release(void)
{
#if defined(_WIN32) || defined (_WIN64)
	if (InterlockedDecrement(&_ref) <= 0)
	{
		delete this;
		return 0;
	}

	return _ref;
#else
	if(atomic_dec_return(&_ref) <= 0)
	{
		delete this;
		return 0;
	}

	return _ref.counter;
#endif
}
*/

