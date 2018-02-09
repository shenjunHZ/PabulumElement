/*
* Copyright (c) 
* All rights reserved.
*
* �ļ����ƣ�AX_IAddRefAble.h
* �ļ���ʶ��
* ժҪ������ָ�룬�����ڶ��߳�ָ�밲ȫ���ݡ�
*
*
*/
//////////////////////////////////////////////////////////////////////

#if !defined AX_IADDREFABLE_INCLUDE
#define AX_IADDREFABLE_INCLUDE

// ԭ���Ĵ��������ע�ͣ�/* linux�µ�atomic_tϵ�к����ƺ����ܱ�֤�߳�ͬ��������ʵ��
// ʵ��Ӧ��ʹ��atomic���㹻������������һЩ��linux�µ�atomicӦ���ܹ���֤�߳�ͬ��

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
	virtual ~AX_IAddRefAble();  // ����ֱ��delete����Ҫͨ��release()������

public:
	virtual int addRef(void);
	virtual int release(void);

protected:
	int release_without_delete();  // ��Ҫ�������࣬Ӧ���ڴ��ģʽ

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

/* linux�µ�atomic_tϵ�к����ƺ����ܱ�֤�߳�ͬ��������ʵ��
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
