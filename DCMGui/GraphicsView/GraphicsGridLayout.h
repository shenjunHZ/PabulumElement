#ifndef _DSGUI_GRAPHICSGRIDLAYOUT_H
#define _DSGUI_GRAPHICSGRIDLAYOUT_H

#include "GraphicsLayout.h"

namespace DSGUI
{
    class DSPictureBrowser;
    // 文字元素
    class DS_GUI_EXPORT DSGraphicsGridLayout : public DSGraphicsLayout
	{
        Q_OBJECT
	public:
		// 构造
        DSGraphicsGridLayout(DSPictureBrowser* pParent);

    public:
        // 添加QGraphicsItem,添加失败返回-1
        virtual int AddItem(QGraphicsItem* pItem);
        // 插入QGraphicsItem,添加失败返回-1
        virtual int InsertItem(int iIndex, QGraphicsItem* pItem);
        // 计算返回第iIndex个QGraphicsItem，不会从列表中移除
        virtual QGraphicsItem* ItemAt(int iIndex) const;
        // 取出第iIndex个QGraphicsItem，会从列表中移除
        virtual QGraphicsItem* TakeAt(int iIndex);
        // 计算索引
        virtual int IndexOfItem(QGraphicsItem* pItem) const;
        // 获取QGraphicsItem数量
        virtual int GetItemCount() const;
        // 获取所有QGraphicsItem
        virtual QList<QGraphicsItem*> GetItems() const;
        // 交换位置
        virtual bool SwapItem(int iSource, int iTarget);
		// 计算第iIndex个QGraphicsItem的位置
		virtual QRectF ActualItemRect(int iIndex);
    public:
        // 重新布局
        virtual void ReLayout();
    private:
        QGraphicsView* m_pGraphicsView;
        QList<QGraphicsItem*> m_listItems;
	};
}

#endif
