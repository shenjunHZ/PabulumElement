/*
 *@file   Point.h
 *@brief  封装对点操作的额外接口
 * 
 *@author cc
 *@date   2014-07-02
 *
 */

#ifndef _DSGUI_POINT_H
#define _DSGUI_POINT_H

#include "DSGuiGlobal.h"
#include <QPoint>

namespace DSGUI
{
	/** @class DSPoint
	  * @brief 坐标轴点
	  */
    class DS_GUI_EXPORT DSPoint : public QPoint
	{
	public:
        DSPoint();
        DSPoint(int iX, int iY);

    public:
        // 将ptGlobalPos转换成屏幕上的有效点
        static QPoint GetDesktopAvailablePoint(const QPoint& ptGlobalPos);
    public:
        // 赋值操作
        DSPoint& operator = (QPoint pt);
	};
}


#endif // _DSGUI_POINT_H

