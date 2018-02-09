/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2011-09
 *
 * DTime.h : ʱ�䴦����
 */

#ifndef INCLUDED_LIBDSL_DTIME_H
#define INCLUDED_LIBDSL_DTIME_H

#include <libdsl/dslbase.h>
#include <time.h>

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

/* ע�⣺��С�� Y2038 ���⣬DTime֧��ת����ʱ����һ����Χ��
 * linux 32λ�´���� 1900 �굽 2038 �꣬
 * linux 64λ�����൱��������
 * windowsƽ̨������32λ����64λ������� 1970 �굽 3000 ��
 */

#ifdef _WIN32
// windowsƽ̨��32λ��64λ���� time_t ��64λ�ģ���������һ��ʱ�䷶Χ�����3000���ڣ����ٿ���ʱ��
#define LIBDSL_DTIME_MAX ( (0x793406fffLL - 12LL * 3600) * 1000LL )
#define LIBDSL_DTIME_MIN ( 12LL * 3600 * 1000LL )
#elif ( defined(__SIZEOF_LONG__) && __SIZEOF_LONG__ == 8 ) || ( defined(__WORDSIZE) && __WORDSIZE == 64 )
#define LIBDSL_DTIME_MAX ( 0x7fffffffffffffffLL )
#define LIBDSL_DTIME_MIN ( 0x8000000000000000LL )
#else
#define LIBDSL_DTIME_MAX ( 0x7fffffffLL * 1000 )
#define LIBDSL_DTIME_MIN ( 0xffffffff80000000LL * 1000 )
#endif

// DTime��ʱ��ı�ʾ��ת������

class LIBDSL_API DTime
{
public:
	// DTime����֧�֣�ת������������Сʱ��
	static const int64_t s_maxTime = LIBDSL_DTIME_MAX;
	static const int64_t s_minTime = LIBDSL_DTIME_MIN;

	static int64_t Now();      // ��̬��Ա���� ��ȡϵͳ��ǰʱ�� ��λms Epoch(1970-1-1) 
	static int64_t GetTime() { return Now(); }
	static uint32_t GetTick(); // ms from system start, 49 days roundup
	static int GetTimeZone();	// ��ȡϵͳʱ�����������ʱ��������ms ��λms
	
	DTime();
	DTime( int64_t t );
	DTime( const DTime & t );
	DTime & operator = ( const DTime & t );

	void SetNow();

	// ��λ��ms������Ҫ��1000LL��Ҫ����ת����64λ����ֹ���
	// ��� t С��LIBDSL_DTIME_MIN����ǿ����ΪLIBDSL_DTIME_MIN����ʾ��ʱ�䡣
	// ��� t ����LIBDSL_DTIME_MAX����ǿ������ΪLIBDSL_DTIME_MAX����ʾ��ʱ��
	void SetTime( int64_t t ); 

	// �����Ա��ŵı���ʱ��ת����Epochʱ�䣨��1970-1-1��ʼ����������λms
	// ���ʵ�ʱ�ʾ��ʱ������LIBDSL_DTIME_MIN����ʾ��ʱ�䣬�򷵻�LIBDSL_DTIME_MIN
	// ���ʵ�ʱ�ʾ��ʱ������LIBDSL_DTIME_MAX����ʾ��ʱ�䣬�򷵻�LIBDSL_DTIME_MAX
	int64_t MakeTime() const;

	// t ��ʱ��������λms
	DTime & operator += ( int64_t t );
	DTime & operator -= ( int64_t t );

public:
	int m_year;		
	int m_month;	
	int m_day;		
	int m_hour;		
	int m_minute;
	int m_second;
	int m_millisecond;
	int m_dayOfWeek;
};

LIBDSL_API bool operator == ( const DTime & t1, const DTime & t2 );
LIBDSL_API bool operator != ( const DTime & t1, const DTime & t2 );
LIBDSL_API bool operator < ( const DTime & t1, const DTime & t2 );
LIBDSL_API bool operator <= ( const DTime & t1, const DTime & t2 );
LIBDSL_API bool operator > ( const DTime & t1, const DTime & t2 );
LIBDSL_API bool operator >= ( const DTime & t1, const DTime & t2 );
LIBDSL_API DTime operator + ( const DTime & t1, int64_t t2 );
LIBDSL_API DTime operator - ( const DTime & t1, int64_t t2 );

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif //INCLUDED_LIBDSL_DTIME_H
