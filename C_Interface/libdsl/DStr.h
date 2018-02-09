/* Copyright (c) 2012, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2012-09
 *
 * DStr.h : �ַ���������
 */

#ifndef INCLUDED_LIBDSL_DSTR_H
#define INCLUDED_LIBDSL_DSTR_H

#include <libdsl/dslbase.h>

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

class LIBDSL_API DStr
{
public:  // һЩ��̬��������װ�������ܣ����а�ȫ��ǿ
	// ��ǿ��strcpy����֤��Խ������'\0'��β������ʵ��д�볤�ȣ�����'\0'��
	static int strcpy_x( char * dst, int dst_max_len, const char * src );

	// ��ǿ��strcat����֤��Խ������'\0'��β������ʵ��д�볤�ȣ�����'\0'��
	static int strcat_x( char * dst, int dst_max_len, const char * src );

	// ��ǿ��sprintf����֤��Խ������'\0'��β������ʵ��д�볤�ȣ�����'\0'��
	// ����֧�� len += sprintf_x( buf + len, maxlen - len, "xxxx", ... ); ������д��
	// ��ʵ��buffer����ʱ����֤\'0'������maxlen - 1����ԭ��snprintf��VC�᷵��-1�Ҳ���֤'\0'��gcc�᷵�ؼ���buffer�㹻ʱ��д�볤�ȣ�
	// ��������maxlen-1ʱ�޷����ֳ��ȸոպû��ǳ����ˣ����Լ򻯶������������߶�������������
	static int sprintf_x( char * dst, int dst_max_len, const char * fmt, ... ) DSL_ATTR_PRINTF(3,4);

	// �ַ���������*��*��֤�����'\0'��β�����ֻ����max_copy_len���ֽڣ����src���Ȳ��㣬ʣ��ռ���'\0'���
	static char * strncpy( char * dst, const char * src, int max_copy_len );

	static int strcmp( const char * src, const char * dst );
	static int strncmp( const char * src, const char * dst, int len );
	static int stricmp( const char * src, const char * dst );
	static int strnicmp( const char * src, const char * dst, int len );
	static int strcasecmp( const char * src, const char * dst );
	static int strncasecmp( const char * src, const char * dst, int len );

	static int atoi( const char * src );
	static int64_t atoi64( const char * src );
	static double atod( const char * src );
	// FIXME : need buf size ? use sprintf instead ?
	static char * itoa( int val, char * buf );
	static char * i64toa( int64_t val, char * buf );
	static char * dtoa( double val, char * buf );
	static bool space(char ch); // �ж��ַ��Ƿ�Ϊ���ɼ��ַ�
	static DStr trim(const char * src, int len); // ȥ���ַ�����β�Ĳ��ɼ��ֶ�

public:
	DStr();
	explicit DStr( const char * src, int len = -1 );
	DStr( const DStr & src );
	~DStr();

	// �����㹻�ռ䣬���ܻ�Ԥ�����࣬�㹻ʱ�������
	int reserve( int len );
	inline bool empty() const { return m_len == 0; }
	inline const char * c_str() const { return m_str; }
	// FIXME : if overflow, return empty char
	inline char operator [] ( int pos ) const { if( pos >= 0 && pos < m_len ) return m_str[pos]; else return '\0'; }
	inline int length() const { return m_len; }
	// int size() const; // FIXME ? len or cap ?

public:
	inline DStr & assign( const DStr & str ) { return assign( str.c_str(), str.length() ); }
	DStr & assign( const char * s, int len = -1 );
	DStr & assignfmt( const char * fmt, ... ) DSL_ATTR_PRINTF(2,3);
	inline DStr & operator = ( const char * s ) { return assign( s ); }
	inline DStr & operator = ( const DStr & str ) { return assign( str ); }

	inline DStr & append( const DStr & str ) { return append( str.c_str(), str.length() ); }
	DStr & append( const char * s, int len = -1 );
	DStr & appendfmt( const char * fmt, ... ) DSL_ATTR_PRINTF(2,3);
	inline DStr & operator += ( const char * src ) { return append( src ); }
	inline DStr & operator += ( const DStr & str ) { return append( str ); }

	friend LIBDSL_API DStr operator + ( const DStr & left, const DStr & right );
	friend LIBDSL_API DStr operator + ( const DStr & left, const char * right );

	int insert( int start, const char * target );
	inline int insert( int start, DStr & target ) { return insert( start, target.c_str() ); }
	int erase( int start, int len );

	DStr substr( int start, int len ) const;
	// �����ҵ����ַ�����λ�ã��Ҳ�������-1
	int findstr( const char * str ) const;
	int findcasestr( const char * str ) const;
	// �����ҵ����ַ���λ�ã��Ҳ�������-1
	int findchar( int ch ) const;
	// ���ش��ַ�����ͷ�����ֵ�accept_chs�е��ַ��ĸ�����û�оͷ���0
	int countaccept( const char * accept_chs ) const;
	// ���ش��ַ�����ͷ�������ֵ�reject_chs�е��ַ��ĸ����������һ���ַ�����chs�У��򷵻�0
	int countreject( const char * reject_chs ) const;

public:
	inline int cmp( const DStr & str ) const { return cmp( str.c_str(), -1 ); }
	int cmp( const char * s, int len = -1 ) const;
	inline int casecmp( const DStr & str ) const { return casecmp( str.c_str(), -1 ); }
	int casecmp( const char * str, int len = -1 ) const;

	friend LIBDSL_API bool operator == ( const DStr & left, const DStr & right );
	friend LIBDSL_API bool operator == ( const DStr & left, const char * right );
	friend LIBDSL_API bool operator != ( const DStr & left, const DStr & right );
	friend LIBDSL_API bool operator != ( const DStr & left, const char * right );
	friend LIBDSL_API bool operator < ( const DStr & left, const DStr & right );
	friend LIBDSL_API bool operator < ( const DStr & left, const char * right );
	friend LIBDSL_API bool operator <= ( const DStr & left, const DStr & right );
	friend LIBDSL_API bool operator <= ( const DStr & left, const char * right );
	friend LIBDSL_API bool operator > ( const DStr & left, const DStr & right );
	friend LIBDSL_API bool operator > ( const DStr & left, const char * right );
	friend LIBDSL_API bool operator >= ( const DStr & left, const DStr & right );
	friend LIBDSL_API bool operator >= ( const DStr & left, const char * right );

public:
	double asDouble() const;
	int64_t asInt64() const;
	int	asInt()const;

	void setValue(double val);
	void setValue(int64_t val);
	void setValue(int val);

	void tolower();
	void toupper();

protected:
	char * m_str;
	int m_len; 
	int m_cap;
};

LIBDSL_API bool operator == ( const DStr & left, const DStr & right );
LIBDSL_API bool operator == ( const DStr & left, const char * right );
LIBDSL_API bool operator != ( const DStr & left, const DStr & right );
LIBDSL_API bool operator != ( const DStr & left, const char * right );
LIBDSL_API bool operator < ( const DStr & left, const DStr & right );
LIBDSL_API bool operator < ( const DStr & left, const char * right );
LIBDSL_API bool operator <= ( const DStr & left, const DStr & right );
LIBDSL_API bool operator <= ( const DStr & left, const char * right );
LIBDSL_API bool operator > ( const DStr & left, const DStr & right );
LIBDSL_API bool operator > ( const DStr & left, const char * right );
LIBDSL_API bool operator >= ( const DStr & left, const DStr & right );
LIBDSL_API bool operator >= ( const DStr & left, const char * right );

LIBDSL_API DStr operator + ( const DStr & left, const DStr & right );
LIBDSL_API DStr operator + ( const DStr & left, const char * right );

// �����ִ�Сд�ıȽ����ӣ�������std::map��
class LIBDSL_API DStrCaseCompare
{
public:
	bool operator () ( const DStr & s1, const DStr & s2 ) const { return s1.casecmp( s2 ) < 0; }
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBDSL_DSTR_H

