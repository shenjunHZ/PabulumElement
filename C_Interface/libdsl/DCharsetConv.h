/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2011-09
 *
 * DCharsetConv.h : �ַ���ת������
 */

#ifndef INCLUDED_LIBDSL_DCHARSETCONV_H
#define INCLUDED_LIBDSL_DCHARSETCONV_H

#include <libdsl/dslbase.h>

#ifdef ANDROID
// android don't have iconv.h, create a fake one
typedef void * iconv_t;
inline iconv_t iconv_open( const char * tocode, const char * fromcode ) { return NULL; }
inline size_t iconv( iconv_t cd, char ** inbuf, size_t * inbytesleft, char ** outbuf, size_t * outbytesleft ) { return -1; }
inline int iconv_close( iconv_t cd ) { return -1; }
#elif ! defined(_WIN32)
#include <iconv.h>
#endif

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

// �ַ���ת����ϵͳ�ڲ������ʽӦ��ʹ��utf-8��
// ����ʱ��Ӧ�ø���Դ��ʽת����utf-8�����ʱ���ٽ�utf-8ת���������ʽ

enum {
	DSL_CP_UNKNOWN = 0,
	DSL_CP_UTF8,
	DSL_CP_UTF16,
	DSL_CP_UNICODE = DSL_CP_UTF16,
	DSL_CP_GB2312,
	DSL_CP_GBK,
	DSL_CP_GB18030, // 5
	DSL_CP_BIG5,

	DSL_CP_MAX
};

class LIBDSL_API DCharsetConv
{
public:
	DCharsetConv( int fromcp = DSL_CP_UTF8, int tocp = DSL_CP_UTF16 );
	~DCharsetConv();

	int SetCP( int fromcp = DSL_CP_UTF8, int tocp = DSL_CP_UTF16 );

	// ����ת������ַ������ȣ���λbyte����������ظ���
	// ����ʱ���ܻ��в��������ܱ�ת������dst�У�����ǰ����Ƚ�dst����
	int Conv( const char * src, int srclen, char * dst, int dstlen );
	
protected:
	int m_fromcp;  // ת��ǰ�ַ����ı����ʽ
	int m_tocp;    // ת�����ַ����ı����ʽ
#ifndef _WIN32
	iconv_t m_ic;
#endif
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif //INCLUDED_LIBDSL_DCHARSETCONV_H

