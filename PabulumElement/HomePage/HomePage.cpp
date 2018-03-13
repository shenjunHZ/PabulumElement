#include "HomePage/HomePage.h"
#include "HomePage/QPanelButton.h"
#include "AppCommon/commonControl.h"
#include "FunctionPage/PrepareTableWidget.h"
#include "FunctionPage/MaterialRepositoryWidget.h"
#include "FunctionPage/MaterialAnalyzeWidget.h"

#include <QtWidgets/QHBoxLayout>

#define DSS_HOME_PAGE_WIDTH 650
#define DSS_HOME_PAGE_HIGHT 430

HomePage::HomePage(QWidget *parent /*= 0*/)
    : QDlgSkin(parent)
{
    setWindowFlags((windowFlags() & ~Qt::Dialog) | Qt::Popup | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(DSS_HOME_PAGE_WIDTH, DSS_HOME_PAGE_HIGHT);

    QHBoxLayout* h1 = new QHBoxLayout(this);
    h1->setSpacing(0);
    h1->setContentsMargins(0, 0, 0, 0);
    QWidget* centerWidget = new QWidget(this);
    centerWidget->setObjectName("centerWidget");
    centerWidget->setFixedSize(DSS_HOME_PAGE_WIDTH, DSS_HOME_PAGE_HIGHT);
    h1->addWidget(centerWidget);

    QHBoxLayout* h2 = new QHBoxLayout(centerWidget);
    h2->setSpacing(0);
    h2->setContentsMargins(0, 0, 0, 0);

    m_mdBasic = new QHomeBasic(centerWidget);
    m_mdBasic->setFixedSize(DSS_HOME_PAGE_WIDTH, DSS_HOME_PAGE_HIGHT);
    h2->addWidget(m_mdBasic);

    this->setObjectName("QDSSHomePage");
    SET_MODULE_STYLE_BY_PATH("HomePage");
}

HomePage::~HomePage()
{

}

void HomePage::InitModule(mainApp::MaterialRepositoryWidget* pMaterialRepositoryWidget, mainApp::MaterialAnalyzeWidget* pMaterialAnalyzeWidge)
{
    QPanelButton* pBtn = new QPanelButton(this, QObject::tr("Material Repository"));
    QIcon icon = QIcon(commonSpace::GetSkinPath("HomePage") + "localconfig.png");
    pBtn->load(icon.pixmap(92, 100));
    pBtn->setVisible(true);

    PanelBtnInfoEx_t struPanelBtnInfo;
    PanelBtnInfoList& lsPanelBtnInfo = struPanelBtnInfo.lsPanelBtnInfo;

    PanelBtnInfo_t panelBtnInfo;
    panelBtnInfo.pBtn = pBtn;
    panelBtnInfo.strPluginID = QObject::tr("Material Repository");
    panelBtnInfo.vecWidgetID = "mainApp::MaterialRepositoryWidget"; // class object name
    panelBtnInfo.bRight = true;
    panelBtnInfo.nType = HomeBasic;
    panelBtnInfo.pWidget = pMaterialRepositoryWidget;
    panelBtnInfo.pIcon = new QIcon(commonSpace::GetSkinPath("HomePage") + "BTN_TOOLBAR_LOCALCONFIG_MENU.png");
    lsPanelBtnInfo.push_back(panelBtnInfo);

    m_vecBtnInfo.push_back(struPanelBtnInfo);

    QPanelButton* pBtnRecipe = new QPanelButton(this, QObject::tr("Prepare Table"));
    icon = QIcon(commonSpace::GetSkinPath("HomePage") + "HeatPic.png");
    pBtnRecipe->load(icon.pixmap(92, 100));
    pBtnRecipe->setVisible(true);

    PanelBtnInfoEx_t struPanelBtnInfoRecipe;

    panelBtnInfo.pBtn = pBtnRecipe;
    panelBtnInfo.strPluginID = QObject::tr("Prepare Table");
    panelBtnInfo.vecWidgetID = "mainApp::MaterialAnalyzeWidget";
    panelBtnInfo.bRight = true;
    panelBtnInfo.nType = HomeBasic;
    panelBtnInfo.pWidget = pMaterialAnalyzeWidge;
    panelBtnInfo.pIcon = new QIcon(commonSpace::GetSkinPath("HomePage") + "BTN_TOOLBAR_HEATPIC_MENU.png");
    struPanelBtnInfoRecipe.lsPanelBtnInfo.push_back(panelBtnInfo);

    m_vecBtnInfo.push_back(struPanelBtnInfoRecipe);

    m_mdBasic->SetPanelBtn(m_vecBtnInfo);
    m_mdBasic->SetRowCol(0, 5);
}

void HomePage::mousePressEvent(QMouseEvent * event)
{
    QDlgSkin::mousePressEvent(event);

    QRect rec = geometry();
    QPoint point = event->pos();
    if (point.x() < 0 || point.x() > this->width() || point.y() < 0 || point.y() > this->height())
    {
        hide();
    }
}
