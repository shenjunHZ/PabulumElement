#ifndef _DSGUI_GRAPHICSHITEMLAYOUT_H
#define _DSGUI_GRAPHICSHITEMLAYOUT_H

#include "GraphicsLayout.h"

namespace DSGUI
{
    class DSPictureBrowser;
    // 文字元素
    class DS_GUI_EXPORT DSGraphicsHorLayout : public DSGraphicsLayout
	{
        Q_OBJECT
    public:
        enum LayoutDirection
        {
            LeftToRight = 0,
            RightToLeft = 1,
        };
	public:
		// 构造
        DSGraphicsHorLayout(LayoutDirection enumLayout, DSPictureBrowser* pParent);
        ~DSGraphicsHorLayout();

    public:
        // 添加QGraphicsItem,添加失败返回-1
        virtual int AddItem(QGraphicsItem* pItem);
        // 插入QGraphicsItem,添加失败返回-1
        virtual int InsertItem(int iIndex, QGraphicsItem* pItem);
        // 计算返回第iIndex个QGraphicsItem，不会从列表中移除
        virtual QGraphicsItem* ItemAt(int iIndex) const;
        // 参数为场景的的鼠标位置
        virtual QGraphicsItem* ItemAt(const QPointF& ptPos) const;
        // 取出第iIndex个QGraphicsItem，会从列表中移除
        virtual QGraphicsItem* TakeAt(int iIndex);
        // 计算索引
        virtual int IndexOfItem(QGraphicsItem* pItem) const;
        // 获取QGraphicsItem数量
        virtual int GetItemCount() const;
        // 获取所有QGraphicsItem
        virtual QList<QGraphicsItem*> GetItems() const ;
        // 交换位置
        virtual bool SwapItem(int iSource, int iTarget);
		// 计算第iIndex个QGraphicsItem的位置
		virtual QRectF ActualItemRect(int iIndex);
    public:
        // 设置自动移动是否开启，默认开启
        void SetOpenAutoMoveEnable(bool bOpen);
        // 设置单步移动大小
        void SetSingleStep(int iSingleStep);
        // 左移
        void MoveLeft();
        // 右移
        void MoveRight();
    public:
        // 重新布局
        virtual void ReLayout();

    private slots:
        // 选中改变，处理是否自动移动
        void OnClickedItem(QGraphicsItem* pItem);
        // 值改变
        void OnSliderReleased();
    private:
        QGraphicsView* m_pGraphicsView;
        LayoutDirection m_enumLayoutDirection; // 布局方式
        QList<QGraphicsItem*> m_listItems;
        int m_iSingleStep;
        bool m_bOpenMove; // 是否打开移动
        bool m_bCanMove;  // 是否可以移动
	};
}

#endif
