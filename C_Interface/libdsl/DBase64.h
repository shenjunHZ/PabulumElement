/* Copyright (c) 2013, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
* 2013-10
*
* DBase64.h : base64�����
*/

#ifndef	INCLUDED_LIBDSL_DBASE64_H
#define	INCLUDED_LIBDSL_DBASE64_H

#include <libdsl/dslbase.h>
#include <libdsl/DStr.h>

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

class LIBDSL_API DBase64
{
public:
	static DStr Encode( const DStr & src );
	static DStr Decode( const DStr & src );

	// ����dstʵ�ʳ��ȣ�dstmaxlenӦ�����㹻�ռ�
	static int Encode( const char * src, int srclen, char * dst, int dstmaxlen );
	static int Decode( const char * src, int srclen, char * dst, int dstmaxlen );
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBDSL_DBASE64_H

