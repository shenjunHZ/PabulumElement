/*
 *@file   PixmapItem.h
 *@brief  
 * 
 *@author cc
 *@date   2014-06-23
 *
 */

#ifndef _DSGUI_PIXMAPITEM_H
#define _DSGUI_PIXMAPITEM_H

#include "DSGuiGlobal.h"
#include <QtGui/QGraphicsPixmapItem>

namespace DSGUI
{
    // 图片元素
	class DS_GUI_EXPORT DSPixmapItem : public QGraphicsPixmapItem
	{
	public:
		// 参数1：图片 参数2：图片大小
        DSPixmapItem(const QPixmap& pixmap, QSize szPix = QSize(), QGraphicsItem* pParent = NULL);

	};

    // 图片元素，只在父元素选中时候才显示
    class DS_GUI_EXPORT DSSelectPixmapItem : public QGraphicsPixmapItem
    {
    public:
        // 构造
        DSSelectPixmapItem(const QPixmap& pixmap, QGraphicsItem* pParent = NULL);

    public:
        // 绘图
        void paint(QPainter* pPainter, const QStyleOptionGraphicsItem *option, QWidget *pWidget );
    };

}

#endif
