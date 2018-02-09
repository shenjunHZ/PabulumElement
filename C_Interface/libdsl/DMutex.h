/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2011-09
 *
 * DMutex.h : ����������
 */

#ifndef INCLUDED_LIBDSL_DMUTEX_H
#define INCLUDED_LIBDSL_DMUTEX_H

#include <libdsl/dslbase.h>

// BEGIN -- ��ƽ̨��صĶ��壬ʹ���߿�������

// TODO : win32��critical section�ǵݹ��������ܸġ�
// �����ǲ��Ƽ�ʹ�õݹ���������linux���Ƿ�֧�ֵݹ�������windows��Ҫ��Ҫ��һ���ݹ��жϣ���

#ifdef _WIN32
#define	DSL_MUTEX_CS(hcs)				CRITICAL_SECTION	hcs[1];
#define	DSL_MUTEX_csConstruct(hcs)	(InitializeCriticalSection(hcs), TRUE)
#define	DSL_MUTEX_csDestruct(hcs)		DeleteCriticalSection(hcs)
// #define	DSL_MUTEX_csTryEnter(hcs)		TryEnterCriticalSection(hcs)
#define	DSL_MUTEX_csEnter(hcs)		EnterCriticalSection(hcs)
#define	DSL_MUTEX_csLeave(hcs)		LeaveCriticalSection(hcs)

#else

#include <pthread.h>

#define	DSL_MUTEX_CS(hcs)					pthread_mutex_t	hcs[1];
#ifdef MAC
#define DSL_MUTEX_csConstruct( hcs ) \
	do { \
	pthread_mutexattr_t attr;  \
	pthread_mutexattr_init( &attr );  \
	/* ���� recursive */ \
	pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE);  \
	pthread_mutex_init( hcs, &attr ); \
	pthread_mutexattr_destroy( &attr ); \
	} while( 0 )
#else
#define DSL_MUTEX_csConstruct( hcs ) \
	do { \
	pthread_mutexattr_t attr;  \
	pthread_mutexattr_init( &attr );  \
	/* ���� recursive */ \
	pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE_NP );  \
	pthread_mutex_init( hcs, &attr ); \
	pthread_mutexattr_destroy( &attr ); \
	} while( 0 )
#endif


#define	DSL_MUTEX_csDestruct(hcs)				pthread_mutex_destroy( hcs )
// #define	DSL_MUTEX_csTryEnter(hcs)				(0 == pthread_mutex_trylock(hcs))
#define	DSL_MUTEX_csEnter(hcs)				pthread_mutex_lock(hcs)
#define	DSL_MUTEX_csLeave(hcs)				pthread_mutex_unlock(hcs)

#endif

// END -- ��ƽ̨��صĶ��壬ʹ���߿�������

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

// <1> �߳�������
class DEvent;

class LIBDSL_API DMutex
{
public:
	DMutex(void);
	~DMutex(void);

	void Lock();
	void Unlock();

private: // ���ɿ���
	DMutex( const DMutex & mtx );
	DMutex & operator = ( const DMutex & mtx );

private:
	friend class DEvent;
	DSL_MUTEX_CS(m_csLock);
};

/*	�����������ڣ����������������ʹ��
 *	DMutexGuard guard(DMutex);
 */
class LIBDSL_API DMutexGuard
{
public:
	DMutexGuard(DMutex *);
	~DMutexGuard();

private: // ���ɿ���
	DMutexGuard( const DMutexGuard & mtx );
	DMutexGuard & operator = ( const DMutexGuard & mtx );

private:
	DMutex *m_pDMutex;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif //INCLUDED_LIBDSL_DMUTEX_H

