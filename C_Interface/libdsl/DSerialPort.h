/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾,  All rights reserved.
 * 2014-04
 * 
 * DSerialPort.h : ���ڶ�д����
 * 
 */

#ifndef	INCLUDED_LIBDSL_DSERIALPORT_H
#define	INCLUDED_LIBDSL_DSERIALPORT_H

#include <libdsl/dslbase.h>

#ifndef _WIN32
#include <termios.h>
#include <unistd.h>
#endif


BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

enum{
	FC_XONXOFF = 0x00,
	FC_DTRDSR  = 0x01,
	FC_RTSCTS  = 0x02,
};

enum{
	ASCII_XON  = 0x11,
	ASCII_XOFF = 0x13,
};

class SerialData
{
public:
	int8_t   byteSize;		// ����λ
	int8_t   stopBits;		// ֹͣλ 0, 1, 2
	int8_t   parity;		// ��żУ�� 0:NONE 1:Odd 2:Even 3:Mark 4:Space
	uint32_t baudRate;		// ������
	int8_t   flowCtrl;		// ����
	uint32_t fBinary;		// Binary Mode
	SerialData() : byteSize(8), stopBits(0), parity(0), baudRate(9600), flowCtrl(FC_XONXOFF), fBinary(1){}
};


class LIBDSL_API DSerialPort
{
public:
	DSerialPort();
	~DSerialPort();

	// serialIndex��1��ʼ
	int OpenDev( int serialIndex, SerialData & serialData, int readTimeout );
	void CloseDev();

	// ͬ����д,Read֧�ֳ�ʱ����
	// Readʱһ�ζ�ȡ���ݵ���󳤶�ΪdataLen-1, ��֤data��'\0'����
	int Read( char * data, int dataLen );
	int Write( char * data, int dataLen );

	inline int GetTimeOut(){ return m_readTimeout; }
private:
	int InitDev( SerialData & serialData );

private:
	int			m_readTimeout;	// Ĭ�϶���ʱΪ100ms
#ifndef _WIN32
	int			m_fdSerial;
	termios		m_oldtermios;
#else
	HANDLE		m_handleSerial;
#endif
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif //INCLUDED_LIBDSL_DSERIALPORT_H
