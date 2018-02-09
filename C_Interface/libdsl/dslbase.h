/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾
 * All rights reserved.
 *
 * �ļ����ƣ�dslbase.h
 * ժҪ���������ͨ�ö���
 *
 */

#ifndef INCLUDED_LIBDSL_DSLBASE_H
#define INCLUDED_LIBDSL_DSLBASE_H

// BEGIN -- ��ƽ̨��صĶ��壬ʹ���߿�������

#ifdef _WIN32

# pragma warning( disable:4127 )

#ifndef __int8_t_defined
#define __int8_t_defined
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int int16_t;
typedef unsigned short int uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif 

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0502
#endif

#include <winsock2.h>
#include <windows.h>

// ����class�ؼ��ֺ��棬�Լ��������߱��������ǰ��
#define DSL_DEPRECATED	__declspec(deprecated)

#if defined(LIBDSL_EXPORTS)
#define LIBDSL_API __declspec(dllexport)
#else
#define LIBDSL_API __declspec(dllimport)
#endif

#if defined(_MSC_VER)
#pragma warning(disable: 4251) /* class 'A' needs to have dll interface for to be used by clients of class 'B'. */
#endif

#else

#include <stddef.h> // NULL
#include <stdint.h>
#include <errno.h>

// ����class�ؼ��ֺ��棬�Լ��������߱��������ǰ�棬��gccʵ�ʿɷ��õĵط�����
#define DSL_DEPRECATED	__attribute__ ((deprecated))

#define LIBDSL_API

#endif

#ifdef __x86_64__
#ifndef DslSizet
#define DslSizet "lu"
#endif
#ifndef DslId64
#define DslId64 "ld"
#endif
#ifndef DslIu64
#define DslIu64 "lu"
#endif
#else
#ifndef DslSizet
#define DslSizet "u"
#endif
#ifndef DslId64
#define DslId64 "lld"
#endif
#ifndef DslIu64
#define DslIu64 "llu"
#endif
#endif // __x86_64__


#ifdef __GNUC__
#define DSL_ATTR_PRINTF(x,y) __attribute__((format (printf,x,y)))
#else
#define DSL_ATTR_PRINTF(x,y) 
#endif

// END -- ��ƽ̨��صĶ��壬ʹ���߿�������

extern "C" LIBDSL_API const char * GetLibInfo_libdsl();
extern "C" LIBDSL_API const char * GetLibInfo_libdsl_1_3_X();

#define BEGIN_NAMESPACE_DSL namespace dsl {
#define END_NAMESPACE_DSL }

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

// ����һ�㷵��0�ɹ������ظ�����ʾʧ��
// һЩͨ�õĴ����룬С��100��ģ��
#define DSL_ERROR_OK			0	// �ɹ�
#define DSL_ERROR_FAILED		-11	// ��������룬ִ��ʧ��
#define DSL_ERROR_INVALID_PARAM	-12	// ��������

#define SAFE_DELETE(obj)		do { if(obj) {delete obj; obj = NULL; } } while(0)
#define SAFE_M_DELETE(obj)		do { if(obj) {delete [] obj; obj = NULL; } } while(0)
#define SAFE_RELEASE(obj)		do { if(obj) {obj->release(); obj = NULL;} } while(0)
// #define SAFE_RET_CALL(fun)		{int nErr = (fun); if(nErr != DSL_ERROR_OK) return nErr;}

class LIBDSL_API DBaseLib
{
public:
	static const char * GetLibInfo();
	static const char * GetLibInfo_1_3_X();

	// �����ظ�Init�����Զ���¼���ô�������Ҫ����ͨ�ö�ε�Uninit
	// szLogFileΪNULL��ʾ���ı���־�ļ�������ر���־����Ҫ�رտɵ���DLOG_SET_FILE(NULL)
	static int Init(const char* szLogFile);
	static int Uninit();

protected:
	static int m_ref;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

namespace DahuaSoftwareLine = dsl;

#endif // INCLUDED_LIBDSL_DSLBASE_H

