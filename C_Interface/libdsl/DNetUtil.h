/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2013-12
 *
 * DNetUtil.h : util function for network
 */

#ifndef	INCLUDED_LIBDSL_DNETUTIL_H
#define	INCLUDED_LIBDSL_DNETUTIL_H

#include <libdsl/DNetEngine.h>  // DSL_NET_ADDR_LEN

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

class DStr;

struct RemoteAddrStat
{
	char	addr[DSL_NET_ADDR_LEN];
	int		port;
	bool	reachable;
};

#define DNETUTIL_CHECKTCP_WAITALL	(1<<0)

class LIBDSL_API DNetUtil
{
public:
	DNetUtil() {}
	~DNetUtil() {}

	// ������������host����������IP��ַ��������ʽ��
	static int ResolveAddr(const char * host, char retAddr[DSL_NET_ADDR_LEN]);

	// �������TCP��ͨ�ԣ�ȱʡ�ǵ���һ�ɹ�����ʱ������ʧ��ʱ����
	// ���flagΪDNETUTIL_CHECKTCP_WAITALL����ȫ�����ɹ���ʧ�ܡ���ʱ�ŷ���
	static int CheckTcpConnect(RemoteAddrStat * addressArray, int arraySize, int timeout_ms = 3000, int flag = 0 );

	// ����URL���õ�IP��Port
	// ֧�ָ�ʽ: [schema://]host:[port]/XXX��֧��IPv4 & IPv6�����port�ֶβ����ڣ���ôʹ��defaultPort��ֵ
	static int ParseIpPortFromUrl(const char * url, int defaultPort, DStr * retHost, int * retPort );
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBDSL_DNETUTIL_H
