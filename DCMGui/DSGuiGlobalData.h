/*
 * @file	DSGuiGlobalData.h
 * @note	Technology Co., Ltd. All Rights Reserved 
 * @brief	DSGUI 全局数据
 * @author	JCL 
 * @date	2015-8-25
 * 
 * @note 
 * @note 
 */
#ifndef __DSGUI_GLOBALDATA_H
#define __DSGUI_GLOBALDATA_H

#include "DSGuiGlobal.h"
#include <QString>

namespace DSGUI
{
	//设置皮肤路径 (strFileName 皮肤文件夹名称)
	extern void SetSkinVersion(QString& strFileName);

	//获取程序运行路径
	extern QString GetSkinVersion();
}
#endif

