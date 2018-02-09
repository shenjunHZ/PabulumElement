#ifndef _DSGUI_CHECKBOXITEM_H
#define _DSGUI_CHECKBOXITEM_H

#include "DSGuiGlobal.h"
#include <QGraphicsPixmapItem>

namespace DSGUI
{
    // 勾选框元素
    class DS_GUI_EXPORT DSCheckBoxItem : public QGraphicsPixmapItem
    {
    public:
        // 构造
        DSCheckBoxItem(const QPixmap& pixUnChechBox, const QPixmap& pixChechBox, QGraphicsItem *pParent = NULL);

    public:
        // 是否勾选
        bool IsChecked() const;
    protected:
        // 重载鼠标释放事件
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    private:
        bool m_bChecked; // 是否勾选
        QPixmap m_pixUnCheckPicture; // 勾选图片
        QPixmap m_pixCheckPicture;   // 非勾选图片
    };
}

#endif
