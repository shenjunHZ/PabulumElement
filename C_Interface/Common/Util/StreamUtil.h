
#ifndef __COMMON_STREAMUTIL_H__
#define __COMMON_STREAMUTIL_H__

#include "Common/CommonGlobal.h"
#include <string>


#define  MEDIAPARSERBUFLEN	1*1024*1024		// 码流分析库缓冲大小	

namespace Common
{
	//厂商类型 流类型与播放库自带的vaxplayer.ini做一一映射
	typedef enum
	{
		STREAM_TYPE_UNKNOW = 0,			//未知
		STREAM_TYPE_DAHUA = 1,			//大华流
		STREAM_TYPE_HIK = 2,			//海康流
		STREAM_TYPE_H3C = 3,			//华三流
		STREAM_TYPE_HANBANG = 4,		//汉邦私有流
	}stream_type_e;

	/*
		协议厂商、播放库厂商、后缀名三者映射关系如下：
		
			协议厂商	播放库厂商	后缀名
	 大华		0			1		 .dav
	 海康		1			2		 .hav
	 汉邦		2			4		 .bav
	 宇视		3			3		 .ts
	 ...		..			..		 ...
	*/

	/** brief	协议厂商类型转换成播放库厂商类型
		@param	IN int nProStreamType	协议厂商类型
		@return	播放库厂商类型 具体值表示见枚举stream_type_e
		@see    
	*/
	COMMON_EXPORT int ChangeStreamTypeFromProToVax(int nProStreamType);

	/** brief	根据厂商类型更改后缀名
		@param	IN int nStreamType	播放库厂商类型 具体值表示见枚举stream_type_e
		@param	IN string szOldName 原始文件名
		@param	OUT string szNewName 修改后的文件名
		@return	true:已修改 false:未修改
		@see    
	*/
	COMMON_EXPORT  bool ChangeFileExtName(int nStreamType, const std::string& szOldName, std::string& szNewName);

	/** brief	根据文件名后缀获取具体的厂商类型
		@param	IN char szFilePath 文件全路径
		@return	厂商类型，具体值表示见枚举stream_type_e
		@see    
	*/
	COMMON_EXPORT int GetStreamTypeByFileExtName(const char* szFilePath);

	/** brief	根据具体的厂商类型获取文件名后缀
		@param	[IN]int iStreamType 厂商类型	具体值表示见枚举stream_type_e
		@return	后缀名,含"."
		@see    
	*/
	COMMON_EXPORT std::string GetFileExtNameByStreamType( int iStreamType );
}

#endif
