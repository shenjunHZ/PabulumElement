/* Copyright (c) 2013, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
* 2013-10
*
* DMsgBus.h : ��Ϣ���߶���
*/

#ifndef	INCLUDED_LIBDSL_DMSGBUS_H
#define	INCLUDED_LIBDSL_DMSGBUS_H

#include <libdsl/DRefObj.h>
#include <libdsl/DThreadRunner.h>
#include <libdsl/DEvent.h>
#include <libdsl/DStr.h>
#include <deque>
#include <vector>

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

class DMsgBus;

typedef unsigned int DMHID;  // ��ʶMsgHandler��ݵ�ID

#define DMSG_INVALID_ID		((unsigned int)-1)

#define DMSG_TYPE_UNKNOWN			0     // ��Ӧ�ó��ֵ�����
#define DMSG_TYPE_DST_NOT_FOUND		1	  // �����߲����ڣ�ϵͳ�˻ظ�������
#define DMSG_TYPE_DST_NOT_ACCEPT 	2     // �����߲��������Ϣ���˻ظ�������
#define DMSG_TYPE_USER_BEGIN 		1000  // �û��Զ�����ϢӦ��1000��ʼ

class LIBDSL_API DMsg : virtual public DRefObj
{
public:
	DMsg( int type = DMSG_TYPE_UNKNOWN, DMHID src = DMSG_INVALID_ID, DMHID dst = DMSG_INVALID_ID ) 
		: m_type( type ), m_src( src ), m_dst( dst ) {}

	inline void SetType( int type ) { m_type = type; return; }
	inline int GetType() const { return m_type; }

	inline void SetID( DMHID src, DMHID dst ) { m_src = src; m_dst = dst; return; }
	inline void SetSrcID( DMHID src ) { m_src = src; return; }
	inline void SetDstID( DMHID dst ) { m_dst = dst; return; }
	inline DMHID GetSrcID() const { return m_src; }
	inline DMHID GetDstID() const { return m_dst; }

protected:
	virtual ~DMsg() {}

protected:
	int m_type;  // ��Ϣ���� 0 ~ 999 ��ϵͳ����ֵ
	DMHID m_src;
	DMHID m_dst;
};

// �˻ظ��û�����Ϣ�������ŵ���ԭʼ��Ϣ
class LIBDSL_API DMsgWrap : public DMsg
{
public:
	DMsgWrap( const DRef<DMsg> & msg, int type = DMSG_TYPE_UNKNOWN, DMHID src = DMSG_INVALID_ID, DMHID dst = DMSG_INVALID_ID ) 
		: DMsg( type, src, dst ), m_msg( msg ) {}

	inline const DRef< DMsg > & GetMsg() const { return m_msg; }
	inline void SetMsg( const DRef<DMsg> & msg ) { m_msg = msg; return; }

protected:
	DRef<DMsg> m_msg;
};

// ��Ϣ�������Ļ��࣬�û��̳д���ʵ�־������Ϣ����
// ϵͳ�ᱣ֤ͬһ��DMsgHandler�յ�����Ϣ�Ǵ��л����лص�
class LIBDSL_API DMsgHandler : virtual public DRefObj
{
public:
	DMsgHandler() : m_id( DMSG_INVALID_ID ) {}

	inline DMHID GetID() { return m_id; }
	virtual const char * GetName() { return NULL; }
	virtual int OnMsg( const DRef<DMsg> & msg ) = 0;
	
protected:
	virtual ~DMsgHandler() {}

private:
	friend class DMsgBus;
	DMHID m_id; // ����ʱ���ã��˳�ʱ�������DMsgBus����ά��
};

// NOTE ����OnMsg()��ʵ���У�������Ҫmsgת���ɾ�������࣬����ʹ��DRef::Cast()������ʵ��
// ���� DRef<DMsg> msg = new DMsgWrap(); DRef< DMsgWrap > msgwrap = msg.Cast<DMsgWrap>();

#define DMSG_FLAG_MSG_URGENCY	(1 << 0)	// ������Ϣ�����ڶ���ǰͷ���촦��

class LIBDSL_API DMsgBus
{
public:
	DMsgBus( unsigned int nThreadNum = 1, unsigned int nMaximumQueue = 4096 );
	virtual ~DMsgBus();

	int Start();
	int SignalStop();
	int Stop();

	// NOTE : ��ӵ�handler�����ɳ���65535��
	DMHID AddHandler( const DRef<DMsgHandler> & handler );
	int DelHandler( const DRef<DMsgHandler> & handler );

	DMHID FindHandler( const char * name );

	int PushMsg( const DRef< DMsg > & msg, int flag = 0 );

	int QueueSize( void );
	bool IsRunning( void ) const { return m_isRunning; }
	void SetThreadName(const char * name); // �����߳����� �15�ֽ� ������Startǰ����

protected:
	int driver_engine( DThread * th, int index );
	static int driver_func( void * arg, void * th );

protected:
	class  PerThreadInfo
	{
	public:
		int id;
		DMsgBus* pMsgBus;
	};

	unsigned int m_maximumQueue;
	unsigned int m_threadNum;
	int m_handlerCount;          // ��ֹMsgHandler��ID�ظ���ȫ�ּ���
	
	dsl::DEvent* m_evt;
	std::vector< std::deque< DRef<DMsg> > > m_vecMsg;

	std::vector< PerThreadInfo > m_vecArgInfo;

	dsl::DMutex m_handlerMutex;
	std::vector< DRef<DMsgHandler> > m_vecHandler;
	
	std::vector< DRunner<void> > m_vecThread;
	bool m_isRunning;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBDSL_DMSGBUS_H

