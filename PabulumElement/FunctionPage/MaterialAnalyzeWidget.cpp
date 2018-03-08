#include "MaterialAnalyzeWidget.h"
#include "ui_MaterialAnalyzeWidget.h"

#include <QtWidgets/QDesktopWidget>

const int g_iWidthWidow = 803;
const int g_iHeighWidow = 603;

namespace mainApp 
{
    MaterialAnalyzeWidget::MaterialAnalyzeWidget(std::shared_ptr<MysqlDB::CMysqlDB> ptrMysqlDB, QWidget* pParent /*= nullptr*/)
        : DSGUI::DSDialog(pParent/*, CloseButtonHint | MinimizeButtonHint | MaximizeButtonHint*/)
        , m_pUi(nullptr)
        , m_pPrepareTableWidget()
        , m_pRecipeElementWidget()
        , m_pMysqlDB(nullptr)
    {
        m_pUi = new Ui::MaterialAnalyzeWidget();
        m_pUi->setupUi(this->GetCentralWidget());
        setAttribute(Qt::WA_StyledBackground);
        m_pMysqlDB = ptrMysqlDB;

        //this->setAttribute(Qt::WA_TranslucentBackground, false);
        //this->resize(g_iWidthWidow, g_iHeighWidow);

        //QFont font = this->font();
        //font.setPixelSize(16);
        //this->setFont(font);
        //int pixSize = font.pixelSize();
        //int pointSize = font.pointSize();

        this->setObjectName("MaterialAnalyzeWidget");
        //this->SetCloseAnimaEnable(true);
        //this->setWindowFlags(windowFlags() | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
        //this->SetOpenDoubleClickTitle(true);

        // move to middle
        QDesktopWidget* pDeskWidget = QApplication::desktop();
        int iScreen = pDeskWidget->primaryScreen(); // use primary screen for show
        QWidget* pPrimaryScreen = pDeskWidget->screen(iScreen);

        int iWidth = pPrimaryScreen->width();
        int iHeight = pPrimaryScreen->height();
        this->move((iWidth - width()) / 2, (iHeight - height()) / 2);

        m_pUi->funcStackedWidget->setCurrentWidget(m_pUi->m_pPrepareTableWidget);
        m_pPrepareTableWidget = m_pUi->m_pPrepareTableWidget;
        m_pRecipeElementWidget = m_pUi->m_pRecipeElementWidget;
        m_pPrepareTableWidget->SetAbbreviationTable(m_pMysqlDB);

        m_pPrepareTableWidget->setRecipeElementWidget(m_pRecipeElementWidget);
        connectSgn();
    }

    MaterialAnalyzeWidget::~MaterialAnalyzeWidget()
    {
        m_pPrepareTableWidget = nullptr;
        m_pRecipeElementWidget = nullptr;
    }

    void MaterialAnalyzeWidget::connectSgn()
    {
        connect(m_pUi->m_pPrepareTableWidget,  SIGNAL(sgnNextWidget()),   this, SLOT(onNextWidget()));
        connect(m_pUi->m_pRecipeElementWidget, SIGNAL(sgnFrontWidget()),  this, SLOT(onFrontWidget()));
        connect(m_pRecipeElementWidget,        SIGNAL(sgnExport()),       m_pPrepareTableWidget, SLOT(onExport()));
    }

    void MaterialAnalyzeWidget::onNextWidget()
    {
        m_pUi->funcStackedWidget->setCurrentWidget(m_pUi->m_pRecipeElementWidget);
    }

    void MaterialAnalyzeWidget::onFrontWidget()
    {
        m_pUi->funcStackedWidget->setCurrentWidget(m_pUi->m_pPrepareTableWidget);
    }

    void MaterialAnalyzeWidget::onUpdateDefinition()
    {
        if (nullptr != m_pPrepareTableWidget)
        {
            m_pPrepareTableWidget->SetAbbreviationTable(m_pMysqlDB);
        }
    }

}