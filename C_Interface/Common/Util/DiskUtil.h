#ifndef __COMMON_DISKUTIL_H__
#define __COMMON_DISKUTIL_H__

#include "Common/CommonGlobal.h"
#include "Common/BasicTypes.h"
#include <vector>
#include <string>

namespace Common
{
	// 磁盘信息
	struct DiskSpaceInfo
	{
		unsigned long long iCapacity;  // 总容量
		unsigned long long iFree;      // 剩余
		unsigned long long iAvailable; // 可用
	};

	// 获取磁盘信息
	COMMON_EXPORT bool GetDiskSpace(const char* pPathName, DiskSpaceInfo& struDiskSpaceInfo );
}

#endif // __COMMON_DISKUTIL_H__
