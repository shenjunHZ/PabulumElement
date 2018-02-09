/*
 *@file   SystemUtil.h
 *@brief  封装系统相关函数
 * 
 *@author cc
 *@date   2014-07-01
 *
 */

#ifndef __DSGUI_SYSTEMUTIL_H
#define __DSGUI_SYSTEMUTIL_H

#include "DSGuiGlobal.h"
#include <QtNetWork/QNetworkInterface>

namespace DSGUI
{
    // 不阻塞主线程的等待，但主线程的消息队列会继续执行，需考虑数据同步问题
    DS_GUI_EXPORT void qWait(int iMs);

    // 会阻塞主线程
    DS_GUI_EXPORT void qSleep(int iMs);

	// 获取本机IP
	DS_GUI_EXPORT QString GetLocalIP(QAbstractSocket::NetworkLayerProtocol enumProtocol);
}

#endif
