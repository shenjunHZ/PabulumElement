#ifndef QCONTAINMANAGER_H
#define QCONTAINMANAGER_H

#include "HomePage/qsinglemaindlg.h"

#include <QObject>
#include <set>

using std::set;
typedef struct
{
    QPanelButton *pBtn;
    QWidget *pWidget;
}TrashObjInfo;

//*************** 工具条显示子项个数管理类 *************/
class QItemIDManager
{
public:
    QItemIDManager();
    QItemIDManager(int nNum)
    {
        m_nMaxNum = nNum;
    }

    int TrytoGetFreeItemID()
    {
        return ((m_mapWidgetID.count() >= m_nMaxNum) ? -1:0);
    }

    int GetFreeItemID(QWidget *pWidget)
    {
        if(m_mapWidgetID.find(pWidget) != m_mapWidgetID.end()) 
        {
            // have exist
            return 0;
        } 
        else if (m_mapWidgetID.count() >= m_nMaxNum) 
        {
            return -1;
        }

        set<int> setAllocId;

        for(int i=1; i <= m_nMaxNum; i++)
            setAllocId.insert(i);
        foreach(int id, m_mapWidgetID.values())
            setAllocId.erase(id);

        if(setAllocId.size() > 0) 
        {
            int nRetId = *(setAllocId.begin());
            m_mapWidgetID.insert(pWidget, nRetId);
            return (m_nMaxNum==1) ? 0 : nRetId;
        }
        else 
        {
            return -1;
        }
    }

    //需找可用的ID，并不插入
    int GetFreeItemID()
    {
        if (m_mapWidgetID.count() >= m_nMaxNum) 
        {
            return -1;
        }

        set<int> setAllocId;

        for(int i=1; i <= m_nMaxNum; i++)
            setAllocId.insert(i);
        foreach(int id, m_mapWidgetID.values())
            setAllocId.erase(id);

        if(setAllocId.size() > 0) {
            int nRetId = *(setAllocId.begin());
            return (m_nMaxNum==1) ? 0 : nRetId;
        }
        else {
            return -1;
        }
    }

    void TakebackFreeID(QWidget *pWidget)
    {
        QMap<QWidget*, int>::Iterator it = m_mapWidgetID.find(pWidget);
        if(it == m_mapWidgetID.end()) 
        {
            // 不存在
            return;
        }
        m_mapWidgetID.erase(it);
    }

private:
    QMap<QWidget*, int> m_mapWidgetID;
    int m_nMaxNum;
};


class QContainManager : public QObject
{
    Q_OBJECT

public:
    explicit QContainManager(QObject *parent = 0);
    virtual ~QContainManager();

    QSingleMainDlg* CreateNewWindow(QPanelButton *btnItem, QWidget *SubWidget, QIcon menuIcon = QIcon(), QString menuName = "", QString strWidgetID = "");
    int TrytoAddItem(const QString &strClassNa);
    int AddItem(QSingleMainDlg* target, QPanelButton *btnItem, QWidget *SubWidget, int nPos = 0, QIcon menuIcon = QIcon(), QString menuName = "", QString strWidgetID = "");
    int RemoveItem(QSingleMainDlg* target, QPanelButton *btnItem, QWidget *SubWidget, bool bDeleteBtn = true, bool bAnimation = true);

    void AddItemRegulation(const QString &strClassName, int nMaxNum);
    void TakebackFreeID(const QString &classNa, QWidget *pWidget, const QString& strWidgetID);
    int  PopupSpecialWidget(const QString &strWidgetID);
    bool GetSpecialWidget(const QWidget *pWidget);
    int  PopupSpecialWidget(const QWidget *pWidget);

    // 扔回垃圾桶,不是谁都能回收的,必须注册
    int WantMoveToTrash(const QString &name,QPanelButton *button,QWidget *pWidget);
    int RestoreObject(const QString &name,QPanelButton *&button,QWidget *&pWidget);
    void RegistTrashObj(const QString &name);
    //
    int GetFreeItemID(const QString &strWidgetID, QWidget *pWidget);
    //需找可用的ID，并不插入
    int GetFreeItemID(const QString &classNa);
    void ExitContainManage(QSingleMainDlg*target);
    bool IsWidgetInToolBar(QString strWidgetID);

private:
    //int TakeBackFormDragMDlg(QSingleMainDlg*target);
    QString GetWidgetID(QSingleMainDlg* target, QPanelButton* pBtn);
private:
    QList<QSingleMainDlg*> m_ContainerList;
    QMap<QString, QItemIDManager> m_mapReg;
    QMap< QString, QList<TrashObjInfo> > m_mapTrashs;

signals:
    void sgnHomePageShow(bool bPopup);
    void sgnHomePageHide();

public slots:
    void OnCloseWindow(QSingleMainDlg*);
    
};

#endif // QCONTAINMANAGER_H
