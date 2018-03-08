#include "AppCommon/ClientApp.h"
#include "AppCommon/commonControl.h"
#include "MessageBox/MessageBox.h"

#include "HomePage/QPanelButton.h"
#include "HomePage/qsinglemaindlg.h"
#include "HomePage/qcontainmanager.h"
#include "HomePage/ViewDefine.h"

#include <libdsl/DPrintLog.h>
#include <QtCore/qstring.h>
#include <QString>

using namespace DSGUI;

QContainManager::QContainManager(QObject *parent)
    : QObject(parent)
{

}

QContainManager::~QContainManager()
{
    QList<TrashObjInfo>::iterator itList;
    QMap< QString, QList<TrashObjInfo> >::iterator itMap = m_mapTrashs.begin();

    while (itMap != m_mapTrashs.end())
    {
        QList<TrashObjInfo> & lstItem = itMap.value();
        itList = lstItem.begin();
        while (itList != lstItem.end())
        {
            Q_DELETE(itList->pBtn);
            Q_DELETE(itList->pWidget);
            itList = lstItem.erase(itList);
        }
        itMap++;
    }
    m_mapTrashs.clear();

}

QSingleMainDlg* QContainManager::CreateNewWindow(QPanelButton *btnItem, QWidget *SubWidget, QIcon menuIcon/* = QIcon()*/, QString menuName/* = ""*/, QString strWidgetID/* = ""*/)
{
    const bool bTheAppMain = (theApp.m_pMainDlg == nullptr);
    QSingleMainDlg *pMainDlg = new QSingleMainDlg(0, bTheAppMain);
    if (pMainDlg == nullptr)
    {
        return nullptr;
    }

    if(bTheAppMain)
    {
        pMainDlg->setObjectName("DSS_MAIN_DIALOG");
        theApp.m_pMainDlg = pMainDlg;
        pMainDlg->setWindowFlags(pMainDlg->windowFlags() | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

        connect(pMainDlg, SIGNAL(sgnHomePageHide()),     this, SIGNAL(sgnHomePageHide()));
        connect(pMainDlg, SIGNAL(sgnHomePageShow(bool)), this, SIGNAL(sgnHomePageShow(bool)));
    }
    else
    {
        pMainDlg->setParent(theApp.m_pMainDlg);
        pMainDlg->setWindowFlags(pMainDlg->windowFlags() | Qt::Dialog);
    }

    // connect.
    connect(pMainDlg, SIGNAL(sgnCloseWindow(QSingleMainDlg*)), this, SLOT(OnCloseWindow(QSingleMainDlg*)));

    // add to list
    m_ContainerList.push_back(pMainDlg);

    AddItem(pMainDlg, btnItem, SubWidget, 0, menuIcon, menuName, strWidgetID);
    
    if (bTheAppMain)
    {
        pMainDlg->hide();		
    }	
    else
    {
        pMainDlg->_Show();
    }
    return pMainDlg;
}

/*
    探测下能否增加一项
    return -1:无法添加 0:可以添加 1:已经存在
*/
int QContainManager::TrytoAddItem(const QString &strClassNa)
{
    if(strClassNa.isEmpty()) 
    {
        return -1;
    }

    QMap<QString, QItemIDManager>::Iterator itMap = m_mapReg.find(strClassNa);
    if(itMap == m_mapReg.end()) 
    {
        return 0;
    } 
    else 
    {
        QItemIDManager &Manager = itMap.value();
        int nRet = Manager.TrytoGetFreeItemID();
        if (nRet == 0) 
        {
            return 0;
        } 
        else 
        {
            return 1;
        }
    }
}

int  QContainManager::AddItem(QSingleMainDlg* target, QPanelButton *btnItem, QWidget *SubWidget, int nPos, QIcon menuIcon/* = QIcon()*/, QString menuName/* = ""*/, QString strWidgetID/* = ""*/)
{
    if( !target || m_ContainerList.indexOf(target) == -1 || ! btnItem || !SubWidget) 
    {
        return -1;
    }

    if(strcmp(target->objectName().toStdString().c_str(), "DSS_MAIN_DIALOG") == 0)
    {
        emit sgnHomePageHide();
    }
    //QString className = SubWidget->metaObject()->className();
    GetFreeItemID(strWidgetID, SubWidget);
    int nAddRet = target->AddItem(btnItem, SubWidget, nPos, menuIcon, menuName, strWidgetID);
    if(nAddRet < 0)
    {
        // TOOLBAR里添加失败,则要回收
        TakebackFreeID(strWidgetID, SubWidget, strWidgetID);
    }
    return nAddRet;
}

/*
  返回剩余TOOLBAR移除按钮后剩余数量
 */
int  QContainManager::RemoveItem(QSingleMainDlg* target, QPanelButton *btnItem, QWidget *SubWidget
                                 , bool bDeleteBtn, bool bAnimation)
{
    if( !target || m_ContainerList.indexOf(target) == -1 || ! btnItem || !SubWidget) {
        return -1;
    }

    QString strWidgetID = GetWidgetID(target, btnItem);

    QWidget *pSaveWidget = SubWidget;
    QString className = pSaveWidget->metaObject()->className();

    int nRmvRet = target->RemoveItem(btnItem, bDeleteBtn, bAnimation);
    if (nRmvRet != -1 && bDeleteBtn)
    {
        // 回收ID
        TakebackFreeID(className, pSaveWidget, strWidgetID);
    }
    return nRmvRet;
}

bool QContainManager::GetSpecialWidget(const QWidget *pWidget)
{
    QList<ToolBarItemInfo> lstGetItemInfo;
    QList<QSingleMainDlg*>::Iterator it = m_ContainerList.begin();

    while(it != m_ContainerList.end())
    {
        QSingleMainDlg *mainDlg = *it;
        if(mainDlg->GetToolBar()->GetSpecialWidget(pWidget))
        {
            return true;
        }
        it++;
    }

    return false;
}

int QContainManager::PopupSpecialWidget(const QString &strWidgetID)
{
    emit sgnHomePageHide();
    
    QList<ToolBarItemInfo> lstGetItemInfo;
    QList<QSingleMainDlg*>::Iterator it = m_ContainerList.begin();

    while(it != m_ContainerList.end())
    {
        QSingleMainDlg *mainDlg = *it;
        if(mainDlg->GetToolBar()->PopupSpecialWidget(strWidgetID) == 0 )
        {
            return 0;
        }
        it++;
    }

    return -1;
}

int QContainManager::PopupSpecialWidget(const QWidget *pWidget)
{
    emit sgnHomePageHide();

    QList<ToolBarItemInfo> lstGetItemInfo;
    QList<QSingleMainDlg*>::Iterator it = m_ContainerList.begin();

    while(it != m_ContainerList.end())
    {
        QSingleMainDlg *mainDlg = *it;
        if(mainDlg->GetToolBar()->PopupSpecialWidget(pWidget) == 0 )
        {
            return 0;
        }
        it++;
    }

    return -1;
}
void QContainManager::AddItemRegulation(const QString &strClassName, int nMaxNum)
{
    QItemIDManager manager(nMaxNum);
    m_mapReg.insert(strClassName, manager);
}
/*
    allocation ID
    return: -1(beyond the allowed number); 0(not find or have exist);
            or return >0 ID
*/
int QContainManager::GetFreeItemID(const QString &strWidgetID, QWidget *pWidget)
{
    QMap<QString, QItemIDManager>::Iterator itMap = m_mapReg.find(strWidgetID);
    if(itMap == m_mapReg.end())
    {
        AddItemRegulation(strWidgetID, 1);
        itMap = m_mapReg.find(strWidgetID);
    }

    QItemIDManager &Manager = itMap.value();
    return Manager.GetFreeItemID(pWidget);
}

int QContainManager::GetFreeItemID(const QString &classNa)
{
    QMap<QString, QItemIDManager>::Iterator itMap = m_mapReg.find(classNa);
    if(itMap == m_mapReg.end())
    {
        AddItemRegulation(classNa, 1);

        itMap = m_mapReg.find(classNa);
    }
    QItemIDManager &Manager = itMap.value();
    return Manager.GetFreeItemID();
}

/*
 回收ID
*/
void QContainManager::TakebackFreeID(const QString &classNa, QWidget *pWidget, const QString& strWidgetID)
{
    QMap<QString, QItemIDManager>::Iterator itMap = m_mapReg.find(classNa);
    if(itMap == m_mapReg.end()) 
    {
        return;
    }
    QItemIDManager &Manager = itMap.value();
    Manager.TakebackFreeID(pWidget);
    //theApp.DealWithModuleClose(strWidgetID);
}

/*
 扔回垃圾桶
*/
int QContainManager::WantMoveToTrash(const QString &name, QPanelButton *button, QWidget *pWidget)
{
    QMap< QString, QList<TrashObjInfo> >::iterator it;
    if ( (it = m_mapTrashs.find(name)) == m_mapTrashs.end() )
    {
        return -1;
    }

    QList<TrashObjInfo>  &lstInfo = it.value();
    TrashObjInfo info = {button, pWidget};
    lstInfo.push_back(info);
    return 0;
}

/*
 从垃圾桶里还原
*/
int QContainManager::RestoreObject(const QString & name, QPanelButton *& button, QWidget *&pWidget)
{
    button = NULL;
    pWidget = NULL;

    QMap< QString, QList<TrashObjInfo> >::iterator it;
    if ( (it = m_mapTrashs.find(name)) == m_mapTrashs.end() )
    {
        return -1;
    }
    QList<TrashObjInfo>  &lstInfo = it.value();
    if (lstInfo.count() == 0) {
        return -1;
    } else {
        const TrashObjInfo & info = *lstInfo.begin();
        button = info.pBtn;
        pWidget = info.pWidget;
        lstInfo.erase(lstInfo.begin());
    }

    return 0;
}

void QContainManager::RegistTrashObj(const QString &name)
{
    m_mapTrashs[name];
}


/*
 关闭一个容器
*/
void QContainManager::OnCloseWindow(QSingleMainDlg* target)
{
    QVector<QSingleMainDlg*> vecForms;

    if(target == theApp.m_pMainDlg) 
    {
        vecForms = m_ContainerList.toVector();
    } 
    else 
    {
        vecForms.push_back(target);
    }

    if (target == theApp.m_pMainDlg) 
    {
        if (DSMessageBox::Ok != DSMessageBox::ShowInformation(target, QObject::tr("Notice"), QObject::tr("are you sure to exit application?"), DSMessageBox::Ok | DSMessageBox::Cancel))
        {
            return;
        }
    }
    DLOG_INFO("CloseWindow");
    ExitContainManage(target);	 
}

void QContainManager::ExitContainManage(QSingleMainDlg* target)
{
    DLOG_INFO("Exit DSSClient");
    m_ContainerList.removeOne(target);

    if(target == theApp.m_pMainDlg) 
    {		
        QList<QSingleMainDlg*>::Iterator it = m_ContainerList.begin();
        while(it != m_ContainerList.end()) 
        {
            QSingleMainDlg *dlg = *it;

            dlg->close();
            Q_DELETE(dlg);
            it++;
        }
        m_ContainerList.clear();

        //target->hide();
        target->close();
        Q_DELETE(target);
    }
    else
    {
        target->close();
        Q_DELETE(target);
    }	
}

bool QContainManager::IsWidgetInToolBar(QString strWidgetID)
{
    QList<QSingleMainDlg*>::Iterator it = m_ContainerList.begin();
    while(it != m_ContainerList.end())
    {
        QSingleMainDlg* pMainDlg = *it;
        if (pMainDlg != NULL
            && pMainDlg->IsWidgetInToolBar(strWidgetID))
        {
            return true;
        }
        it++;
    }

    return false;
}


QString QContainManager::GetWidgetID(QSingleMainDlg* target, QPanelButton* pBtn)
{
    foreach(ToolBarItemInfo item, target->GetToolBar()->m_lstWidget)
    {
        if(item.pBtn == pBtn)
        {
            return item.strWidgetID;
        }
    }	

    return "";
}
