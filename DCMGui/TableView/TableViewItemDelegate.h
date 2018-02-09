/*
 *@file   TableViewItemDelegate.h
 *@brief  
 * 
 *@author 
 *@date   2014-05-28
 *
 */

#ifndef __DS_TABLEVIEWITEMDELEGATE_H
#define __DS_TABLEVIEWITEMDELEGATE_H

#include "TableView/BaseViewItemDelegate.h"

namespace DSGUI
{
	class DS_GUI_EXPORT DSTableViewItemDelegate : public DSBaseViewItemDelegate
	{
		Q_OBJECT

	public:
        DSTableViewItemDelegate(QObject* pParent);

    public:
        // 绘图
        virtual void paint(QPainter* pPainter, const QStyleOptionViewItem& optionItem, const QModelIndex& miItem) const;

    public:
		// 编辑状态，创建控件
		virtual QWidget* createEditor(QWidget* pParent, const QStyleOptionViewItem& optionItem, const QModelIndex& miItem) const;

		// 给编辑状态下创建的控件设置数据
		virtual void setEditorData(QWidget *pEditor, const QModelIndex& miItem) const;

		// 给视图设置数据
		virtual void setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex& miItem) const;

		// 编辑状态下控件位置
		virtual void updateEditorGeometry(QWidget *pEditor, const QStyleOptionViewItem& optionItem, const QModelIndex& miItem) const;

	public:
		// 设置图片间隔
		void SetPixmapSpace(int nSpace);

		// 设置图片边距
		void SetPixmapMargin(int nMargin);
	signals:
		// 编辑完成,数据改变
		void SignalEditorDataChanged(const QModelIndex& miItem) const;

    protected:
        // 图片排列方式
        virtual Qt::Alignment GetMousePixmapAlignment(const QStyleOptionViewItem& optionItem, const QModelIndex& miItem) const;

        // 检查鼠标所有位置
        virtual struTreeViewData::DSItemDataRole CheckMouse(const QPoint& ptMouse, const QStyleOptionViewItem& optionItem, const QModelIndex& miItem) const;

        // 获取图片区域
        // 参数1为ItemPixmapOneRole，ItemPixmapTwoRole，ItemPixmapThreeRole
        // 参数4指图片排列方式
        virtual QRect GetItemPixmapRect(struTreeViewData::DSItemDataRole enumItemDataRole, const QStyleOptionViewItem& optionItem, 
            const QModelIndex& miItem, Qt::Alignment enumAlignment) const;

        // 获取图片占用的区域
        virtual QRect GetAllItemPixmapRect(const QStyleOptionViewItem& optionItem, const QModelIndex& miItem, Qt::Alignment enumAlignment) const;

    public Q_SLOTS:
        // ToolTip事件
        bool helpEvent(QHelpEvent* pEvent, QAbstractItemView* pView, const QStyleOptionViewItem& optionItem, const QModelIndex& miItem);
        // hover事件
        void hoverEvent(QHoverEvent* pHoverEvent, QAbstractItemView* pView, const QStyleOptionViewItem& optionItem, const QModelIndex& miItem);
        // 鼠标移动事件
        struTreeViewData::DSItemDataRole mouseEvent(QMouseEvent* pMouseEvent, QAbstractItemView* pView, const QStyleOptionViewItem& optionItem,
            const QModelIndex& miItem);

	protected:
        bool m_bMousePressed; // 鼠标按下
		int  m_nPixmapSpace;	//图片间隔
		int	 m_nPixmapMargin;
	};
}

#endif
