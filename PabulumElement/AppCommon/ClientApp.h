#pragma once
#include <QSharedMemory>

#include "HomePage/qcontainmanager.h"
#include "HomePage/HomePage.h"
#include "HomePage/qsinglemaindlg.h"

namespace mainApp
{
    class CLoginUI;
    class MaterialRepositoryWidget;
    class MaterialAnalyzeWidget;
}

using namespace mainApp;

class ClientApp : public QObject
{
    Q_OBJECT

public:
    ClientApp();
    ~ClientApp();

    bool isRunning();
    bool initInstance();
    int exitInstance();
    void releaseShareMemory();

public:
    QSingleMainDlg*			m_pMainDlg;
    QContainManager*		m_pContainManager;
    HomePage*			    m_pHomePage;

private:
    void initData();
    bool initModule();
    bool createClientInitCtrl();
    void ClearData();

private slots:
    void onHomePageShow(bool bPopup);
    void onHomePageHide(void);

private:
    QSharedMemory*            m_sharedMen;
    mainApp::CLoginUI*        m_pLoginUi;

    mainApp::MaterialRepositoryWidget* m_pMaterialRepositoryWidget;
    mainApp::MaterialAnalyzeWidget*    m_pMaterialAnalyzeWidget;
};

extern ClientApp theApp;
