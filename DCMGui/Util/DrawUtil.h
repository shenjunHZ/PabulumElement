/*
 *@file   DrawUtil.h
 *@brief  绘图封装
 * 
 *@author cc
 *@date   2014-07-01
 *
 */

#ifndef __DSGUI_DRAWUTIL_H
#define __DSGUI_DRAWUTIL_H

#include <QPainter>

namespace DSGUI
{
    // 九宫切割方式绘图,用于实现图片放大
    bool DrawBorderPixmap(QPixmap& pixmapTarget, const QRect& rtTarget, const QMargins& marginsTarget,
        QPixmap& pixmapSource, const QRect& rtSource,const QMargins& marginsSource);
}

#endif
