/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2014-04
 *
 * DStatusServer.h : ״̬����
 */

#ifndef INCLUDED_LIBDSL_DSTATUSSERVER_H
#define INCLUDED_LIBDSL_DSTATUSSERVER_H

#include <libdsl/DHttpServer.h>

#include <set>
#include <list>

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

#define STATUS_CONTENT_TYPE_DIR		"x-status/dir"
#define STATUS_CONTENT_TYPE_INFO1	"x-status/info1"
#define STATUS_CONTENT_TYPE_RWINFO1	"x-status/rwinfo1"
#define STATUS_CONTENT_TYPE_RWTXT	"x-status/rwtxt"

class LIBDSL_API DStatusServer : public DHttpHandler
{
public:
	DStatusServer( DNetEngine * ne );

	const char * GetDocRoot() const { return m_docroot.c_str(); }
	int SetDocRoot( const char * local_path ); // default is "./html"
	// TODO : auth

	// pathӦ���Ǹ�Ŀ¼�µ��ļ�����Ŀ¼����֧�ֶ��Ŀ¼
	int AddResHdl( const char * path, const DRef<DHttpHandler> & handler, const char * content_type = STATUS_CONTENT_TYPE_DIR );
	int DelResHdl( const char * path );

	int Start( const char * ip, int port );
	int Stop();

	static int ReplyHttp( const DRef<DHttpSession> & httpsess, const DHttp & httpmsg, int status, const char * content_type, const char * data, int len = -1 );

protected: // IMP DHttpHandler
	virtual int OnConnect( const DRef<DHttpSession> & httpsess, const char * remote_ip, int remote_port );
	virtual int OnHttp( const DRef<DHttpSession> & httpsess, const DHttp & httpmsg  );
	virtual int OnClose( const DRef<DHttpSession> & httpsess );

protected:
	virtual ~DStatusServer();

	DRef<DHttpHandler> find_handler( const DStr & path );

	// ���� 0��δ����> 0���ɹ�����< 0������ʧ��
	int handle_status( const DStr & path, const DStr & param, const DRef<DHttpSession> & httpsess, const DHttp & httpmsg  );
	int handle_libdsl( const DStr & path, const DStr & param, const DRef<DHttpSession> & httpsess, const DHttp & httpmsg  );
	int handle_dir( const DStr & path, const DStr & param, const DRef<DHttpSession> & httpsess, const DHttp & httpmsg  );

protected:
	DHttpServer m_svr;

	DStr m_docroot;

	DMutex m_lock;
	class ResHdlInfo
	{
	public:
		DStr m_path;
		DRef<DHttpHandler> m_hdl;
		DStr m_type;
	};
	std::list< ResHdlInfo > m_hdls; // ��������̫�࣬�ȼ򵥴���ʹ��������m_path�ӳ���������
	std::set< DRef<DHttpSession> > m_sess;  // ��ǰ���ߵ��û���Ϣ
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBDSL_DSTATUSSERVER_H
