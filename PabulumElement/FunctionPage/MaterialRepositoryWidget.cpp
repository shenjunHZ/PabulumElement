#include "FunctionPage/MaterialRepositoryWidget.h"
#include "AppCommon/commonControl.h"
#include "Common/GlobalDataCenter/GlobalDataCenter.h"
#include "SearchEdit/SearchEdit.h"

#include "MessageNotify/MessageNotify.h"
#include "MySQL/MysqlDB.h"
#include "ui_MaterialRepositoryWidget.h"

#include <QtGui/QPixmap>
#include <QtCore/QString>
#include <QtGui/QIcon>
#include <QtWidgets/QDesktopWidget>
#include <iostream>

const int g_iConstInitial = 0;
const int g_iWidthWidow = 803;
const int g_iHeighWidow = 603;

namespace mainApp
{
    MaterialRepositoryWidget::MaterialRepositoryWidget(std::shared_ptr<MysqlDB::CMysqlDB> ptrMysqlDB, QWidget* pParent /*= nullptr*/)
        : DSGUI::DSDialog(pParent/*, CloseButtonHint | MinimizeButtonHint | MaximizeButtonHint*/),
        m_pUi(nullptr),
        m_pMysqlDB(nullptr)
    {
        m_pUi = new Ui::MaterialRepositoryWidget();  // auto delete by parent widget
        m_pUi->setupUi(this->GetCentralWidget());
        this->setAttribute(Qt::WA_TranslucentBackground, false);
        this->setObjectName("MaterialOperationWidget");
        //this->resize(g_iWidthWidow, g_iHeighWidow);
        //this->SetCloseAnimaEnable(true);
        //this->setWindowFlags(windowFlags() | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
        //this->SetOpenDoubleClickTitle(true);

        m_pMysqlDB = ptrMysqlDB;
        // move to middle
        QDesktopWidget* pDeskWidget = QApplication::desktop();
        int iScreen = pDeskWidget->primaryScreen(); // use primary screen for show
        QWidget* pPrimaryScreen = pDeskWidget->screen(iScreen);

        int iWidth = pPrimaryScreen->width();
        int iHeight = pPrimaryScreen->height();
        this->move((iWidth - width()) / 2, (iHeight - height()) / 2);

        InitUI();
        ConnectSgn();
        SET_MODULE_STYLE_BY_PATH("MaterialOperationWidget");
    }

    MaterialRepositoryWidget::~MaterialRepositoryWidget()
    {
        
    }

    bool MaterialRepositoryWidget::createTable()
    {
        if (nullptr == m_pMysqlDB)
        {
            return false;
        }

        return m_pMysqlDB->createTable(QString::fromStdString("MaterialRepositoryTable"));
    }

    void MaterialRepositoryWidget::InitUI()
    {
        m_pUi->m_pSearchWord->setMinimumHeight(40);
        m_pUi->m_pSearchWord->setMinimumWidth(80);

        QIcon iconItemSearch;
        iconItemSearch.addPixmap(QPixmap(commonSpace::GetSkinPath("MaterialOperationWidget") + "search_normal.png"), QIcon::Normal);
        iconItemSearch.addPixmap(QPixmap(commonSpace::GetSkinPath("MaterialOperationWidget") + "search_hover.png"), QIcon::Active);
        iconItemSearch.addPixmap(QPixmap(commonSpace::GetSkinPath("MaterialOperationWidget") + "search_pressed.png"), QIcon::Selected);
        m_pUi->m_pToolListView->AddItem(iconItemSearch, QObject::tr("Search"));
        m_pUi->m_pToolListView->SetCurrentIndex(g_iConstInitial);

        QIcon iconItemAdd;
        iconItemAdd.addPixmap(QPixmap(commonSpace::GetSkinPath("MaterialOperationWidget") + "ADD-n.png"), QIcon::Normal);
        iconItemAdd.addPixmap(QPixmap(commonSpace::GetSkinPath("MaterialOperationWidget") + "ADD-h.png"), QIcon::Active);
        iconItemAdd.addPixmap(QPixmap(commonSpace::GetSkinPath("MaterialOperationWidget") + "ADD-p.png"), QIcon::Selected);
        m_pUi->m_pToolListView->AddItem(iconItemAdd, QObject::tr("Add"));

        m_pUi->m_pSearchWidget->SetAbbreviationTable(m_pMysqlDB);
        m_pUi->m_pAddWidget->SetAbbreviationTable(m_pMysqlDB);

        m_pUi->funcStackedWidget->setCurrentWidget(m_pUi->m_pSearchWidget);
        if (!createTable())
        {
            DSGUI::DSMessageNotify::Instance().AddTextNotification(QObject::tr("read database table failed!"));
        }
    }

    void MaterialRepositoryWidget::ConnectSgn()
    {
        bool bRet = connect(m_pUi->m_pToolListView, SIGNAL(SignalCurrentIndexChanged(int)), this, SLOT(OnCurrentIndexChanged(int)));
        std::cout << "this is for test bRet: " << bRet <<std::endl;

        connect(m_pUi->m_pSearchWord, SIGNAL(SignalSearchBtnClicked(QString&)), this, SLOT(OnSearchBtnClicked(QString&)));
        connect(this,                 SIGNAL(sgnShowNotifyDlg(QString&)),       this, SLOT(OnShowNotifyDlg(QString&)));

        connect(m_pUi->m_pAddWidget,    SIGNAL(sgnAddDefinition()),    this, SIGNAL(sgnAddDefinition()));
        connect(m_pUi->m_pSearchWidget, SIGNAL(sgnModifyDefinition()), this, SIGNAL(sgnModifyDefinition()));
        connect(m_pUi->m_pSearchWidget, SIGNAL(sgnDelDefinition()),    this, SIGNAL(sgnDelDefinition()));
        connect(m_pUi->m_pSearchWidget, SIGNAL(sgnAddComboItem(const std::vector<AbbreviationInfo_s>&)), 
            this, SLOT(onAddComboItem(const std::vector<AbbreviationInfo_s>&)));

        connect(m_pUi->m_comboMaterial, SIGNAL(currentIndexChanged(int)), m_pUi->m_pSearchWidget, SLOT(onCurrentIndexChanged(int)));
    }

    void MaterialRepositoryWidget::SetSelectWidgetType(widgetType_e nType)
    {
        switch (nType)
        {
        case widgetType_e::WIDGET_TYPE_SEARCH:
        {
            m_pUi->funcStackedWidget->setCurrentWidget(m_pUi->m_pSearchWidget);
        }
            break;
        case widgetType_e::WIDGET_TYPE_ADD:
        {
            m_pUi->funcStackedWidget->setCurrentWidget(m_pUi->m_pAddWidget);
        }
            break;
        default:
            break;
        }
    }

    void MaterialRepositoryWidget::OnCurrentIndexChanged(int nIndex)
    {
        SetSelectWidgetType((widgetType_e)nIndex);
    }

    void MaterialRepositoryWidget::OnSearchBtnClicked(QString& strSearchWord)
    {
        m_pUi->m_pToolListView->SetCurrentIndex(g_iConstInitial);
        SetSelectWidgetType(widgetType_e::WIDGET_TYPE_SEARCH);

        m_pUi->m_pSearchWidget->SetAcronymText(strSearchWord);
    }

    void MaterialRepositoryWidget::ShowNotifyDlg(const QString& strNotify) const
    {
        if (!strNotify.isEmpty())
        {
            DSGUI::DSMessageNotify::Instance().AddTextNotification(strNotify);
        }
    }

    void MaterialRepositoryWidget::OnShowNotifyDlg(QString& strNotify)
    {
        ShowNotifyDlg(strNotify);
    }

    void MaterialRepositoryWidget::onAddComboItem(const std::vector<AbbreviationInfo_s>& vecInfo)
    {
        m_pUi->m_comboMaterial->clear();
        for (auto info : vecInfo)
        {
            m_pUi->m_comboMaterial->addItem(QString::fromStdString(info.strAcronym));
        }
    }

} // end namespace mainApp