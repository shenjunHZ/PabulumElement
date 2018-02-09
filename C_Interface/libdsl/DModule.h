/* Copyright (c) 2012, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2012-02
 *
 * Module.h :  ģ���� �����ģ�鷢�͵���Ϣ
 */

#ifndef INCLUDED_LIBDSL_MODULE_H
#define INCLUDED_LIBDSL_MODULE_H

#include <libdsl/DMessageQueue.h>
#include <libdsl/DTimerMgr.h>

BEGIN_NAMESPACE_DSL
////////////////////////////////////////////////////////////////////////////////

class DModule;
class LIBDSL_API DModuleMessage : public DMessage
{
public:
	DModuleMessage(DModule * mdl)
	{
		m_deqSourceModules.push_back(mdl);
	}

private:
	friend class DModule;
	bool m_isAck;
	std::deque< DRef<DModule> > m_deqSourceModules;
};


class LIBDSL_API DModule : public DMessageQueue, public DTimerHandler
{
public:
	DModule(unsigned int nThreadNum = 1,unsigned int nMaximumQueue = 1024);

	~DModule();

	// �ڲ���Ϣ��ͨ�ô���

	// 1  ������Ϣ��Ŀ��ģ��
	int SendMessage(DModuleMessage * pMsg, DModule * dstMdl);
	// 2  ������Ϣ��Ŀ��ģ�� ���践��
	int SendReport(DModuleMessage * pMsg, DModule * dstMdl);
	// 3  �ظ���Ϣ��Դģ��
	int ReplyMessage(DModuleMessage * pMsg);

	// ��ʱ������

	// 1 ������ʱʱ ����ֵΪtimerID ����-1��ʾʧ��
	unsigned int CreateTimer();
	// 2 ������ʱ�� ����0��ʾ�ɹ� ������ʾʧ��
	int StartTimer(unsigned int timerID, int timeout_ms);
	// 3 �رն�ʱ�� ����0��ʾ�ɹ� ������ʾʧ��
	int CloseTimer(unsigned int timerID);


public:
	virtual void OnMessage(DModuleMessage* pMsg);				// �յ�����ģ�����Ϣ����
	virtual void OnReplyMessage(DModuleMessage * pMsg);			// �յ�Ŀ��ģ�����Ϣ�ظ�
	virtual void OnTimeout( unsigned int timer_id );	// ��ʱ������

protected:
	virtual void processMsg( DMessage * pMsg );

	DTimerMgr m_TimerMgr;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif //INCLUDED_LIBDSL_MODULE_H
