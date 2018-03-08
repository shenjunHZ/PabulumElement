#include "ClientApp.h"
#include "libdsl/dslbase.h"
#include "libdsl/DPrintLog.h"
#include "Login/LoginUI.h"
#include "FunctionPage/MaterialRepositoryWidget.h"
#include "FunctionPage/MaterialAnalyzeWidget.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

ClientApp theApp;

ClientApp::ClientApp() : m_sharedMen(nullptr)
    , m_pLoginUi(nullptr)
    , m_pContainManager(nullptr)
    , m_pHomePage(nullptr)
    , m_pMainDlg(nullptr)
    , m_pMaterialRepositoryWidget(nullptr)
    , m_pMaterialAnalyzeWidget(nullptr)
{
    initData();
}

ClientApp::~ClientApp()
{
    //SAFE_DELETE(m_pMaterialRepositoryWidget);
    //SAFE_DELETE(m_pMaterialAnalyzeWidget);
}

void ClientApp::initData()
{
    m_sharedMen = new QSharedMemory("pabulum element client app");
}

bool ClientApp::initModule()
{
//     m_pMaterialRepositoryWidget = new mainApp::MaterialRepositoryWidget();
//     m_pPrepareTableWidget = new mainApp::PrepareTableWidget();

    return true;
}

bool ClientApp::createClientInitCtrl()
{
    if (nullptr == m_pLoginUi)
    {
        m_pLoginUi = new mainApp::CLoginUI(); // login interface
    }
    if (m_pLoginUi->init() < 0)
    {
        return false;
    }

    int dlgCode = m_pLoginUi->exec();
    if (QDialog::Rejected == dlgCode)
    {
        return false;
    }
    return true;
}

void ClientApp::ClearData()
{
    //说明：m_pDSSMainDlg在containManager中删除，m_pDSSHomePage在父窗口m_pDSSMainDlg中删除	
    //各模块控件在父窗口m_pDSSMainDlg中销毁	
    SAFE_DELETE(m_pContainManager);

    if (nullptr != m_pLoginUi)
    {
        delete m_pLoginUi;
        m_pLoginUi = nullptr;
    }
}

bool ClientApp::isRunning()
{
    volatile int i = 2;
    while (i--)
    {
        if (m_sharedMen->attach(QSharedMemory::ReadOnly))
        {
            m_sharedMen->detach();
        }
    }

    if (!m_sharedMen->create(1))
    {
        return true;
    }
    return false;
}

bool ClientApp::initInstance()
{
    DLOG_INFO("ClientApp::initInstance:start");
    initModule();

    if (createClientInitCtrl())
    {
        m_pContainManager = new QContainManager();
        connect(m_pContainManager, SIGNAL(sgnHomePageShow(bool)), this, SLOT(onHomePageShow(bool)));
        connect(m_pContainManager, SIGNAL(sgnHomePageHide()),     this, SLOT(onHomePageHide()));
        m_pContainManager->CreateNewWindow(NULL, NULL);

        // create main dialog
        m_pHomePage = new HomePage();
        m_pHomePage->setParent(theApp.m_pMainDlg);
        m_pHomePage->hide();
        if (theApp.m_pMainDlg)
        {
            theApp.m_pMainDlg->SetHomePage(m_pHomePage);
        }

        std::shared_ptr<MysqlDB::CMysqlDB> ptrMysqlDB = m_pLoginUi->getMysqlDB();
        if (nullptr != m_pLoginUi)
        {
            delete m_pLoginUi;
            m_pLoginUi = nullptr;
        }

        m_pMaterialRepositoryWidget = new mainApp::MaterialRepositoryWidget(ptrMysqlDB);
        m_pMaterialAnalyzeWidget = new mainApp::MaterialAnalyzeWidget(ptrMysqlDB);
        m_pHomePage->InitModule(m_pMaterialRepositoryWidget, m_pMaterialAnalyzeWidget);
        m_pHomePage->m_mdBasic->AddButtons();
        m_pMainDlg->_SwitchMaximized();
        m_pHomePage->show();

        connect(m_pMaterialRepositoryWidget, SIGNAL(sgnAddDefinition()), m_pMaterialAnalyzeWidget, SLOT(onUpdateDefinition()));
        connect(m_pMaterialRepositoryWidget, SIGNAL(sgnModifyDefinition()), m_pMaterialAnalyzeWidget, SLOT(onUpdateDefinition()));
        connect(m_pMaterialRepositoryWidget, SIGNAL(sgnModifyDefinition()), m_pMaterialAnalyzeWidget, SLOT(onUpdateDefinition()));

        return true;
    }

    return false;
}

int ClientApp::exitInstance()
{
    ClearData();
    return 0;
}

void ClientApp::releaseShareMemory()
{
    if (m_sharedMen && m_sharedMen->isAttached())
    {
        m_sharedMen->detach();
    }

    SAFE_DELETE(m_sharedMen);
}

void ClientApp::onHomePageShow(bool bPopup)
{
    if (nullptr != m_pHomePage)
    {
        QPoint point;
        point.setX((theApp.m_pMainDlg->width() - m_pHomePage->width()) / 2);
        point.setY((theApp.m_pMainDlg->height() - m_pHomePage->height()) / 2);
        QPoint globPoint = theApp.m_pMainDlg->mapToGlobal(point); // 屏幕座标
        QRect desktopRec = QApplication::desktop()->availableGeometry(m_pHomePage);

        if ((globPoint.y() + m_pHomePage->height() - desktopRec.height()) > 0) // 超出下屏区域
        {
            int gPoint = globPoint.y();
            globPoint.setY(gPoint - (gPoint + m_pHomePage->height() - desktopRec.height()));
        }
        if ((globPoint.x() + m_pHomePage->width() - desktopRec.width()) > 0) // 超出右屏区域
        {
            int gPoint = globPoint.x();
            globPoint.setX(gPoint - (gPoint + m_pHomePage->width() - desktopRec.width()));
        }
        else if (globPoint.x() < 0) // 超出左屏区域
        {
            globPoint.setX(0);
        }
        if (bPopup)
        {
            m_pHomePage->setWindowFlags((m_pHomePage->windowFlags() & ~Qt::Dialog) | Qt::Popup);
            m_pHomePage->move(globPoint);
        }
        else
        {
            point.setY((theApp.m_pMainDlg->height() - m_pHomePage->height() - TOOLBAR_HEIGHT) / 2);
            m_pHomePage->setWindowFlags((m_pHomePage->windowFlags() & ~Qt::Dialog) | Qt::WindowStaysOnTopHint);
            m_pHomePage->move(point);
        }
        m_pHomePage->setFocus(Qt::NoFocusReason);
        m_pHomePage->show();
        m_pHomePage->raise();
    }
}

void ClientApp::onHomePageHide(void)
{
    if (NULL != m_pHomePage && m_pHomePage->isVisible())
    {
        m_pHomePage->hide();
    }
}