/* Copyright (c) 2013, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2013-07
 *
 * StreamAnalysis.h : ��Ƶ����������
 */

#ifndef INCLUDED_LIBDSL_STREAM_H
#define INCLUDED_LIBDSL_STREAM_H

#include <libdsl/dslbase.h>
#include <map>

#ifdef _WIN32
#pragma warning( disable:4996 )
#endif

enum StreamType 
{ 
	ESTREAM_TYPE_UNKNOW = -1, 
	ESTREAM_TYPE_DHAV = 0,//Ԥ���� 
	ESTREAM_TYPE_HIK = 1,//�������� 
	ESTREAM_TYPE_HANBANG = 2,//�������� 
	ESTREAM_TYPE_UNVIEW = 3,//�������� 
	ESTREAM_TYPE_3RD_PS = 4,//����PS�� 
	ESTREAM_TYPE_XINCH = 5,//�Ų����� 
	ESTREAM_TYPE_LIYUAN = 6,//��Ԫ���� 
	ESTREAM_TYPE_BIT = 7,//�������� 
	ESTREAM_TYPE_3RD_RAW,//�������������� 
};

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

// NOTE : �µ�ý������⣨MediaParser���Ѿ�֧�ֵ������������ͷ�������˱������

class LIBDSL_API DSL_DEPRECATED StreamAnalysis
{
public:
	StreamAnalysis();
    ~StreamAnalysis();

public:
	int GetExtendheadStreamtype(unsigned char *data, int len);

private:
	void InitLenTable();
private:
	std::map<int,int> _lenTable;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif //INCLUDED_LIBDSL_STREAM_H
