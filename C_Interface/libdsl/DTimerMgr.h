/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2011-09
 *
 * DTimerMgr.h : ��ʱ������
 */

#ifndef INCLUDED_LIBDSL_DTIMERMGR_H
#define INCLUDED_LIBDSL_DTIMERMGR_H

#include <libdsl/dslbase.h>
#include <libdsl/DRefObj.h>
#include <libdsl/DThreadRunner.h>
#include <libdsl/DEvent.h>

#include <list>

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

#define INVALID_TIMER_ID	((unsigned int)-1)

class LIBDSL_API DTimerHandler : virtual public DRefObj
{
public:
	DTimerHandler() {}
	DSL_DEPRECATED DTimerHandler( DRefObj * /*obj*/ ) {}

	virtual void OnTimeout( unsigned int timer_id ) = 0;

protected:
	virtual ~DTimerHandler() {}
};

// TODO : ��ʱ�ȵ��̻߳ص����Ժ��ٿ��Ƕ��̻߳ص�timer����ʱҪע��ͬһ��Handler�Ķ��timer�ص��Ĵ��л�
//        ���timer�����϶࣬��ʱ�����������ͨ���������DTimerMgr���������ö��߳�

// Timer���Ƕ���ִ�еģ��������ִ�У������StopTimer()

class LIBDSL_API DTimerMgr
{
public:
	DTimerMgr();
	virtual ~DTimerMgr();

	// create timer, and start, ret_timer_id will get id value before OnTimeout callback
	void CreateTimer( DTimerHandler * handler, int timeout_ms, unsigned int * ret_timer_id );
	// create timer, not start, return timer id
	unsigned int CreateTimer( DTimerHandler * handler );
	int StartTimer( unsigned int timer_id, int timeout_ms );
	int PauseTimer( unsigned int timer_id );
	DSL_DEPRECATED int StopTimer( unsigned int timer_id ) { return PauseTimer( timer_id ); }
	int DestroyTimer( unsigned int timer_id );
	DSL_DEPRECATED int CloseTimer( unsigned int timer_id ) { return DestroyTimer( timer_id ); }

	inline int GetTimerNum() { m_mtxTimers.Lock(); int ret = (int)m_Timers.size(); m_mtxTimers.Unlock(); return ret; }

protected:
	int runTimer( DThread * th );

protected:
	class TNode
	{
	public:
		unsigned int m_id;
		DRef<DTimerHandler> m_handler;
		uint32_t m_next_tick;
		int timeout_ms;
	};

	unsigned int m_next_id;       // ��һ��timer id����Ϊhint��TODO�����Ż�
	DMutex m_mtxTimers;
	std::list< TNode > m_Timers;  // ��ʱ��������������е�timer
	std::map<int, TNode> m_preTimers;  // δ���л�ֹͣ��timer

	DEvent m_evt;
	DRunner<DTimerMgr> m_runner;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBDSL_DTIMERMGR_H
