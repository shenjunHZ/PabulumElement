/*
 *@file   IconProvider.h
 *@brief  图标提供者
 * 
 *@author cc
 *@date   2014-07-18
 *
 */

#ifndef __DSGUI_ICONPROVIDER_H
#define __DSGUI_ICONPROVIDER_H

#include "DSGuiGlobal.h"
#include <QIcon>

namespace DSGUI
{
	/** @class DSIconProvider
	  * @brief 封装部分文件图标获取
	  */
	class DS_GUI_EXPORT DSIconProvider
	{
	public:
        // 获取指定路径图标,参数为完整路径
        static QIcon GetIcon(const QString& strFilePath);
	};
}

#endif
