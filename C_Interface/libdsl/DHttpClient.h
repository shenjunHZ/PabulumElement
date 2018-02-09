/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2012-12
 *
 * DHttpClient.h : Http�ͻ��˿�
 */

#ifndef INCLUDED_LIBDSL_DHTTPCLIENT_H
#define INCLUDED_LIBDSL_DHTTPCLIENT_H

#include <libdsl/dslbase.h>
#include <libdsl/DHttp.h>
#include <libdsl/DRefObj.h>
#include <libdsl/DEvent.h>
#include <libdsl/DNetEngine.h>

#include <deque>

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

class DHttpSession;
class DHttpClient;
class DHttpServerSession;

class LIBDSL_API DHttpHandler : virtual public DRefObj
{
public:
	DHttpHandler() {}
	virtual ~DHttpHandler() {}

	virtual int OnConnect( const DRef<DHttpSession> & httpsess, const char * remote_ip, int remote_port ) = 0;
	virtual int OnHttp( const DRef<DHttpSession> & httpsess, const DHttp & httpmsg  ) = 0;
	virtual int OnClose( const DRef<DHttpSession> & httpsess ) = 0;
};

class LIBDSL_API DHttpSession : public DSocketHandler
{
public:
	DHttpSession();

	int SetHandler( const DRef< DHttpHandler > & handler );

	int SendHttp( const DHttp & httpmsg );
	// return 1 : got msg, 0 : timeout, < 0 : error
	int WaitHttp( DHttp * httpmsg, int timeout_ms );
	int SetSendBufSize(int max_size );
	int Close();

protected:

	virtual void OnConnect( SOCKID hSocket, SOCKID newClient, const char * remoteAddr, int remotePort,DRef<DSocketHandler> * ppEvent );
	virtual void OnData( SOCKID hSocket, const char * pBuffer, int len, const char* remoteAddr, int remotePort );
	virtual void OnClose( SOCKID hSocket, int error );

	virtual ~DHttpSession();
	
protected:
	friend class DHttpClient;
	friend class DHttpServerSession;
	DNetEngine * m_neteng;
	SOCKID m_sock;
	DRef<DHttpHandler> m_handler; // �����handler����ͨ��handler�ص�
	DHttp * m_msg;		// ����δ��������http��
	bool m_is_recv_body;

	DEvent m_evt;
	DHttp * m_wait_msg;  // ����ⲿ���ڵ���WaitHttp�ڵȴ��������֪ͨ�ȴ��ɹ�
	std::deque< DHttp*> m_pending_msg;  // �������Ϣ����������������ѯ
};

class LIBDSL_API DHttpClient
{
public:
	DHttpClient( DNetEngine * ne );
	virtual ~DHttpClient();

	DRef<DHttpSession> Connect( const char * ip, int port, const DRef<DHttpHandler> & handler = 0 );

protected:
	DNetEngine * m_neteng;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBDSL_DHTTPCLIENT_H
