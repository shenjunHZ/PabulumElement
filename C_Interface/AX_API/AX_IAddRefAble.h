/*
* Copyright (c) 
* All rights reserved.
*
* 文件名称：AX_IAddRefAble.h
* 文件标识：
* 摘要：计数指针，适用于多线程指针安全传递。
*
*
*/
//////////////////////////////////////////////////////////////////////

#if !defined AX_IADDREFABLE_INCLUDE
#define AX_IADDREFABLE_INCLUDE

// 原来的代码有这个注释：/* linux下的atomic_t系列函数似乎不能保证线程同步，重新实现
// 实际应该使用atomic就足够，更加轻量级一些，linux下的atomic应该能够保证线程同步

#define AX_IADDREFABLE_IMPL_USE_ATOMIC
// #define AX_IADDREFABLE_IMPL_USE_MUTEX
// #define AX_IADDREFABLE_IMPL_USE_NONE

#if defined( AX_IADDREFABLE_IMPL_USE_ATOMIC )
#include "AX_API/AX_Atomic.h"
#elif defined( AX_IADDREFABLE_IMPL_USE_MUTEX )
#include "AX_API/AX_Mutex.h"
#else
#pragma message( "must use ATOMIC or MUTEX, plain int only for compare test" )
#endif

class AX_IAddRefAble
{
public:
	AX_IAddRefAble();

protected:
	virtual ~AX_IAddRefAble();  // 不能直接delete，需要通过release()来析构

public:
	virtual int addRef(void);
	virtual int release(void);

protected:
	int release_without_delete();  // 主要用于子类，应用内存池模式

private:
#if defined( AX_IADDREFABLE_IMPL_USE_ATOMIC )
	atomic_t m_ref;
#elif defined( AX_IADDREFABLE_IMPL_USE_MUTEX )
	int	m_ref;
	AX_Mutex m_mutex;
#else
	int m_ref;
#endif
};

/* linux下的atomic_t系列函数似乎不能保证线程同步，重新实现
#if defined(_WIN32) || defined (_WIN64)
	#include "winsock2i.h"
#else
	#include <pthread.h> 

	#ifdef LINUX
		#include "AX_Atomic.h"
	#else
		#include <asm/asm-armnommu/atomic.h>
	#endif
#endif

class AX_IAddRefAble
{
public:
	AX_IAddRefAble();
	virtual ~AX_IAddRefAble();

	virtual int addRef(void);
	virtual int release(void);

protected:

#if defined(_WIN32) || defined (_WIN64)
	long _ref;
#else
	atomic_t _ref;
#endif
};
*/

#include "AX_IAddRefAble.inl"

#endif // !defined AX_IADDREFABLE_INCLUDE
