#ifndef _DSGUI_TOOLLISTVIEW_H
#define _DSGUI_TOOLLISTVIEW_H

#include "DSGuiGlobal.h"

#include <QFrame>

namespace DSGUI
{
    class DSToolListViewPrivate;

    class DS_GUI_EXPORT DSToolListView : public QFrame
    {
        Q_OBJECT
    public:
        // 构造
        explicit DSToolListView(QWidget* pParent = NULL);
        // 析构
        ~DSToolListView();

    public:
        // 添加
        int AddItem(const QString& strText);
        // 图标支持动态切换，参数1代码实现示例如下：
        // QIcon iconItem;
        // iconItem.addPixmap(QPixmap("normal.png"), QIcon::Normal);
        // iconItem.addPixmap(QPixmap("hover.png"),  QIcon::Active);
        // iconItem.addPixmap(QPixmap("Selected.png"), QIcon::Selected);
        // iconItem.addPixmap(QPixmap("Disabled.png"), QIcon::Disabled);
        int AddItem(const QIcon& icon, const QString& strText);
        // 插入
        int InsertItem(int iIndex, const QString& strText);
        int InsertItem(int iIndex, const QIcon& icon, const QString& strText);
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
        // tooltip
        void SetItemToolTip(int iIndex, const QString& strToolTip);
        QString GetItemToolTip(int iIndex) const;

    public:
        // 获取添加的item数
        int GetItemCount() const;

    public:
        // 设置当前Item
        void SetCurrentIndex(int iIndex);
        // 当前索引
        int GetCurrentIndex() const;

    signals:
        // 点击操作
        void SignalClickedItem(int iIndex);
        // 选中改变
        void SignalCurrentIndexChanged(int iIndex);

    protected:
        // 事件改变
        virtual void changeEvent(QEvent* pEvent);

    private:
        // 私有数据
        QScopedPointer<DSToolListViewPrivate> d_ptr;

    private:
        Q_DECLARE_PRIVATE(DSToolListView)
        Q_DISABLE_COPY(DSToolListView)
        Q_PRIVATE_SLOT(d_func(), void OnButtonClicked())
    };
}

#endif
