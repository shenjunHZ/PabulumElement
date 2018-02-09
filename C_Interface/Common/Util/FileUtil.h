#ifndef __COMMON_FILEUTIL_H__
#define __COMMON_FILEUTIL_H__

#include "Common/CommonGlobal.h"
#include <vector>
#include <string>

namespace Common
{
	// 获取文件列表
	COMMON_EXPORT std::vector<std::string> GetFileList(const char* pDirName);

	// 获取文件名列表
	COMMON_EXPORT std::vector<std::string> GetFileNameList(const char* pDirName);

	// 创建文件夹
	COMMON_EXPORT bool MakeDir(const char* pDirName);

	// 创建文件夹 采用原生c创建
	COMMON_EXPORT bool MakeDirEx(const char* pDirName);

	// 删除文件
	COMMON_EXPORT bool RemoveFile(const char* pFileName);

	// 检验windows 文件名的有效性，无效的字符使用“_”替换. 
	COMMON_EXPORT std::string GetValidFileName(const char* szFileName);

	// 判断文件是否存在
	COMMON_EXPORT bool FileExists(const char* pFilePath);

	// 重命名文件
	COMMON_EXPORT bool RenameFile(const char* pOldFileName, const char* pNewFileName);

	// 拷贝文件
	COMMON_EXPORT bool CopyFileFunc(const char* pSrcFile, const char* pDstFile);

	// 获取可执行程序路径
	COMMON_EXPORT std::string GetCurDirPath();
}

#endif