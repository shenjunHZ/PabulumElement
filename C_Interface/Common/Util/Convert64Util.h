#ifndef __CONVERT64UTIL_H__
#define __CONVERT64UTIL_H__
/*
编、解码相关的方法
*/
#include "Common/CommonGlobal.h"
#include <string>

namespace Common
{

	COMMON_EXPORT  std::string enBase64( const char* inbuf, size_t inbufLen );
	COMMON_EXPORT  std::string enBase64( const std::string &inbuf);
	// TODO : 接口增加 maxOutbufLen 参数, 必须保证outbuf足够大
	COMMON_EXPORT  int  deBase64( std::string src, char* outbuf );
	COMMON_EXPORT  std::string deBase64( std::string src);

}


#endif
