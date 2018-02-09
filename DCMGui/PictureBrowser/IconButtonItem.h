#ifndef _DSGUI_ICONBUTTONITEM_H
#define _DSGUI_ICONBUTTONITEM_H

#include "DSGuiGlobal.h"
#include <QGraphicsPixmapItem>

namespace DSGUI
{
    // 按钮图标元素，带OpenHandCursor状态
	class DS_GUI_EXPORT DSIconButtonItem : public QObject,
        public QGraphicsPixmapItem
	{
        Q_OBJECT
	public:
		// 构造
        DSIconButtonItem(const QPixmap& pixmap, QGraphicsItem *pParent = NULL);

    signals:
        // 鼠标点击
        void SignalClicked();
    private:
        // 鼠标释放
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* pMouseEvent);
        // 绘图
        virtual void paint(QPainter *pPainter, const QStyleOptionGraphicsItem *option, QWidget *pWidget = 0);
	};
}

#endif
