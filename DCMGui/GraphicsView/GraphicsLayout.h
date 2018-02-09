#ifndef _DSGUI_GRAPHICSITEMLAYOUT_H
#define _DSGUI_GRAPHICSITEMLAYOUT_H

#include "DSGuiGlobal.h"
#include <QGraphicsView>

namespace DSGUI
{
    // 文字元素
    class DS_GUI_EXPORT DSGraphicsLayout : public QObject
	{
        Q_OBJECT
	public:
		// 构造
        DSGraphicsLayout(QGraphicsView* pParent = NULL);
        ~DSGraphicsLayout();

    public:
        // 添加QGraphicsItem,添加失败返回-1
        virtual int AddItem(QGraphicsItem* pItem) = 0;
        // 插入QGraphicsItem,添加失败返回-1
        virtual int InsertItem(int iIndex, QGraphicsItem* pItem) = 0;
        // 计算返回第iIndex个QGraphicsItem，不会从列表中移除
        virtual QGraphicsItem* ItemAt(int iIndex) const = 0;
        // 取出第iIndex个QGraphicsItem，会从列表中移除
        virtual QGraphicsItem* TakeAt(int iIndex) = 0;
        // 计算索引
        virtual int IndexOfItem(QGraphicsItem* pItem) const = 0;
        // 获取QGraphicsItem数量
        virtual int GetItemCount() const = 0;
        // 获取所有QGraphicsItem
        virtual QList<QGraphicsItem*> GetItems() const = 0;
        // 交换位置
        virtual bool SwapItem(int iSource, int iTarget) = 0;
		// 计算第iIndex个QGraphicsItem的位置
		virtual QRectF ActualItemRect(int iIndex) = 0;
    public:
        // 设置横向间隔
        void SetHorizontalSpacing(int iSpacing);
        // 获取横向间隔
        int GetHorizontalSpacing() const;
        // 设置横向间隔
        void SetVerticalSpacing(int iSpacing);
        // 获取横向间隔
        int GetVerticalSpacing() const;

        // 设置边缘间隔
        void SetScenceMargins(int iLeft, int iTop, int iRight, int iBottom);
        void SetScenceMargins(const QMargins& margins);
        // 获取边缘间隔
        void GetScenceMargins(int* pLeft, int* pTop, int* pRight, int* pBottom) const;
        QMargins GetScenceMargins() const;
    public:
        // 重新布局
        virtual void ReLayout() = 0;
    protected:
        int m_iHSpacing;
        int m_iVSpacing;
        int m_iLeftMargin;
        int m_iTopMargin;
        int m_iRightMargin;
        int m_iBottomMargin;
	};
}

#endif
