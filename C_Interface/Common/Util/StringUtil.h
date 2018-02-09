
#ifndef __COMMON_STRINGUTIL_H
#define __COMMON_STRINGUTIL_H

#include "Common/CommonGlobal.h"
#include "boost/format.hpp"
#include <string>
#include <sstream>
#include <assert.h>

namespace Common
{
	// 指针转字符,当pStr为空值时,默认返回strDefaultValue
	inline std::string PToString(const char* pStr, const std::string& strDefaultValue = "")
	{
		if (NULL == pStr)
		{
			return strDefaultValue;
		}

		return pStr;
	}

	// 指针转int,当pStr为空值时,默认返回nDefaultValue
	inline int PToInt(const char* pStr, int nDefaultValue = 0)
	{
		if ( NULL == pStr )
		{
			return nDefaultValue;
		}

		return atoi(pStr);
	}

	// 指针转long,当pStr为空值时,默认返回nDefaultValue
	inline long PToLong(const char* pStr, long nDefaultValue = 0)
	{
		if ( NULL == pStr )
		{
			return nDefaultValue;
		}

		return atol(pStr);
	}

	// 指针转float,当pStr为空值时,默认返回nDefaultValue
	inline float PToFloat(const char* pStr, float nDefaultValue = 0.0)
	{
		if ( NULL == pStr )
		{
			return nDefaultValue;
		}

		return (float)atof(pStr);
	}

    template <class T>
    inline std::string TToString(const T& source)
    {
        std::stringstream ss;
        ss << source;
        return ss.str();
    }

    template <size_t N>
    inline std::string ArrayToString(const unsigned char (&szArray)[N])
    {
        char szDuplicate[N + 1] = { 0 };
        memcpy(szDuplicate, szArray, N);
        return szDuplicate;
    }

    template <size_t N>
    inline void StringToArray(char (&szArray)[N], const char* pStr)
    {
        assert(pStr != NULL); 
        memset(szArray, 0, N);
        strncpy((char*)szArray, pStr, N);
    }

    template <size_t N>
	inline void StringToArray(char (&szArray)[N], const std::string& str)
    {
        StringToArray(szArray, str.c_str());
    }

	template<class TFirst>
	void StringFormat(boost::format& fmt, const TFirst& first)
	{
		fmt % first;
	}

	template<class TFirst, class TOther>
	void StringFormat(boost::format& fmt, const TFirst& first, const TOther& second)
	{
		StringFormat(fmt, first);
		StringFormat(fmt, second);
	}

	/*传统c语言风格
	cout << boost::format("\n\n%s" 
		"%1t 十进制 = [%d]\n" 
		"%1t 格式化的十进制 = [%5d]\n" 
		"%1t 格式化十进制，前补'0' = [%05d]\n" 
		"%1t 十六进制 = [%x]\n" 
		"%1t 八进制 = [%o]\n" 
		"%1t 浮点 = [%f]\n" 
		"%1t 格式化的浮点 = [%3.3f]\n" 
		"%1t 科学计数 = [%e]\n" 
		) % "example :\n" % 15 % 15 % 15 % 15 % 15 % 15.01 % 15.01 % 15.01 << endl; 

	//.net的风格
	cout << boost::format("%1%" 
		"%1t 十进制 = [%2$d]\n" 
		"%1t 格式化的十进制 = [%2$5d]\n" 
		"%1t 格式化十进制，前补'0' = [%2$05d]\n" 
		"%1t 十六进制 = [%2$x]\n" 
		"%1t 八进制 = [%2$o]\n" 
		"%1t 浮点 = [%3$f]\n" 
		"%1t 格式化的浮点 = [%3$3.3f]\n" 
		"%1t 科学计数 = [%3$e]\n" 
		) % "example :\n" % 15 % 15.01 << endl; 
	**********************************************************/
	// 例子StringFormat("%s--%s", "str1", "str2");
	// 例子StringFormat("%1--%2", "str1", "str2");
	template<class TFirst>
	std::string StringFormat(const char* pFormat, const TFirst& first)
	{
		boost::format fmt(pFormat);
		StringFormat(fmt, first);
		return fmt.str();
	} 

	template<class TFirst, class TOther>
	std::string StringFormat(const char* pFormat, const TFirst& first, const TOther& second)
	{
		boost::format fmt(pFormat);
		StringFormat(fmt, first, second);
		return fmt.str();
	} 
}

#endif
