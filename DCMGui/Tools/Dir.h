/*
 *@file   DSDir.h
 *@brief  封装部分文件目录操作
 * 
 *@author 20753
 *@date   2015-03-17
 *
 */

#ifndef __DSGUI_DIR_H
#define __DSGUI_DIR_H

#include "DSGuiGlobal.h"
#include <QString>

namespace DSGUI
{
	/** @class DSDir
	  * @brief 封装部分文件目录操作
	  */
	class DS_GUI_EXPORT DSDir
	{
	public:
		//设置程序运行路径
		static void SetCurrentPath(QString& strPath);

		//获取程序运行路径
		static QString GetCurrentPath();

	};
}

#endif
