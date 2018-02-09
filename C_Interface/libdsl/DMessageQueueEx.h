/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
* 2011-09
*
* DMessageQueueEx.h : �����ȼ���Ϣ���ж���
*/

#ifndef	INCLUDED_LIBDSL_DMESSAGEQUEUEEX_H
#define	INCLUDED_LIBDSL_DMESSAGEQUEUEEX_H

#include <libdsl/DMessageQueue.h>
#include <libdsl/DRefObj.h>
#include <libdsl/DThreadRunner.h>
#include <libdsl/DEvent.h>
#include <deque>
#include <vector>

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////
typedef enum _EnumQueueLevel_
{
	queue_high  = 0,	// �����ȼ�
	queue_normal = 1,	// ��ͨ���ȼ�
	queue_low = 2,		// �����ȼ�
	queue_max,
}EnumQueueLevel;

class DMessageData;

class LIBDSL_API DMessageQueueEx : virtual public DRefObj
{
public:
	DMessageQueueEx(unsigned int nThreadNum = 1,unsigned int nMaximumQueue = 1024) ;
	
	virtual int Start();
	virtual int SignalStop();
	virtual int Stop();

	virtual int PushMsg(DMessage* pMsg, EnumQueueLevel level = queue_normal);
	virtual int QueueSize();

	// �ⲿ������Ϣ�ж�,��ʱ����Ҫ���� Start SignalStop Stop���̲߳�������
	// ����ֵ 0 ���� 1 ��æ
	virtual int HeartBeat(); 

	// ������Ϣ�ж���δ������Ϣ
	// ����ֵ 0 �ɹ� -1 ʧ��
	int		ClearMsg(EnumQueueLevel level = queue_normal);


	bool IsRunning(void) const ;


	void SetThreadName(const char * name); // �����߳����� �15�ֽ� ������Startǰ����

protected:
	virtual ~DMessageQueueEx();
	virtual void processMsg( DMessage * pMsg ) = 0;
	int driver_engine( DThread * th );

protected:

	DMessageData * m_impl;

};

// ��Ϣ����ģ�壬��װ��Ϣ��������ע��ͷ���
// ʹ�÷��� class MyMessageQueue : public DMessageQueueTpl<MyMessageQueue> { ... }; 
// Ȼ���ڹ��캯�����ʼ�������е��� AddFunction() ע����Ϣ������

template< class T >
class DMessageQueueTplEx : public DMessageQueueEx
{
public:
	DMessageQueueTplEx( unsigned int nThreadNum = 1,unsigned int nMaximumQueue = 1024 )
		: DMessageQueueEx( nThreadNum, nMaximumQueue )
	{
	}

protected:
	virtual ~DMessageQueueTplEx() {}
	typedef void (T::*MsgFunc_t)( DMessage * pMsg );
	virtual void processMsg( DMessage * pMsg )
	{
		typename std::map< int, MsgFunc_t >::iterator it = m_funcMap.find( pMsg->GetType() );
		if( it == m_funcMap.end() )
			OnUnknownMsg( pMsg );
		else
			(((T*)this)->*(it->second))( pMsg );
		return;
	}
	virtual void OnUnknownMsg( DMessage * /*pMsg*/ )
	{
		// ��������أ����в���ʶ����Ϣ�Ĵ���ȱʡ��ֱ�Ӻ���
		return;
	}

protected:
	void AddMsgFunc( int type, MsgFunc_t func )
	{
		m_funcMap[type] = func;
		return;
	}
	void DelMsgFunc( int type )
	{
		typename std::map< int, MsgFunc_t >::iterator it = m_funcMap.find( type );
		if( it != m_funcMap.end() )
			m_funcMap.erase( it );
		return;
	}

protected:
	std::map< int, MsgFunc_t > m_funcMap;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif 
