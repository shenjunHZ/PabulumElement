#ifndef DH_DSS_COMPONENT_AX_API_AX_STR_H_INCLUDED
#define DH_DSS_COMPONENT_AX_API_AX_STR_H_INCLUDED

#include <stdio.h>
#include <string.h>

namespace AX_OS
{


	typedef int (*Fun_snprintf)(char *buffer,size_t count,const char *format ,... );
	extern Fun_snprintf snprintf;
	
	typedef int (*Fun_stricmp)(const char* str1, const char* str2);
	extern Fun_stricmp stricmp;
	
	//dest:Ŀ��buffer,���Ŀ��bufferû��'\0'�������������һ���ַ�Ϊ'\0',����0
	//src:
	//srcBufLen:Ŀ��buffer���ܳ���,copy����Ŀ���ᳬ�����srcBufLen-1
	//ִ����ɺ������copy����ô��Destһ��������0����
	//���صĽ���Ǵ�src copy��dest�е��ַ���Ŀ
	size_t strncat(char* dest, const char* src, const size_t srcBufLen);

	//��ȫ���ַ���copy����
	//���ݴ����siz��С����src copy���siz-1���ַ���dst,����copy��ɵ��ַ��������'\0'
	//���ڴ����dst=NULL����src=NULL�����˼��
	//����ֵsizΪdst��buffer�Ĵ�С
	//���ؽ����ʵ��copy��dst�е��ַ�����Ŀ��������'\0'�ַ�
	size_t strncpy(char* dst, const char* src, size_t siz);

	//��ȫ���ַ���copy����
	//dst,Ŀ��buffer
	//dstBufLen,Ŀ��buffer�ռ��С,�ú������д��dstBufLen-1���ַ���������д���ַ��������'\0'�ַ�
	//src,Դbuffer
	//Ҫcopy���ַ�����,��dstBufLen-1�ռ����������£����copy���ַ���ĿΪsrcCopyCount,�����ں������'\0'�ַ�
	size_t strncpy(char* dst, size_t dstBufLen, const char* src, size_t srcCopyCount);

	// ��ǿ��snprintf����֤'\0'������ʵ��д�볤�ȣ�
	// ����֧�� len += snprintf_x( buf + len, maxlen - len, "xxxx", ... ); ������д��
	// ��ʵ��buffer����ʱ����֤\'0'������maxlen - 1����ԭ��snprintf��VC�᷵��-1�Ҳ���֤'\0'��gcc�᷵�ؼ���buffer�㹻ʱ��д�볤�ȣ�
	// ��������maxlen-1ʱ�޷����ֳ��ȸոպû��ǳ����ˣ����Լ򻯶������������߶�������������
	// Ҳ��������Ҫ�޳����ұ�֤'\0'ʱ���ַ���������ȡ��strncpy����ע��ԭ��strncpy����֤'\0'��
	// �� strncpy( dst, src, siz - 1 ); dst[size - 1] = '\0'; �൱�� snprintf( dst, siz, "%s", src );
	int snprintf_x( char * buf, int maxlen, const char * fmt, ... );
}

#endif//DH_DSS_COMPONENT_AX_API_AX_STR_H_INCLUDED
