/*
 *@file   CustomToolBox.h
 *@brief  可随意展开多个抽屉
 *        父类接口不可以使用
 *        ui设计器中从QFrame提升
 *@author cc
 *@date   2014-08-20
 *
 */

#ifndef __DSGUI_CUSTOMTOOLBOX_H__
#define __DSGUI_CUSTOMTOOLBOX_H__

#include "ToolBox/ToolBox.h"

namespace DSGUI
{
    class DSCustomToolBoxPrivate;
    /** @class CCustomToolBox
     *  @brief 可随意展开多个抽屉
     *  父类接口不可以使用
     *  ui设计器中从QFrame提升
     */
    class DS_GUI_EXPORT DSCustomToolBox : public DSToolBox
    {
        Q_OBJECT
    public:
        // 构造
        explicit DSCustomToolBox(QWidget* pParent = NULL);
        // 析构
        ~DSCustomToolBox();

    public:
        // 添加
        int AddItem(QWidget* pWidget, const QString& strText);
        int AddItem(QWidget* pWidget, const QIcon& icon, const QString& strText);

		int AddItem(QWidget* pWidget, const QString& strText, QPixmap& pixIndicatorExpand, QPixmap& pixIndicatorCollapse, QSize indicatorSize);
		int AddItem(QWidget* pWidget, const QIcon& icon, const QString& strText, QPixmap& pixIndicatorExpand, QPixmap& pixIndicatorCollapse, QSize indicatorSize);

        // 插入
        int InsertItem(int iIndex, QWidget* pWidget, const QString& strText);
        int InsertItem(int iIndex, QWidget* pWidget, const QIcon& icon, const QString& strText);

		int InsertItem(int iIndex, QWidget* pWidget, const QString& strText, QPixmap& pixIndicatorExpand, QPixmap& pixIndicatorCollapse, QSize indicatorSize);
		int InsertItem(int iIndex, QWidget* pWidget, const QIcon& icon, const QString& strText, QPixmap& pixIndicatorExpand, QPixmap& pixIndicatorCollapse, QSize indicatorSize);
        // 删除
        void RemoveItem(int iIndex);

    public:
        // 是否可用
        void SetItemEnabled(int iIndex, bool bEnabled);
        bool IsItemEnabled(int iIndex) const;
        // 是否显示
        void SetItemVisible(int iIndex, bool bVisible);
        bool IsItemVisible(int iIndex) const;
        // 文字
        void SetItemText(int iIndex, const QString& strText);
        QString GetItemText(int iIndex) const;
        // 图标
        void SetItemIcon(int iIndex, const QIcon& icon);
        QIcon GetItemIcon(int iIndex) const;
        // 提示
        void SetItemToolTip(int iIndex, const QString& strToolTip);
        QString GetItemToolTip(int iIndex) const;

    public:
        // 通过索引获取窗口
        QWidget* GetWidget(int iIndex) const;
        // 获取添加的窗口在item的索引
        int IndexOf(QWidget* pWidget) const;
        // 获取添加的item数
        int GetItemCount() const;

    public:
        // 设置展开或收缩
        void SetExpandOrCollapseIndex(int iIndex, bool bExpanded);
        void SetExpandOrCollapseWidget(QWidget* pWidget, bool bExpanded);
        // 是否展开
        bool IsExpanded(int iIndex) const;

    signals:
        // 点击操作
        void SignalClickedItem(int iIndex);
        // 点击操作，参数2：当前状态
        void SignalClickedItem(int iIndex, bool bExpanded);
        // 展开或搜索
        void SignalExpandOrCollapse(int iIndex, bool bExpanded);

    protected:
        // 事件改变
        virtual void changeEvent(QEvent* pEvent);

    private:
        QScopedPointer<DSCustomToolBoxPrivate> d_ptr;

    private:
        Q_DECLARE_PRIVATE(DSCustomToolBox)
        Q_DISABLE_COPY(DSCustomToolBox)
        Q_PRIVATE_SLOT(d_func(), void OnButtonClicked())
        Q_PRIVATE_SLOT(d_func(), void OnWidgetDestroyed(QObject*))
    };
}

#endif
