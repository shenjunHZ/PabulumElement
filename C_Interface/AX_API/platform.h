#ifndef __PLATFORM_H__
#define __PLATFORM_H__
//
// basic primitive data types:
//   byte, int8, uint8, int16, uint16, int32, uint32, float32, float64
//   char, string, boolean, time, octetString, binaryString, octet, displayString
//   octetString
//

#if !defined(byte)
typedef unsigned char byte;
#endif

#if !defined(int8)
typedef char int8;
#endif

#if !defined(uint8)
typedef unsigned char uint8;
#endif

#if !defined(int16)
typedef short int16;
#endif

#if !defined(uint16)
typedef unsigned short uint16;
#endif

#if !defined(int32)
typedef int int32;
#endif

#if !defined(uint32)
typedef unsigned int uint32;
#endif

#if !defined(float32)
typedef float float32;
#endif

#if !defined(float64)
typedef double float64;
#endif

#if !defined(octet)
typedef unsigned char octet;
#endif

#if !defined(sstring)
typedef char* sstring;
#endif

#if !defined(displayString)
typedef char* displayString;
#endif

#if !defined(octetString)
typedef unsigned char* octetString;
#endif

#if !defined(binaryString)
typedef unsigned char* binaryString;
#endif

#if !defined(uint64)
#if (defined( _WIN32 ) || defined( _WIN64))&& ! defined( __MINGW32__ )
typedef unsigned __int64	uint64;
#else
typedef unsigned long long	uint64;
#endif
#endif

#if !defined(int64)
#if (defined( _WIN32 ) || defined( _WIN64)) && ! defined( __MINGW32__ )
typedef __int64	int64;
#else
typedef long long	int64;
#endif
#endif

#if !defined(uint128)
typedef struct { unsigned char octet[16]; } uint128;
#endif

#if !defined(boolean)
typedef uint8 boolean;
#endif

#if !defined(ip_Address)
typedef unsigned char* ip_Address;
#endif

#if !defined(DateTime)
typedef unsigned long DateTime;
#endif

#if !defined(TRUE)
#define TRUE ((boolean)1)
#endif

#if !defined(FALSE)
#define FALSE ((boolean)0)
#endif

#if !defined(NULL)
#define NULL ((int32)0)
#endif

#ifndef DOAX_DEPRECATED
#if defined(_WIN32) || defined(_WIN64)
// 放在class关键字后面，以及函数或者变量定义的前面
#define DOAX_DEPRECATED	__declspec(deprecated)
#else
#define DOAX_DEPRECATED	__attribute__ ((deprecated))
#endif // #ifdef WIN32
#endif // #ifndef DOAX_DEPRECATED

#endif //__PLATFORM_H__

