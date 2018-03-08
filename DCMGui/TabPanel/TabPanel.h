#ifndef _DSGUI_TABPANEL_H
#define _DSGUI_TABPANEL_H

#include "DSGuiGlobal.h"
#include "PictureBrowser/PictureBrowser.h"
#include "TabMimeData.h"
#include <QVariant>
#include <QIcon>

namespace DSGUI
{
    class DSTabPanelPrivate;

    typedef struct TabPanel
    {
        QString strPluginId; //当strPluginIdGroupList为空时，strPluginId值表示插件id；当strPluginIdGroupList不为空时，strPluginId值表示组名；
        QStringList strPluginIdGroupList; //标签组包含的插件id
    }TabPanel_t;

    typedef struct TabItemInfo
    {
        QIcon iconItem;
        QString strText;
        QString strPluginID;
    }TabItemInfo_t;

    /**  类名：DSTabPanel
      *  说明  面板标签
     **/
    class DS_GUI_EXPORT DSTabPanel : public DSPictureBrowser
    {
        Q_OBJECT

    public:
        // 构造
        explicit DSTabPanel(QWidget* pParent = NULL);
         ~DSTabPanel();

    public:
        // 设置格子大小
        void SetGridSize(const QSize& szGrid);
        //设置行列数
        void SetRowCol(int nRow, int nCol);
        //设置内容与边框的边距
        void SetMargins(int iLeft, int iTop, int iRight, int iBottom);
        //设置浮层面板
        void SetFloatPanel(DSTabPanel* pFloatPanel);
        //设置浮层item
        void SetFloatItem(QGraphicsItem* pItem);

    public:
        // 添加标签，返回添加的位置
        int AddTab(const QString &strName, const QString &strPluginID, const QVariant& vtUserData = QVariant());
        int AddTab(const QIcon& iconTab, const QString &strName, const QString &strPluginID, const QVariant& vtUserData = QVariant());
        int AddTabGroup(const QList<TabGroup_t>& lsTabGroup, const QString& strGroupName);
        int InsertTabGroup(int iIndex, const QList<TabGroup_t>& lsTabGroup, const QString& strGroupName);
        // 插入标签，返回添加的位置
        int InsertTab(int iIndex, const QString &strName, const QString &strPluginID, const QVariant& vtUserData = QVariant());
        int InsertTab(int iIndex, const QIcon& iconTab, const QString &strName, const QString &strPluginID, const QVariant& vtUserData = QVariant());
        // 删除标签
        void RemoveTab(int iIndex);
        // tab页数量
        int GetTabCount() const;

        // 获取所有tab的ID
        QList<TabPanel_t> GetAllTabPluginID();

        void setRoundMask(int xRnd, int yRnd);

        // 删除所有标签
        void RemoveAllTab();

    public:
        // 标签文字
        QString GetTabText(int iIndex) const;
        void SetTabText(int iIndex, const QString &strTab);
        // 标签图标
        QIcon GetTabIcon(int iIndex) const;
        void SetTabIcon(int iIndex, const QIcon & iconTab);
        //标签描述
        QString GetTabPluginID(int iIndex) const;
        void SetTabPluginID(int iIndex, const QString &strPluginID);
        // 标签tip
        //void SetTabToolTip(int iIndex, const QString & strTip);
        //QString GetTabToolTip(int iIndex) const;
        // 设置自定义数据
        void SetUserData(int iIndex, const QVariant& vtUserData);
        QVariant GetUserData(int iIndex) const;
        // 标签组名
        void SetGroupTabText(const QString& strText);
        QString GetGroupTabText() const;
        
        bool IsCombine(int iIndex);
        void GetItemsInfo(int iIndex, QList<TabItemInfo_t>& lsList) const;
        QString GetGroupName(int iIndex);

    public:
        /** 枚举：TabDirection
         *  说明：布局方式
         **/
        enum TabDirection 
        { 
            LeftToRight = 0,
            //RightToLeft = 1,
            //TopToBottom = 2
        };
        // 布局方式
        /*TabDirection GetTabDirection() const;
        void SetTabDirection(TabDirection enumTabDirection);*/

    public:
        enum DragDropMode
        {
            NoDragDrop     = 0,                   // 无拖拽效果
            DragOnly       = 1,                   // 可拖出
            DropOnly       = 2,                   // 可拖进
            DragDrop       = DragOnly | DropOnly, // 可拖出、拖进
            InternalMove   = 4,                   // 可内部移动
        };
        Q_DECLARE_FLAGS(DragDropModes, DragDropMode)
        
        // 拖拽模式
        void SetDragDropModes(DragDropModes enumModes);
        DragDropModes GetDragDropModes() const;

    public:
        // 设置格子间隔
        void SetSpacing(int iSpacing);
        void SetHSpacing(int iSpacing);
        void SetVSpacing(int iSpacing);
        // 设置边缘间隔
        void SetPanelMargins(int iLeft, int iTop, int iRight, int iBottom);

    Q_SIGNALS:
        // 选中改变
        void SignalClickedTab(QString strPluginID);
        // Tab移动
        void SignalTabMoved(int iFrom, int iTo);
        // 拖拽即将离开
        void SignalAboutDragLeave(int iIndex);
        // 拖出Tab栏信号
        void SignalDragLeave();
        // 插入Tab信号
        void SignalInsertTab();
        // 鼠标悬浮进入
        void SignalHoverEnter(QString strText, bool bCombine);
        // 鼠标悬浮离开
        void SignalHoverLeave();
        // 显示节点组
        void SignalTabPanelGroup();
        // 选中单击
        void SignalPressTab(QString strPluginID);
        // 布局改变
        void SignalLayoutChange();

    protected:
        // 事件处理
        virtual bool eventFilter(QObject *pObject, QEvent *pEvent);
        virtual void resizeEvent(QResizeEvent* pResizeEvent);

    private slots:
        void OnBtnEnter(QString strText, bool bCombine);
        void OnBtnLeave();
        void OnBtnClicked(QGraphicsItem*);
        void OnBtnPress(QGraphicsItem*);
        void OnCheckPageBtn();

    private:
        // 私有数据
        QScopedPointer<DSTabPanelPrivate> d_ptr;

    private:
        Q_DECLARE_PRIVATE(DSTabPanel)
        Q_DISABLE_COPY(DSTabPanel)
        Q_PRIVATE_SLOT(d_func(), void OnPreviousBtnClicked())
        Q_PRIVATE_SLOT(d_func(), void OnNextBtnClicked())

    };
}

Q_DECLARE_OPERATORS_FOR_FLAGS(DSGUI::DSTabPanel::DragDropModes)

#endif
