/*
 *@file   BaseView.h
 *@brief  视图基类
 * 
 *@author 
 *@date
 *
 */

#ifndef __DSGUI_BASEVIEW_H
#define __DSGUI_BASEVIEW_H

#include "DSGuiGlobal.h"
#include "ComGUIDef.h"
#include <QTreeView>
#include <QBasicTimer>

namespace DSGUI
{
    class DSBaseViewPrivate;

    class DS_GUI_EXPORT DSBaseView 
        : public QTreeView
    {
        Q_OBJECT

        Q_PROPERTY(QColor msgBoxBottomLineClr READ GetMsgBoxBottomLineColor WRITE SetMsgBoxBottomLineColor)
    public:
        explicit DSBaseView(QWidget* pParent = NULL);
        ~DSBaseView();

        // 信号
    signals:
        // 封装视图上的自绘图片的点击操作 参数2对应Pixmap1Role、Pixmap2Role、Pixmap3Role
        void SignalPixmapClicked(const QModelIndex& miItem, DSGUI::struTreeViewData::DSItemDataRole enumItemRole);

        // 鼠标释放发送（默认的clicked点中勾选框上不会发送）
        void SignalClicked(const QModelIndex& miItem);

    public:
        // 设置横向表格是否显示
        void SetHorizontalGridVisible(bool bVisible);
        // 设置垂直表格是否显示
        void SetVerizontalGridVisible(bool bVisible);

    public:
        // 设置根据文字调整宽度列宽
        void SetColumnResizeToContents(int iColumn);
        //设置调用对象是不是messagebox
        void SetObjType(bool bIsMsgBox);

    protected:
        // 绘制行
        virtual void drawRow(QPainter* pPainter, const QStyleOptionViewItem& optionItem, const QModelIndex& miItem) const;

    protected:
        // 视图事件
        virtual bool viewportEvent(QEvent* pEvent);
        // 大小改变事件
        virtual void resizeEvent(QResizeEvent* pEvent);
        // 处理Column宽度，根据文字自动调整，防止频繁触发造成性能上问题
        virtual void timerEvent(QTimerEvent* pEvent);

    protected Q_SLOTS:
        // 以下重载接口供需自动根据文字调节column宽度使用
        virtual void dataChanged(const QModelIndex& miTopLeft, const QModelIndex& miBottomRight);
        virtual void rowsInserted(const QModelIndex& miParent, int iStart, int iEnd);
        virtual void rowsAboutToBeRemoved(const QModelIndex& miParent, int iStart, int iEnd);

    private:
        QScopedPointer<DSBaseViewPrivate> d_ptr;

    private:
        Q_DECLARE_PRIVATE(DSBaseView)
        Q_DISABLE_COPY(DSBaseView)
        Q_PRIVATE_SLOT(d_func(), void OnExpanded(const QModelIndex& index))
        QColor GetMsgBoxBottomLineColor();
        void SetMsgBoxBottomLineColor(const QColor& msgBoxBottomLineClr);
        QColor m_msgBoxBottomLineClr;

        bool m_bIsMsgBox;
    };
}

#endif
