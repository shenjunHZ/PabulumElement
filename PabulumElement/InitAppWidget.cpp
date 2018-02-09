#include "InitAppWidget.h"
#include "ui_InitAppWidget.h"

#include <QtWidgets/QDesktopWidget>

const int g_iWidthWidow = 803;
const int g_iHeighWidow = 603;

namespace mainApp 
{
    InitAppWidget::InitAppWidget(QWidget* pParent /*= nullptr*/)
        : DSGUI::DSDialog(pParent, CloseButtonHint | MinimizeButtonHint | MaximizeButtonHint)
        , m_pUi(nullptr)
        , m_pMainAppWidget(nullptr)
        , m_pRecipeElementWidget(nullptr)
    {
        m_pUi = new Ui::InitAppWidget();
        m_pUi->setupUi(this->GetCentralWidget());
        setAttribute(Qt::WA_StyledBackground);

        this->setAttribute(Qt::WA_TranslucentBackground, false);
        this->resize(g_iWidthWidow, g_iHeighWidow);
        this->SetTitle(QObject::tr("hang zhou heng mei"));

        QFont font = this->font();
        font.setPixelSize(16);
        this->setFont(font);
        //int pixSize = font.pixelSize();
        //int pointSize = font.pointSize();

        this->setObjectName("InitAppWidget");
        this->SetCloseAnimaEnable(true);
        this->setWindowFlags(windowFlags() | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
        this->SetOpenDoubleClickTitle(true);

        // move to middle
        QDesktopWidget* pDeskWidget = QApplication::desktop();
        int iScreen = pDeskWidget->primaryScreen(); // use primary screen for show
        QWidget* pPrimaryScreen = pDeskWidget->screen(iScreen);

        int iWidth = pPrimaryScreen->width();
        int iHeight = pPrimaryScreen->height();
        this->move((iWidth - width()) / 2, (iHeight - height()) / 2);

        m_pUi->funcStackedWidget->setCurrentWidget(m_pUi->m_pMainAppWidget);
        m_pMainAppWidget = m_pUi->m_pMainAppWidget;
        m_pRecipeElementWidget = m_pUi->m_pRecipeElementWidget;

        m_pMainAppWidget->setRecipeElementWidget(m_pRecipeElementWidget);
        connectSgn();
    }

    InitAppWidget::~InitAppWidget()
    {
        m_pMainAppWidget = nullptr;
        m_pRecipeElementWidget = nullptr;
    }

    void InitAppWidget::connectSgn()
    {
        connect(m_pUi->m_pMainAppWidget,       SIGNAL(sgnNextWidget()),   this, SLOT(onNextWidget()));
        connect(m_pUi->m_pRecipeElementWidget, SIGNAL(sgnFrontWidget()),  this, SLOT(onFrontWidget()));
    }

    void InitAppWidget::onNextWidget()
    {
        m_pUi->funcStackedWidget->setCurrentWidget(m_pUi->m_pRecipeElementWidget);
    }

    void InitAppWidget::onFrontWidget()
    {
        m_pUi->funcStackedWidget->setCurrentWidget(m_pUi->m_pMainAppWidget);
    }

}