/*
 *@file   WidgetUtil.h
 *@brief  封装窗口相关函数
 * 
 *@author cc
 *@date   2014-07-01
 *
 */

#ifndef __DSGUI_WIDGETUTIL_H
#define __DSGUI_WIDGETUTIL_H

#include "DSGuiGlobal.h"
#include <QtCore/QRectF>

class QWidget;
namespace DSGUI
{
    // 获取最顶层类名非pFilterClassName独立窗口（包括pWindow）
    DS_GUI_EXPORT QWidget* GetTopWindow(QWidget* pWindow, const char* pFilterClassName = NULL);

    typedef struct StruWindowData
    {
        enum WindowSection
        {
            NoSection,
            LeftSection,
            TopLeftSection,
            TopSection,
            TopRightSection,
            RightSection,
            BottomRightSection,
            BottomSection,
            BottomLeftSection,
            CenterSection 
        };

    }WindowData;

    // 计算坐标在窗口区域
    StruWindowData::WindowSection WindowSectionAt(QRectF rtWidget, QPointF ptPos,
        qreal dLeftMargin, qreal dTopMargin, qreal dRightMargin, qreal dBottomMargin);
}

#endif
