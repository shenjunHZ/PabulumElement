/*
 *@file   DSFile.h
 *@brief  封装部分文件操作功能
 * 
 *@author cc
 *@date   2014-06-12
 *
 */

#ifndef __DSGUI_FILE_H
#define __DSGUI_FILE_H

#include "DSGuiGlobal.h"
#include <QString>

namespace DSGUI
{
	/** @class DSFile
	  * @brief 封装部分文件操作功能
	  */
	class DS_GUI_EXPORT DSFile
	{
	public:
        // 读取单个文件中所有字符
        static QByteArray ReadAll(const QString& strFile, const QString& strFilePath = QString());

        // 读取文件列表中所有字符
        static QByteArray ReadAll(const QStringList& strListFile, const QString& strFilePath = QString());
	};
}

#endif
