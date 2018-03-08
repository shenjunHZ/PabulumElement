#include "HomePage/qsinglemaindlg.h"
#include "HomePage/ViewDefine.h"

#include "AppCommon/commonControl.h"
#include "AppCommon/ClientApp.h"
#include "Tools/Dir.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

QSingleMainDlg::QSingleMainDlg(QWidget *parent,bool bMain)
    :QDlgSkin(parent)
    , m_bQuit(false)
    , m_pMainPage(NULL)
    , m_bMainDlg(bMain)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_pBg = new QWidget(this);
    m_pBg->setObjectName("QSingleMainDlgBg");
    m_pBg->setGeometry(0, 0, this->width(),this->height());

    m_pBg->show();
    m_SkinSettings.m_dlgSize = QSize(1024, 768);

    m_toolBar = new QDSSToolBar(this, m_bMainDlg);
    connect(m_toolBar, SIGNAL(sgnWantToClose()),      this, SLOT(OnCloseWindow()));
    connect(m_toolBar, SIGNAL(sgnHomePageShow(bool)), this, SIGNAL(sgnHomePageShow(bool)));
    
    m_toolBar->resize(1280, TOOLBAR_HEIGHT);

    this->setObjectName("QSingleMainDlg");

    SET_MODULE_STYLE_BY_PATH("HomePage");
}

QSingleMainDlg::~QSingleMainDlg()
{
    delete m_toolBar;
    m_toolBar = NULL;
}

void QSingleMainDlg::SetHomePage(QWidget *pHomePage)
{
    m_pMainPage = pHomePage;
}

void QSingleMainDlg::_SwitchMaximized()
{
    QDlgSkin::_SwitchMaximized();
}

bool QSingleMainDlg::close()
{
    m_bQuit = true;
    return QDlgSkin::close();
}

 void QSingleMainDlg::closeEvent(QCloseEvent * event)
 {
     if (!m_bQuit)
     {
         event->ignore();
         emit sgnCloseWindow(this);
     }
     else
         QDlgSkin::closeEvent(event);
 }

QDSSToolBar* QSingleMainDlg::GetToolBar()
{
    return m_toolBar;
}

int QSingleMainDlg::AddItem(QPanelButton *btnItem, QWidget *SubWidget, int nPos, QIcon menuIcon/* = QIcon()*/, QString menuName/* = ""*/, QString strWidgetID/* = ""*/)
{
    if (!btnItem || !SubWidget)
    {
        return -1;
    }
    if(0 != (strcmp(SubWidget->objectName().toStdString().c_str(), "DSS_MAIN_PAGE"))) 
    {
        m_toolBar->AddItem(btnItem, SubWidget, nPos, menuIcon, menuName, strWidgetID);	
    }
    else
    {
        m_pMainPage = SubWidget;
    }
    if(0 != strcmp(this->objectName().toStdString().c_str(), "DSS_MAIN_DIALOG")) 
    {
        m_toolBar->HideBtnAddPage();
    }

    SubWidget->setAcceptDrops(true);//FIXME: 这样把drop的范围扩大了，鼠标状态在其他地方也显示可接受的图标
    SubWidget->setParent(this);
    SubWidget->setGeometry(0, m_toolBar->height(), this->width(), this->height()-m_toolBar->height());
    SubWidget->show();
    SubWidget->setFocus(Qt::NoFocusReason);
    SubWidget->activateWindow();
    
    return 0;
}

void QSingleMainDlg::resizeEvent(QResizeEvent *e)
{
    QDlgSkin::resizeEvent(e);
    this->setMask(m_ImgBkgrnd.mask());

    m_toolBar->setGeometry(0, 0, this->width(), m_toolBar->height());
    m_pBg->setGeometry(0, 0, this->width(),this->height());

    foreach(ToolBarItemInfo item, m_toolBar->m_lstWidget)
    {
        if(item.pWidget != NULL)
        {
            item.pWidget->resize(this->width(), this->height()- m_toolBar->height());
        }
    }
    
    if(NULL != m_pMainPage && m_pMainPage->isVisible())
    {
        QPoint point;
        point.setX((width() - m_pMainPage->width())/2);
        point.setY((height() - TOOLBAR_HEIGHT - m_pMainPage->height())/2);
        
        m_pMainPage->move(point);
    }
}

int QSingleMainDlg::RemoveItem(QPanelButton *btnItem, bool bDeleteBtn, bool bAnimation)
{
    if(!btnItem)
        return -1;

    int nRemain = m_toolBar->RemoveItem(btnItem, bDeleteBtn, bAnimation);
    return nRemain;
}

void QSingleMainDlg::OnCloseWindow()
{
    // other action
    // notify contain manager
    emit sgnCloseWindow(this);
}

bool QSingleMainDlg::IsWidgetInToolBar(QString strWidgetID)
{
    foreach(ToolBarItemInfo item, m_toolBar->m_lstWidget)
    {
        if (item.strWidgetID.compare(strWidgetID) == 0)
        {
            return true;
        }
    }

    return false;
}

void QSingleMainDlg::_SwitchNormal()
{
    /*QDlgSkin::_SwitchNormal();*/

    m_bIsMax = false;
    QSize wndSize = GetWndRealSize();
    QRect desktopRec = QApplication::desktop()->availableGeometry(this);
    int wDesktop = desktopRec.width();
    int hDesktop = desktopRec.height();
    int x = (wDesktop - wndSize.width())/2;
    int y = (hDesktop - wndSize.height())/2;
    this->setGeometry(QRect(QPoint(x,y), GetWndRealSize()));

    if(this->isHidden())
    {
        this->show();
    }

}




