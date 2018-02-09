/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾,  All rights reserved.
 *2014-03
 *
 * �ļ����ƣ�DSysUtil.h
 */

#ifndef INCLUDED_LIBDSL_DSYSUTIL_H
#define INCLUDED_LIBDSL_DSYSUTIL_H

#include <libdsl/dslbase.h>
#include <time.h>
#include <vector>

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

struct ProcessInfo
{
	int Pid;
	char ProcName[64];
	char ProcPath[256];
};

class LIBDSL_API DSysUtil
{
public:  
	DSysUtil(){};
	~DSysUtil(){};

	static DSysUtil * instance(){return &m_sysUtil;}

	// ��ȡ��ǰ����·������ȡ�ɹ�����0
	int getCurrentPath( char *path, int len );

	// ����ϵͳʱ��
	void syncTime( time_t newTime );

	// ͨ���������ƻ�ȡ������Ϣ,������ΪNULL,���ȡ��ǰ���н��̵���Ϣ
	int GetProcInfo( std::vector<dsl::ProcessInfo> &vecProcInfo, char *name = NULL );

	// ��ȡ��ǰ�̺߳�
	int GetCurrentThreadID();

private:
	static DSysUtil m_sysUtil;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBDSL_DSYSUTIL_H

