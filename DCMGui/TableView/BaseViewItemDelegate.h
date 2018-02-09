/*
 *@file   BaseItemDelegate.h
 *@brief  
 * 
 *@author 
 *@date   2014-05-24
 *
 */

#ifndef __DS_BASEITEMDELEGATE_H
#define __DS_BASEITEMDELEGATE_H

#include "DSGuiGlobal.h"
#include "ComGUIDef.h"
#include <QtGui/QStyledItemDelegate>

namespace DSGUI
{
    class DS_GUI_EXPORT DSBaseViewItemDelegate : public QStyledItemDelegate
    {
        Q_OBJECT
    public:
        DSBaseViewItemDelegate(QObject* pParent);

    public Q_SLOTS:
        // 处理toolTip操作
        bool helpEvent(QHelpEvent* pEvent, QAbstractItemView* pView, const QStyleOptionViewItem& optionItem, const QModelIndex& miItem);
        // 处理鼠标Hover时间
        void hoverEvent(QHoverEvent* pHoverEvent, QAbstractItemView* pView, const QStyleOptionViewItem& optionItem, const QModelIndex& miItem);
        // 处理鼠标事件
        struTreeViewData::DSItemDataRole mouseEvent(QMouseEvent* pMouseEvent, QAbstractItemView* pView, 
            const QStyleOptionViewItem& optionItem, const QModelIndex& miItem);
    };
}

#endif //__DS_BASEITEMDELEGATE_H
