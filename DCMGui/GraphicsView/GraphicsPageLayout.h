#ifndef _DSGUI_GRAPHICSPAGELAYOUT_H
#define _DSGUI_GRAPHICSPAGELAYOUT_H

#include "GraphicsLayout.h"

namespace DSGUI
{
    class DSPictureBrowser;
    // 文字元素
    class DS_GUI_EXPORT DSGraphicsPageLayout : public DSGraphicsLayout
	{
        Q_OBJECT
	public:
		// 构造
        DSGraphicsPageLayout(DSPictureBrowser* pParent);

    public:
        // 设置一页单元格
        void SetPageCellCount(int iRowCount, int iColCount);
        // 设置当前page页
        void SetCurrentPage(int iIndex);
        // 获取当前page页
        int GetCurrentPage() const;
        // 下一页
        void NextPage();
        // 上一页
        void PrePage();
        // 获取当前page页数量
        int GetPageCount() const;
		//拖拽翻页 下一页
		void MoveNextPage(int index);
		//拖拽翻页  上一页
		void MovePrePage(int index);
		//获取当前页第一个index
		int GetFirstIndex();
		//获取当前页最后一个index
		int GetLastIndex();

    public:
        // 添加QGraphicsItem,添加失败返回-1
        virtual int AddItem(QGraphicsItem* pItem);
        // 插入QGraphicsItem,添加失败返回-1
        virtual int InsertItem(int iIndex, QGraphicsItem* pItem);
        // 计算返回第iIndex个QGraphicsItem，不会从列表中移除
        virtual QGraphicsItem* ItemAt(int iIndex) const;
        // 参数为场景的的鼠标位置
        virtual QGraphicsItem* ItemAt(const QPointF& ptPos) const;
		QList<QGraphicsItem*> ItemsAt(const QPointF& ptPos) const;
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
    signals:
        // 当前page页改变
        void SignalCurrentPageChanged(int iIndex);
        // 总page页改变
        void SignalPageCountChanged(int iPageCount);
    public:
        // 重新布局
        virtual void ReLayout();

		void MoveReLayout(int index);

    private:
        // 更新page总数
        void UpdatePageCount();
    private:
        QGraphicsView* m_pGraphicsView;
        QList<QGraphicsItem*> m_listItems;
        int m_iRowCount;
        int m_iColCount;
        int m_iCurrentPage;
        int m_iPageCount;
	};
}

#endif
