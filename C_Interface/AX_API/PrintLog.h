/* Copyright(c)
 * 
 *
 * PrintLog.h : ��־�����
 */

#ifndef INCLUDED_DSSBASELIB_PRINTLOG_H
#define INCLUDED_DSSBASELIB_PRINTLOG_H

#include <stdarg.h>

#include "AX_API/AX_Mutex.h"

// <1> Log Macro Define

#define PLOG_INIT_FILE( filename )	( CPrintLog::instance()->InitFile( filename ) )
#define PLOG_INIT_STDERR( enable )	( CPrintLog::instance()->InitStderr( enable ) )
#define PLOG_INIT_SYSLOG( enable )	( CPrintLog::instance()->InitSyslog( enable ) )
#define PLOG_SET_LEVEL( level ) ( CPrintLog::instance()->SetLevel( level ) )

#define PLOG_FINI() ( CPrintLog::instance()->Fini() )

#define PLOG_LEVEL_DEBUG	1
#define PLOG_LEVEL_INFO		2
#define PLOG_LEVEL_ERR		3


// ��ӡ��־Ҫ��࣬ȥ��������Ϣ���ؼ����������ڲ��ң����ṩһЩԭʼ���ݹ�����

// ERR �� �������⣬��Ӧ�ó��ֵģ���Ҫ����ע�⣬��Ҫ�����
// INFO �� �����������ʼʱ���Զ�Щ�����ȶ�������𲽼��٣����ֻ�����ؼ��㣬����session���������٣�
// DEBUG �� ������Ϣ���Լ���������ķǹؼ�·��������Ƶ�����ֵĵط�����������²���ӡ��������ʹ�ã�����ҲҪ����

#if defined(_MSC_VER) && _MSC_VER <= 1200
// VC6 doesn't support VARARG in macro, use some hack
#define PLOG_ERR	CPrintLogVC6( __FILE__, __LINE__, PLOG_LEVEL_ERR )
#define PLOG_INFO	CPrintLogVC6( __FILE__, __LINE__, PLOG_LEVEL_INFO )
#define PLOG_DEBUG	CPrintLogVC6( __FILE__, __LINE__, PLOG_LEVEL_DEBUG )

#else

// Normal
#define PLOG_ERR( fmt, ... )	( CPrintLog::instance()->Log( __FILE__, __LINE__, PLOG_LEVEL_ERR, fmt, ##__VA_ARGS__ ) )
#define PLOG_INFO( fmt, ... )	( CPrintLog::instance()->Log( __FILE__, __LINE__, PLOG_LEVEL_INFO, fmt, ##__VA_ARGS__ ) )
#define PLOG_DEBUG( fmt, ... )	( CPrintLog::instance()->Log( __FILE__, __LINE__, PLOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__ ) )

#endif


// <2> log class

#define MAX_LOG_FNAME_LEN	(2048)
#define MAX_LOG_LINE_LEN	(4096)

class DOAX_DEPRECATED CPrintLog
{
public:
	static CPrintLog * instance();

	int InitFile( const char * fname );
	int InitStderr( bool enable );
	int InitSyslog( bool enable );
	int SetLevel( int level );
	int Fini();

	int Log( const char * file, int line, int level, const char * fmt, ... );
	int LogV( const char * file, int line, int level, const char * fmt, va_list ap );

protected:
	CPrintLog();
	~CPrintLog() { Fini(); }

	int create_log_file( int year, int month, int day );
	bool MakeSureDirectoryExist(const char* dir);

#if defined(_WIN32) || defined (_WIN64)
	typedef SYSTEMTIME log_time_t;
#else
	typedef struct {  
		int wYear;  
		int wMonth;
		int wDayOfWeek;
		int wDay;
		int wHour;
		int wMinute;
		int wSecond;
		int wMilliseconds;
	} log_time_t; 
#endif
	int get_curr_time( log_time_t * tm );

private:
	static CPrintLog m_logger;

	bool m_enable_stderr;
	bool m_enable_syslog;

	int m_year, m_month, m_day;
	int m_level;
	char m_fname[MAX_LOG_FNAME_LEN];
#if defined(_WIN32) || defined (_WIN64)
	HANDLE m_fd;
#else
	int m_fd;
#endif
	AX_Mutex	m_mutex;
};

class CPrintLogVC6
{
public:
	CPrintLogVC6( const char * log_file, int log_line, int level ) 
		: m_log_file( log_file ), m_log_line( log_line ), m_level( level ) { }
	~CPrintLogVC6() { }

	void operator () ( const char * fmt, ... );

private:
	const char * m_log_file;
	int m_log_line;
	int m_level;
};

#endif // INCLUDED_DSSBASELIB_PRINTLOG_H
