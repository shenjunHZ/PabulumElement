/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2011-09
 *
 * DExceptionHandler.h : UEF for Windows
 */

#ifndef INCLUDED_LIBDSL_DEXCEPTIONHANDLER_H
#define INCLUDED_LIBDSL_DEXCEPTIONHANDLER_H

#include <libdsl/dslbase.h>

#ifdef _WIN32
#include <windows.h>
#include <dbghelp.h>
// #include <string>
#endif

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

class LIBDSL_API DExceptionHandler
{
private:
	DExceptionHandler() {}
	~DExceptionHandler() {}
	
public:
	static int StartMonitor(const char * szFileName); 
	static int do_minidump(void* pExceptionInfo);
	
#ifdef _WIN32
private:
	static int disable_setunhandledexceptionfilter(void); 

	static LONG WINAPI unhandleexception_handler(struct _EXCEPTION_POINTERS * ExceptionInfo);
	static void purecall_handler(void);
	static void invalidparameter_handler(const wchar_t * expression, const wchar_t * function, const wchar_t * file, unsigned int line, uintptr_t pReserved);
	static void __cdecl new_handler(void);

private:
	// ʹ��Ԥ�ȷ���ռ�ľ�̬������ʽ�����ٶ�ջ����ʹ��
	static bool m_firstException;
	static char m_full_fileName[MAX_PATH];
	static char m_dump_filename[MAX_PATH];
	static SYSTEMTIME m_lpSystemTime;
	static DWORD m_processID;
	static HANDLE m_processHandle;
	static MINIDUMP_EXCEPTION_INFORMATION m_exception_param;
	static HANDLE m_hFileMiniDump;
	static void * m_reserved_space; 
#endif // _WIN32
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBDSL_DEXCEPTIONHANDLER_H

