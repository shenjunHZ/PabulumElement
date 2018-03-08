#include "HomePage/qdsstoolbar.h"
#include "HomePage/ViewDefine.h"
#include "AppCommon/commonControl.h"

//#include "qtoolcombo.h"
#include "AppCommon/ClientApp.h"
#include "MessageBox/MessageBox.h"
#include "Tools/Dir.h"

#include <QtGui/QDrag>
#include <QtCore/QPropertyAnimation>
#include <QtWidgets/QStyle>

using namespace DSGUI;

void MoveAnimation(QPanelButton *pTarget, int xBegin, int xEnd, int msecs=200);
void SwapIterator(list<ToolBarItemInfo>::iterator &it1, list<ToolBarItemInfo>::iterator &it2);
bool IsHomePage(QWidget *pWidget);

QDSSToolBar::QDSSToolBar(QDlgSkin *parent,bool bMainDlg)
    : QDlgSkin(parent)
    , m_bMainDlg(bMainDlg)
{
    m_btnMini=NULL;
    m_btnExchange = NULL;
    m_SelectButton = NULL;

    this->setWndMoveable(parent, true);
    this->setAcceptDrops(true);

    //logo
    m_logo =new QLabel(this);
    m_logo->setObjectName("LABEL_LOGO");
    m_logo->setText(QObject::tr("Hang Zhou Heng Mei"));
    m_logo->show();

    // minimum
    m_btnMini = new QPushButton(this);
    m_btnMini->setObjectName("BTN_MINI");
    connect(m_btnMini, SIGNAL(clicked()), this, SLOT(OnBtnMinimize()));
    m_btnMini->setToolTip(tr("Min"));

    // max
    m_btnMax = new QPushButton(this);
    m_btnMax->setObjectName("BTN_REDUCTION");
    connect(m_btnMax, SIGNAL(clicked()), this, SLOT(OnBtnMax()));
    m_btnMax->setToolTip(tr("Normal"));
    // close
    m_btnClose = new QPushButton(this);
    m_btnClose->setObjectName("BTN_CLOSE");
    connect(m_btnClose, SIGNAL(clicked()), this, SIGNAL(sgnWantToClose()));
    m_btnClose->setToolTip(tr("Close"));

    // +
    m_pbtnAddPage = new QPushButton(this);
    m_pbtnAddPage->setObjectName("BTN_AddPAGE");
    m_pbtnAddPage->resize(BTN_AddPAGE_WIDTH, BTN_AddPAGE_HEIGHT);
    m_pbtnAddPage->setDisabled(true);
    connect(m_pbtnAddPage, SIGNAL(clicked()), this, SLOT(OnBtnAddPage()));

    this->setObjectName("QDSSToolBar");
    SET_MODULE_STYLE_BY_PATH("HomePage");
}

QDSSToolBar::~QDSSToolBar()
{
    
}

bool IsHomePage(QWidget *pWidget)
{
    if (pWidget)
    {
        QString strObjectName = pWidget->objectName();
        if (0 == (strcmp(pWidget->objectName().toStdString().c_str(), "DSS_MAIN_PAGE")))
        {
            return true;
        }
    }
    return false;
}

int QDSSToolBar::AddItem(QPanelButton *btnItem, QWidget *SubWidget, int nPos, QIcon menuIcon/* = QIcon()*/, QString menuName/* = ""*/, QString strWidgetID/* = ""*/)
{
    // set front style
    btnItem->SetHighLight(true);
    m_pbtnAddPage->setDisabled(false);

    QPushButton *btnColseOnBtn = nullptr;
    QLabel *pLabel = nullptr;
    if (!IsHomePage(SubWidget))
    {
        btnColseOnBtn = new QPushButton(btnItem);
        btnColseOnBtn->setObjectName("BTN_TOOLBAR_TOP_CLOSE");
        btnColseOnBtn->move(-btnColseOnBtn->width(), -btnColseOnBtn->height());

        connect(btnColseOnBtn, SIGNAL(clicked()), this, SLOT(OnCloseSubWidget()));
    }

    connect(btnItem, SIGNAL(sgnEnter()),                   this, SLOT(OnBtnEnter()));
    connect(btnItem, SIGNAL(sgnLeave()),                   this, SLOT(OnBtnLeave()));
    connect(btnItem, SIGNAL(sgnLeftClicked(QMouseEvent*)), this, SLOT(OnBtnPressed(QMouseEvent*)));
    connect(btnItem, SIGNAL(sgnDbClicked()),               this, SLOT(OnBtnDbClicked()));
    connect(btnItem, SIGNAL(sgnReleased()),                this, SLOT(OnBtnReleased()));
    connect(btnItem, SIGNAL(sgnMove(QMouseEvent*)),        this, SLOT(OnBtnMove(QMouseEvent*)));

    // previous widget hide
    if (m_SelectButton)
    {
        QWidget *pPrevWidget;
        GetWidgetByButton(pPrevWidget);
        if (pPrevWidget)
        {
            pPrevWidget->hide();
        }
        m_SelectButton->SetHighLight(false);
    }
    m_SelectButton = (QPanelButton*)btnItem;
    btnItem->setParent(this);

    // 是主窗口,得加在主页后面
    if (this->parent() == theApp.m_pMainDlg
        && m_lstWidget.size() > 0
        && nPos == 0)
    {
        nPos = 1;
    }

    int nBeginX = BUTTON_BEGINX;
    int nItem = 0;
    list<ToolBarItemInfo>::iterator it = m_lstWidget.begin();
    while (it != m_lstWidget.end() && nItem < nPos)
    {
        int iBtnWidth = it->pBtn->GetBtnWidth();
        nBeginX += iBtnWidth;   

        it++;
        nItem++;
    }

    ToolBarItemInfo info = { btnItem, btnColseOnBtn,/*pLabel,*/ SubWidget, 0, menuIcon, menuName, strWidgetID, btnItem->GetBtnWidth() };
    it = m_lstWidget.insert(it, info);
                               
    while (it != m_lstWidget.end())
    {
        ToolBarItemInfo &info = *it;

        info.pBtn->setGeometry(nBeginX, TOOLBAR_BORDER, info.pBtn->GetBtnWidth(), TOOLBAR_BTN_HEIGHT);
        info.pBtn->show();
        info.nBeginX = nBeginX;
        nBeginX += info.pBtn->GetBtnWidth();
        it++;
    }

    m_pbtnAddPage->move(nBeginX + 20, (TOOLBAR_HEIGHT - BTN_AddPAGE_HEIGHT) / 2);
    return 0;
}

/*
close event the pushbutton of close on toolbar
 */
void QDSSToolBar::OnCloseSubWidget()
{
    QPushButton *btnClose = dynamic_cast<QPushButton*>(sender());
    if(btnClose == NULL)
        return;

    QPanelButton *pTargetBtn = (QPanelButton*)btnClose->parent();
    if(pTargetBtn == NULL)
        return;

    CloseSubWidget(pTargetBtn);
}

void QDSSToolBar::CloseSubWidget(QPanelButton* pTargetBtn)
{
    QSingleMainDlg *Parent = (QSingleMainDlg*)this->parent();

    // main dialog need one widget at least
    if ( strcmp(Parent->objectName().toStdString().c_str(), "DSS_MAIN_DIALOG") == 0)
    {
        if (m_lstWidget.size()<=1)
        {
            return;
        }
    }

    QWidget *closeWidget;
    GetWidgetByButton(closeWidget, pTargetBtn);

    int nDelRemain = theApp.m_pContainManager->RemoveItem((QSingleMainDlg*)this->parent(), pTargetBtn, closeWidget);


    if(nDelRemain == 0  && strcmp(Parent->objectName().toStdString().c_str(), "DSS_MAIN_DIALOG") != 0)
    {
        emit sgnWantToClose();
    }
    else if(0 == nDelRemain && strcmp(Parent->objectName().toStdString().c_str(), "DSS_MAIN_DIALOG") == 0)
    {
        emit sgnHomePageShow(false);
        m_pbtnAddPage->setDisabled(true);
        m_pbtnAddPage->move(BUTTON_BEGINX,(TOOLBAR_HEIGHT-BTN_AddPAGE_HEIGHT)/2);
    }
}

list<ToolBarItemInfo>::iterator QDSSToolBar::GetWidgetByButton(QWidget*& out, QPanelButton *target)
{
    list<ToolBarItemInfo>::iterator it_ret = m_lstWidget.begin();
    out = NULL;

    if (target == NULL)
    {
        target = m_SelectButton;
    }
    if (target)
    {
        while (it_ret != m_lstWidget.end())
        {
            if ((*it_ret).pBtn == target)
            {
                out = (*it_ret).pWidget;
                return it_ret;
            }
            it_ret++;
        }
    }
    return it_ret;
}

void QDSSToolBar::OnBtnMinimize()
{
    theApp.m_pMainDlg->showMinimized();
}

void QDSSToolBar::RemoveSelectItem()
{
    QPanelButton *pTargetBtn = m_SelectButton;
    QWidget *pRmWidget;
    GetWidgetByButton(pRmWidget, pTargetBtn);

    int nDelRemain = theApp.m_pContainManager->RemoveItem((QSingleMainDlg*)this->parent(), pTargetBtn, pRmWidget);
    QSingleMainDlg *Parent = (QSingleMainDlg*)this->parent();
    if(nDelRemain == 0  && strcmp(Parent->objectName().toStdString().c_str(), "DSS_MAIN_DIALOG") != 0)
    {
        emit sgnWantToClose();
    }
    else if(nDelRemain == 0  && strcmp(Parent->objectName().toStdString().c_str(), "DSS_MAIN_DIALOG") == 0)
    {
        emit sgnHomePageShow(false);
        m_pbtnAddPage->setDisabled(true);
        m_pbtnAddPage->move(BUTTON_BEGINX, (TOOLBAR_HEIGHT-BTN_AddPAGE_HEIGHT)/2);
    }
}

/*
 工具条删除某项
 失败:-1
 成功:返回剩余子项个数
 */
int QDSSToolBar::RemoveItem(QPanelButton *btnItem, bool bDeleteBtn, bool bAnimation)
{
    QWidget *delWidget = NULL;
    list<ToolBarItemInfo>::iterator itNow;
    itNow = GetWidgetByButton(delWidget, btnItem);

    if(itNow == m_lstWidget.end()) return -1;

    if (bDeleteBtn) {
        QString strInfor;
    }

    ToolBarItemInfo& info = *itNow;
    int nMoveX = info.nBeginX;
    int nDeletedBtnWidth = btnItem->GetBtnWidth();

    /************delete Strat***********/

    bool bRealDelete = false;

    if(bDeleteBtn) 
    {
        QString name = info.pWidget->metaObject()->className();

        if(theApp.m_pContainManager->WantMoveToTrash(name,info.pBtn,info.pWidget) == 0) 
        {
            info.pBtn->hide();
            info.pWidget->hide();
        } else 
        {
            bRealDelete = true;
        }
    }

    if (bRealDelete == true)
    {
        Q_DELETE(info.pBtnClose)
        /*Q_DELETE(info.pLblLine)*/
        Q_DELETE(info.pBtn)		
        info.pWidget->setParent(theApp.m_pMainDlg);
        info.pWidget->hide();
        //Q_DELETE(info.pWidget)
    }
    else
    {
        // 取消要移动的按钮与当前窗口的信号关联
        disconnect(info.pBtn, SIGNAL(sgnEnter()), this, SLOT(OnBtnEnter()));
        disconnect(info.pBtn, SIGNAL(sgnLeave()), this, SLOT(OnBtnLeave()));
        disconnect(info.pBtn, SIGNAL(sgnLeftClicked(QMouseEvent*)), this, SLOT(OnBtnPressed(QMouseEvent*)));
        disconnect(info.pBtn, SIGNAL(sgnReleased()), this, SLOT(OnBtnReleased()));
        disconnect(info.pBtn, SIGNAL(sgnMove(QMouseEvent*)), this, SLOT(OnBtnMove(QMouseEvent*)));

        Q_DELETE(info.pBtnClose)
        //Q_DELETE(info.pLblLine)

        // 避免被父窗口析构时析构
        info.pBtn->setParent(NULL);
        info.pWidget->setParent(theApp.m_pMainDlg);
    }
    /************delete End***********/

    itNow = m_lstWidget.erase(itNow);
    if(m_lstWidget.size()==0)
    {
        m_SelectButton = NULL; // 此时没有选中button
        return 0;
    }

    QPanelButton *pbtnHight = NULL;
    QWidget *nowWidget = NULL;

    if(itNow == m_lstWidget.end())
    {
        list<ToolBarItemInfo>::iterator itPrev = itNow;
        itPrev--;
        if(itPrev != m_lstWidget.end())
        {
            pbtnHight = (*itPrev).pBtn;
            nowWidget = (*itPrev).pWidget;
        }
    }
    else
    {
        pbtnHight = (*itNow).pBtn;
        nowWidget = (*itNow).pWidget;
    }
    if(m_SelectButton == btnItem)
    {
        if(nowWidget) 
        {
            nowWidget->show();

#ifndef WIN32
            QCommon::QtSendMessage(nowWidget, WM_VIDEO_REFRESH, (ulong)nowWidget, NULL);
#endif
        }
        m_SelectButton = pbtnHight;
        m_SelectButton->SetHighLight(true);
    }

    // 移动按钮
    while(itNow != m_lstWidget.end() )
    {
        ToolBarItemInfo &GetInfo = *itNow;
        if(GetInfo.pBtn->isHidden())
        {
            if( (nMoveX + GetInfo.pBtn->GetBtnWidth()) <= this->width()-/*125*/TOOLBAR_BTN_MARGIN )
            {
                GetInfo.pBtn->show();

                if(bAnimation) // 显示移动动画效果
                    MoveAnimation(GetInfo.pBtn, GetInfo.nBeginX, nMoveX);
                else
                    GetInfo.pBtn->move(nMoveX, GetInfo.pBtn->y());

                GetInfo.nBeginX = nMoveX;

                nMoveX += GetInfo.pBtn->GetBtnWidth();
            }
            
            //itNow++;
            break;
            //定宽的时候只要show一个出来就break；但是现在不定宽不行

        }
        else
        {
            GetInfo.pBtn->show();

            if(bAnimation)  // 显示移动动画效果
                MoveAnimation(GetInfo.pBtn, GetInfo.nBeginX, nMoveX); //向前移动
            else
                GetInfo.pBtn->move(nMoveX, GetInfo.pBtn->y());

            GetInfo.nBeginX = nMoveX;
            nMoveX += GetInfo.pBtn->GetBtnWidth();
            itNow++;
        }
    }


    m_pbtnAddPage->move(nMoveX+20, (TOOLBAR_HEIGHT-BTN_AddPAGE_HEIGHT)/2);
    return m_lstWidget.size();
}

void QDSSToolBar::PopupToolBarItem(const ToolBarItemInfo& item)
{
    if (item.pBtn->isHidden()) {
        theApp.m_pContainManager->RemoveItem((QSingleMainDlg*)this->parent(), item.pBtn, item.pWidget, false, false);
        theApp.m_pContainManager->AddItem((QSingleMainDlg*)this->parent(), item.pBtn, item.pWidget, 0, item.menuIcon, item.menuName, item.strWidgetID);
    } else {
        if(item.pBtn == m_SelectButton)
            return;
        item.pWidget->show();

        QWidget *pPrev;
        GetWidgetByButton(pPrev);
        if(pPrev)
        {
            pPrev->hide();
        }
        m_SelectButton->SetHighLight(false);
        m_SelectButton = item.pBtn;
        m_SelectButton->SetHighLight(true);
    }
}

bool QDSSToolBar::GetSpecialWidget(const QWidget *pWidget)
{
    foreach(ToolBarItemInfo item, m_lstWidget)
    {
        if(item.pWidget != pWidget) {
            continue;
        }
        return true;
    }
    return false;
}

int QDSSToolBar::PopupSpecialWidget(const QString &strWidgetID)
{
    foreach(ToolBarItemInfo item, m_lstWidget)
    {
        QString strClassName = item.pWidget->metaObject()->className();
        if(item.pWidget->metaObject()->className() != strWidgetID) 
        {
            continue;
        }
        PopupToolBarItem(item);
        return 0;
    }
    return -1;
}

int QDSSToolBar::PopupSpecialWidget(const QWidget *pWidget)
{
    foreach(ToolBarItemInfo item, m_lstWidget)
    {
        if(item.pWidget != pWidget) {
            continue;
        }

        PopupToolBarItem(item);
        return 0;
    }
    return -1;
}

void QDSSToolBar::OnBtnMax()
{
    QDlgSkin *pMain = (QDlgSkin*)this->parent();
    if(pMain->_IsMaximized())
    {
        pMain->_SwitchNormal();
        m_btnMax->setObjectName("BTN_MAX");
        m_btnMax->setToolTip(tr("Max"));
        style()->polish(m_btnMax);
        m_btnMax->update();
    }
    else
    {
        pMain->_SwitchMaximized();
        m_btnMax->setObjectName("BTN_REDUCTION");
        m_btnMax->setToolTip(tr("Normal"));
        style()->polish(m_btnMax);
        m_btnMax->update();
    }
}

void QDSSToolBar::OnBtnPressed(QMouseEvent* e)
{
    QPanelButton *pTarget = dynamic_cast<QPanelButton*>(sender());
    if(pTarget == NULL)
        return;

    m_nGlobalX = e->globalX();
    pTarget->raise();
}

/*
 TOOLBAR按钮释放事件
 */
void QDSSToolBar::OnBtnReleased()
{
    QPanelButton *pTarget = dynamic_cast<QPanelButton*>(sender());

    QWidget *pNow;
    list<ToolBarItemInfo>::iterator it = GetWidgetByButton(pNow, pTarget);
    if( it != m_lstWidget.end() && pTarget->x()!= (*it).nBeginX )
    {
        pTarget->move((*it).nBeginX, pTarget->y());
    }

    if(pTarget==m_SelectButton) {
        return;
    }

    if(pNow) 
    {
        pNow->show();
    }


    QWidget *pPrev;
    GetWidgetByButton(pPrev);
    if(pPrev) 
    {
        pPrev->hide();
    }
    m_SelectButton->SetHighLight(false);
    m_SelectButton = pTarget;
    m_SelectButton->SetHighLight(true);
}

/*
 cursor enter
 */
void QDSSToolBar::OnBtnEnter()
{
    QPanelButton *pTarget = dynamic_cast<QPanelButton*>(sender());
    if(pTarget == NULL)
        return;

    if (m_lstWidget.size()<= 1)  //不显示关闭
            return;

    QWidget *pNow;
    list<ToolBarItemInfo>::iterator it = GetWidgetByButton(pNow, pTarget);
    if(pNow && IsHomePage(pNow))
    {
        // 主页不能关闭
        return;
    }
    if(  (*it).pBtnClose != NULL )
    {
        int btnW = (*it).pBtn->width();
        int btnH = (*it).pBtn->height();

        int paintX = btnW - (*it).pBtnClose->width() - 4 - (*it).pBtn->Margin();
        int paintY = (btnH - (*it).pBtnClose->height())/2 ;

        (*it).pBtnClose->move(paintX, paintY);

    }
}

/*
 cursor leave
 */
void QDSSToolBar::OnBtnLeave()
{
    QPanelButton *pTarget = dynamic_cast<QPanelButton*>(sender());
    if(pTarget == NULL)
        return;

    QWidget *pNow;
    list<ToolBarItemInfo>::iterator it = GetWidgetByButton(pNow, pTarget);
    if(pNow != NULL  && (*it).pBtnClose != NULL )
    {
        (*it).pBtnClose ->move(-(*it).pBtnClose->width(),-(*it).pBtnClose->height());
    }
}

/*
 cursor move
 */
void QDSSToolBar::OnBtnMove(QMouseEvent*e)
{
    QPanelButton *button = dynamic_cast<QPanelButton*>(sender());
    QWidget *pWidget;
    list<ToolBarItemInfo>::iterator it = GetWidgetByButton(pWidget, button);
    if(pWidget == NULL || it == m_lstWidget.end())
        return;

    if(IsHomePage(pWidget))
    {
        // homepage can not move
        return;
    }

    if(e->pos().y() < 0 || e->pos().y() > this->height())
    {
        //StartDrag(it);
        return;
    }
    else
    {
        SwitchButton(it, e->globalX());
    }
}

void QDSSToolBar::SwitchButton(list<ToolBarItemInfo>::iterator &itNow, int nMouseX)
{
    QPanelButton *button = (*itNow).pBtn;
    button->move(button->x()+ (nMouseX-m_nGlobalX), button->y());

    if( nMouseX > m_nGlobalX) // 向右滑动
    {
        list<ToolBarItemInfo>::iterator itNext = itNow;
        itNext++;
        if(itNext != m_lstWidget.end() && !(*itNext).pBtn->isHidden())
        {
            if( (button->x() + button->width()) > ((*itNext).nBeginX + (*itNext).pBtn->GetBtnWidth()/2) )
            {
                SwapIterator(itNow,itNext);
                /*MoveAnimation((*itNow).pBtn, (*itNext).nBeginX, (*itNow).nBeginX,200);*/
                MoveAnimation((*itNow).pBtn, (*itNext).nBeginX,(*itNext).nBeginX- (*itNext).pBtn->GetBtnWidth(),200);
           
                //(*itNow).nBeginX = (*itNow).nBeginX;  //itNow的nBeginX不变
                (*itNext).nBeginX = (*itNow).nBeginX + (*itNow).pBtn->GetBtnWidth();
            }
        }
    }
    else  // 向左滑动
    {
        list<ToolBarItemInfo>::iterator itPrev = itNow;
        if (itPrev != m_lstWidget.begin())
        {
            itPrev--;
            if( ! IsHomePage((*itPrev).pWidget) )
            {
                if( button->x() < ((*itPrev).nBeginX + (*itPrev).pBtn->GetBtnWidth()/2) )
                {
                    SwapIterator(itNow,itPrev);
                   /* MoveAnimation((*itNow).pBtn, (*itPrev).nBeginX, (*itNow).nBeginX,200);*/
                    MoveAnimation((*itNow).pBtn, (*itPrev).nBeginX, (*itPrev).nBeginX+ (*itPrev).pBtn->GetBtnWidth(),200);
                    //每个Item里面的btn宽度不一样，交换的时候要重新调，以前定宽不需要考虑 sunyong
                    //(*itPrev).nBeginX = (*itPrev).nBeginX     //prev的nBeginX不变
                    (*itNow).nBeginX = (*itPrev).nBeginX+ (*itPrev).pBtn->GetBtnWidth();
                }
            }
        }
    }
    m_nGlobalX = nMouseX;
}

/*
 */
void QDSSToolBar::resizeEvent(QResizeEvent *e)
{
    QDlgSkin::resizeEvent(e);

    m_logo->move(20,(height()-m_logo->height())/2);

    const int iSpace = 10;
    const int iHeight = 16;
    const int iWidth = 16;
    const int iStartY = (rect().height()-iHeight)/2;
    m_btnClose->setGeometry(this->width()-iWidth-iSpace,iStartY, iWidth, iHeight);
    m_btnMax->setGeometry(m_btnClose->pos().x()-iWidth-iSpace,iStartY, iWidth, iHeight); 

    if (m_btnMini)
    {
        m_btnMini->setGeometry(m_btnMax->pos().x() - iWidth - iSpace, iStartY, iWidth, iHeight);
    }

    int xBegin = BUTTON_BEGINX;

    list<ToolBarItemInfo>::iterator it = m_lstWidget.begin();
    while(it != m_lstWidget.end())
    {
        ToolBarItemInfo &GetInfo = *it;

        {
            GetInfo.pBtn->move(xBegin,GetInfo.pBtn->y());
            GetInfo.nBeginX = xBegin;
            GetInfo.pBtn->show();
            xBegin +=  GetInfo.pBtn->GetBtnWidth();
        }
        it++;
    }


    m_pbtnAddPage->move(xBegin+20, (TOOLBAR_HEIGHT - BTN_AddPAGE_HEIGHT)/2);
}


void MoveAnimation(QPanelButton *pTarget, int xBegin, int xEnd, int msecs)
{
    QPropertyAnimation *anima = new QPropertyAnimation();
    anima->setPropertyName("pos");
    anima->setTargetObject(pTarget);
    anima->setDuration(msecs);
    anima->setStartValue(QPoint(xBegin, pTarget->y()));
    anima->setEndValue(QPoint(xEnd, pTarget->y()));
    anima->start(QAbstractAnimation::DeleteWhenStopped);
}

void SwapIterator(list<ToolBarItemInfo>::iterator &it1, list<ToolBarItemInfo>::iterator &it2)
{
    ToolBarItemInfo infoTemp = *it1;
    (*it1).pBtn = (*it2).pBtn;
    (*it1).pWidget = (*it2).pWidget;
    (*it1).pBtnClose = (*it2).pBtnClose;
    //(*it1).pLblLine = (*it2).pLblLine;
    (*it1).menuIcon = (*it2).menuIcon;
    (*it1).menuName = (*it2).menuName;
    (*it1).strWidgetID = (*it2).strWidgetID;
    (*it1).iItemWidth = (*it2).iItemWidth;

    (*it2).pBtn = infoTemp.pBtn;
    (*it2).pWidget = infoTemp.pWidget;
    (*it2).pBtnClose = infoTemp.pBtnClose;
    //(*it2).pLblLine = infoTemp.pLblLine;
    (*it2).menuIcon = infoTemp.menuIcon;
    (*it2).menuName = infoTemp.menuName;
    (*it2).strWidgetID = infoTemp.strWidgetID;
    (*it2).iItemWidth = infoTemp.iItemWidth;
}

void QDSSToolBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    if ( (event->button()&Qt::LeftButton) == Qt::LeftButton)
    {
        QSingleMainDlg *parent = (QSingleMainDlg*)this->parent();
        if(parent->_IsMaximized())
        {
            parent->_SwitchNormal();
            m_btnMax->setObjectName("BTN_MAX");
            m_btnMax->setToolTip(tr("Max"));
            style()->polish(m_btnMax);
            m_btnMax->update();
        }
        else
        {
            parent->_SwitchMaximized();
            m_btnMax->setObjectName("BTN_REDUCTION");
            m_btnMax->setToolTip(tr("Normal"));
            style()->polish(m_btnMax);
            m_btnMax->update();
        }

    }
}

void QDSSToolBar::OnBtnAddPage(void)
{
    emit sgnHomePageShow(true);
}

void QDSSToolBar::HideBtnAddPage()
{
    m_pbtnAddPage->hide();
}

void QDSSToolBar::OnBtnDbClicked()
{
    QPanelButton *pTarget = dynamic_cast<QPanelButton*>(sender());
    if(pTarget == NULL)
        return;
    
    CloseSubWidget(pTarget);
}

bool QDSSToolBar::ItemCloseable() const
{
    return (m_lstWidget.size()> 1);
}


