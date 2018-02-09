/* Copyright (c) 2012, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2013-05
 *
 * DStatus.h : ͳ��ϵͳ��Դ���
 */

#ifndef INCLUDED_LIBDSL_DSTATUS_H
#define INCLUDED_LIBDSL_DSTATUS_H

#include <libdsl/dslbase.h>
#include <vector>
#include "libdsl/DStr.h"

#define MAX_ADAPTER_NAME_LEN		256
#define MAX_MAC_ADDRESS_LEN			32

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

struct AdapterInfo
{
	char adapterName[MAX_ADAPTER_NAME_LEN + 4];
	char macAddr[MAX_MAC_ADDRESS_LEN];
	char hostAddr[MAX_MAC_ADDRESS_LEN];
	char subNetMask[MAX_MAC_ADDRESS_LEN];
	char gateWayAddr[MAX_MAC_ADDRESS_LEN];
};

class DStatusImp;

class LIBDSL_API DStatus
{
public:  
	DStatus();
	~DStatus();

	static DStatus * instance() { return &m_status; }

	// ��ȡ��ǰ����CPUʹ���� 0~100
	int getCpuUsage();	

	// ��ȡ��ǰ������ʹ�������ڴ��С   
	int getMemoryUsage(uint64_t * mem);

	// ��ȡ��ǰ����IO�����ֽ���
	int getIOBytes(uint64_t * readBytes, uint64_t * writeBytes);

	// ��ȡָ��·�����ڴ��̵�ʹ����Ϣ
	int getDiskUsage(const char * dir, uint64_t * freeBytes, uint64_t * totalBytes);

	// ��ȡ������� index ��ʾ������� 
	// sendRate��ʾ������ǰ��������(��λ bit/s)
	// recvRate��ʾ������ǰ��������(��λ bit/s)
	// ��С��ѯ����Ϊ1�룬LINUX�·�Ϊ���λ�ȡʱ����ڵ�ƽ�����ͺͽ�������
	// bandwidth��ʾ����������(��λ bit/s)
	// ����ֵ0 ��ʾ�ɹ� <0 ��ʾʧ��
	int getNetState(int index,uint64_t * sendRate,uint64_t * recvRate,uint64_t * bandwidth);

public:
	// ��ȡ����������,Mac�����������ء����������ַ
	int getAdapterInfo( std::vector<AdapterInfo> &vecAdapterInfo );

	// ��ȡ����SN���к� 
	// windows�»�ȡ��һ��������Mac��ַ, linux������ȡ���к�ʧ����ȡeth0������Mac��ַ
	int getSerialNum( char *machineSN, int serialNumSize );

	// ����UUID 
	// NOTE:linux������ libuuid ��, TODO:MAC��δʵ��
	int generateUUID(dsl::DStr& UUIDStr);
	
private:
#if !defined(_WIN32) && !defined(MAC)
	// ��ȡ��ǰ���ͺͽ��ܵ����ֽ���
	int  getCurrentByte( );
	void getBandWidth( int index );
	int  readSerial( char *SN );
#endif

private:
	static DStatus m_status;

	DStatusImp * m_impl;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif  // INCLUDED_LIBDSL_DSTATUS_H

