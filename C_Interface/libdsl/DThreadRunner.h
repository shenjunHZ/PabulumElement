/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2011-09
 *
 * DThreadRunner.h : �߳����ж����Heartbeat����
 */

#ifndef	INCLUDED_LIBDSL_DTHREADRUNNER_H
#define	INCLUDED_LIBDSL_DTHREADRUNNER_H

#include <libdsl/DMutex.h>
#include <libdsl/DRefObj.h>

#include <deque>
#include <map>

// BEGIN -- ��ƽ̨��صĶ��壬ʹ���߿�������
#ifdef _WIN32

#include <process.h>

#define DSL_THREAD_EXIT_CODE_TYPE unsigned int
#define DSL_THREAD_ENTRY __stdcall
#define DSL_HTHREAD		HANDLE

#define DSL_SLEEP_MS( x )	::Sleep( x )

#define DSL_THREAD_START( thread, start_func, param) \
	( (thread = (DSL_HTHREAD)_beginthreadex(NULL, 0, start_func, param, 0, NULL)) != 0 )

#define DSL_THREAD_END( code )	_endthreadex( code )
#define DSL_THREAD_WAIT_CLOSE( thread ) \
	do { \
		WaitForSingleObject( thread, INFINITE ); \
		CloseHandle( thread ); \
	} while( 0 )

#else

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
// #include <sys/prctl.h>

#define DSL_THREAD_EXIT_CODE_TYPE void *
#define DSL_THREAD_ENTRY 
#define DSL_HTHREAD		pthread_t

#define DSL_SLEEP_MS( x )	\
	do { \
		struct timeval tv; \
		tv.tv_sec = (x) / 1000; \
		tv.tv_usec = ( (x) % 1000 ) * 1000; \
		/* TODO : will EINTR affect ? */ \
		select( 0, NULL, NULL, NULL, &tv ); \
	} while( 0 )

#define DSL_THREAD_START( thread, start_func, param) \
	( pthread_create( &thread, NULL, start_func, param) == 0 )

#define DSL_THREAD_END( code )
#define DSL_THREAD_WAIT_CLOSE( thread ) \
	do { \
		void * tmp = NULL; \
		pthread_join( thread, &tmp ); \
	} while( 0 )

#endif

// END -- ��ƽ̨��صĶ��壬ʹ���߿�������


BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

// <1> �̺߳�Heartbeat���ж���

// DThread �� DRunner ��װ���̣߳�ÿ�������װһ���̣߳�
// DThread ʹ�ü̳У�����ͨ���̳У�����run����heartbeatʵ���̺߳���
// DRunner ʹ�����ί�У����̺߳�����Ϊ����ί�и�������

// �߳��˳�ʱ������ Stop �������ⲿ���ã��������߳��ڲ����á�
// ���⼴ʹ�߳������˳����ⲿҲҪ���� Stop ���Ա�����߳���Դ��

// run �� heartbeat �������߳����з�ʽ
// run ֻ����һ�Σ� run �����˳�ʱ���߳̾��˳�
// heartbeat �ᱻ���ж�Σ���һ��ѭ���ﲻͣ���ã�����������������У�����0��sleep 10ms�����ظ�������ֹ�߳�

// TODO : �Ƿ�ϲ�run��heartbeat��Ϊrunloop����run����ֻ����һ�ξͷ��ظ�����heartbeat����

// TODO : �Ƿ�֧�������̣߳�

// TODO : ����priority����

enum dsl_thread_state_e {
	DSL_THREAD_STATE_UNKNOWN = 0,  // ��Ӧ�ó��ֵ�״̬
	DSL_THREAD_STATE_IDLE,         // �߳�δ���������Ѿ�ֹͣ
	DSL_THREAD_STATE_RUNNING,      // �߳���������
	DSL_THREAD_STATE_STOPPING,     // �̵߳ȴ��˳����ȴ�������Դ�����պ󷵻�IDLE״̬��
};

class LIBDSL_API DThread
{
public:
	DThread();
	virtual ~DThread();

	// �����߳�
	virtual int Start();
	// ֪ͨ�߳��˳���
	virtual int SignalStop();
	// ֹͣ�̣߳����ҵȴ��߳��˳�
	virtual int Stop();

	static void SleepMs( int ms );

	inline bool IsRunning() { return m_state == DSL_THREAD_STATE_RUNNING; }

	inline bool IsStopping() { return m_state == DSL_THREAD_STATE_STOPPING; }
	inline bool IsIdle() { return m_state == DSL_THREAD_STATE_IDLE; }
	void SetThreadName(const char * name); // �����߳����� ������Startǰ����

protected:
	virtual int run()
	{
		while( IsRunning() ) {
			int ret = heartbeat();
			if( ret < 0 ) {
				m_state = DSL_THREAD_STATE_STOPPING;
				return ret;
			}
			if( ret == 0 )
				SleepMs( 10 );
		}
		return 0;
	}
	virtual int heartbeat() { return 0; }

	static DSL_THREAD_EXIT_CODE_TYPE DSL_THREAD_ENTRY s_ThreadProc( void * param );

	void SetThreadNameInside(const char * name);

protected:
	DSL_HTHREAD m_thread;
	volatile dsl_thread_state_e m_state;
	char	m_threadName[16]; //
};


// ��ʹ��DSL_RUNNER_TYPE_ONCE���͵�runnerʱ����Ҫ���̺߳����ж��ڼ���߳��Ƿ���Ҫ�˳�������ʹ������;��֪ͨ

enum dsl_runner_type_e {
	DSL_RUNNER_TYPE_UNKNOWN = 0,
	DSL_RUNNER_TYPE_ONCE,
	DSL_RUNNER_TYPE_RUN = DSL_RUNNER_TYPE_ONCE,
	DSL_RUNNER_TYPE_REPEAT,
	DSL_RUNNER_TYPE_HEARTBEAT = DSL_RUNNER_TYPE_REPEAT,
};

template< class T >
class DRunner : public DThread
{
public:
	typedef int ( T::* func_type_t )( DThread * th );
	DRunner( func_type_t func = NULL, T * obj = NULL, dsl_runner_type_e type = DSL_RUNNER_TYPE_ONCE )
		: m_func( func ), m_obj( obj ), m_type( type ) { }

	inline int SetRunner( func_type_t func, T * obj, dsl_runner_type_e type = DSL_RUNNER_TYPE_ONCE )
	{
		m_func = func;
		m_obj = obj;
		m_type = type;
		return 0;
	}

protected:
	virtual inline int run()
	{
		if( m_func == NULL )
			return -1;

		if( m_type == DSL_RUNNER_TYPE_ONCE ) {
			return (m_obj->*m_func)( this );
		}
		else if( m_type == DSL_RUNNER_TYPE_REPEAT ) {
			return DThread::run();
		}
		return -1;
	}
	virtual inline int heartbeat() { return (m_obj->*m_func)( this ); }

protected:
	int reserved;
	func_type_t m_func;
	T * m_obj;
	dsl_runner_type_e m_type;
};

typedef int ( * dsl_runner_func_t )( void * arg, void * th );  // th ʵ����DThread����
extern "C" int dsl_runner_is_running( void * th );  // �̺߳����п��Ե��ô˺������ж��Ƿ񻹿��Լ��������̡߳�

template<>
class LIBDSL_API DRunner<void> : public DThread
{
public:
	DRunner( dsl_runner_func_t func = NULL, void * arg = NULL, dsl_runner_type_e type = DSL_RUNNER_TYPE_ONCE )
		: m_func( func ), m_arg( arg ), m_type( type ) { }

	inline int SetRunner( dsl_runner_func_t func, void * arg = NULL, dsl_runner_type_e type = DSL_RUNNER_TYPE_ONCE )
	{
		m_func = func;
		m_arg = arg;
		m_type = type;
		return 0;
	}

protected:
	virtual int run()
	{
		if( m_func == NULL )
			return -1;

		if( m_type == DSL_RUNNER_TYPE_ONCE ) {
			return m_func( m_arg, this );
		}
		else if( m_type == DSL_RUNNER_TYPE_REPEAT ) {
			return DThread::run();
		}
		return -1;
	}
	virtual int heartbeat(); // { return m_func( m_arg ); }

protected:
	dsl_runner_func_t m_func;
	void * m_arg;
	dsl_runner_type_e m_type;
};

// template<> �ػ�ʱ����Ҫд���
inline int DRunner<void>::heartbeat()
{
	return m_func( m_arg, this );
}

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBDSL_DTHREADRUNNER_H
