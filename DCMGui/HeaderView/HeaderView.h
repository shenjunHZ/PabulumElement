/*
 *@file   HeaderView.h
 *@brief  标题视图
 * 
 *@author 
 *@date   
 *
 */

#ifndef __DSGUI_HEADERVIEW_H
#define __DSGUI_HEADERVIEW_H

#include "DSGuiGlobal.h"
#include <QtGui/QHeaderView>

namespace DSGUI
{
    class DSHeaderViewPrivate;
	class DS_GUI_EXPORT DSHeaderView : public QHeaderView
	{
		Q_OBJECT
	public:
		DSHeaderView(Qt::Orientation enumOrientation, QWidget* pParent);
        ~DSHeaderView();

    public:
		// 设置model
		virtual void setModel(QAbstractItemModel *pModel);

	public:
		// 是否带动视图勾选自动改变
		void SetAutoChangeCheckbox(bool bAutoChangeCheckbox);

	signals:
		// 标题栏checkbox状态改变 不能通过headerDataChanged来获取状态，由于Qt内部此消息会造成视图重新布局
		void SignalCheckStateChanged(Qt::CheckState enumCheckState);  

		// 点击标题栏
		void SignalHeadClicked(Qt::CheckState enumCheckState);

	protected:
		// 绘制标题栏 处理checkbox
		virtual void paintSection(QPainter* pPainter, const QRect& rtHeader, int iIndex) const;
        // 由于Qt内部风格存在缺陷，column宽度在没有数据时，第0列会计算出错，字符显示不全
        virtual QSize sectionSizeFromContents(int iLogicalIndex) const;

	private:
		// 鼠标释放事件
		virtual void mouseReleaseEvent(QMouseEvent* pEvent);

    private:
        QScopedPointer<DSHeaderViewPrivate> d_ptr;

    private:
        Q_DECLARE_PRIVATE(DSHeaderView)
        Q_DISABLE_COPY(DSHeaderView)
        Q_PRIVATE_SLOT(d_func(), void OnDataChanged(const QModelIndex&))
        Q_PRIVATE_SLOT(d_func(), void OnUpdateCheckState())

	};
}

#endif
