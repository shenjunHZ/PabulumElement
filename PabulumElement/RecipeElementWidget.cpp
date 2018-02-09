#include "RecipeElementWidget.h"
#include "ui_RecipeElementWidget.h"
#include "commonControl.h"

const int g_iConstInitial = 0;

namespace mainApp
{

    RecipeElementWidget::RecipeElementWidget(QWidget* pParent /*= nullptr*/)
        : QWidget(pParent)
        , m_pUi(nullptr)
    {
        m_pUi = new Ui::RecipeElementWidget();
        m_pUi->setupUi(this);

        initUI();
        connectSgn();
        SET_MODULE_STYLE_BY_PATH("RecipeElementWidget");
    }

    RecipeElementWidget::~RecipeElementWidget()
    {

    }

    void RecipeElementWidget::initUI()
    {
        QIcon iconItemRecipe;
        iconItemRecipe.addPixmap(QPixmap(commonSpace::GetSkinPath("RecipeElementWidget") + "list_normal.png"), QIcon::Normal);
        iconItemRecipe.addPixmap(QPixmap(commonSpace::GetSkinPath("RecipeElementWidget") + "list_hover.png"), QIcon::Active);
        iconItemRecipe.addPixmap(QPixmap(commonSpace::GetSkinPath("RecipeElementWidget") + "list_pressed.png"), QIcon::Selected);
        m_pUi->m_pToolListView->AddItem(iconItemRecipe, QObject::tr("Recipe Table"));
        m_pUi->m_pToolListView->SetCurrentIndex(g_iConstInitial);

        QIcon iconItemElement;
        iconItemElement.addPixmap(QPixmap(commonSpace::GetSkinPath("RecipeElementWidget") + "list_normal.png"), QIcon::Normal);
        iconItemElement.addPixmap(QPixmap(commonSpace::GetSkinPath("RecipeElementWidget") + "list_hover.png"), QIcon::Active);
        iconItemElement.addPixmap(QPixmap(commonSpace::GetSkinPath("RecipeElementWidget") + "list_pressed.png"), QIcon::Selected);
        m_pUi->m_pToolListView->AddItem(iconItemElement, QObject::tr("Element Table"));

        m_pUi->m_pToolListView->setLineWidth(30);
        m_pUi->funcStackedWidget->setCurrentWidget(m_pUi->m_pRecipeWidget);
    }

    void RecipeElementWidget::connectSgn()
    {
        bool bRet = connect(m_pUi->m_pToolListView, SIGNAL(SignalCurrentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
        connect(m_pUi->m_btnFront, SIGNAL(clicked()), this, SIGNAL(sgnFrontWidget()));
    }

    void RecipeElementWidget::setSelectWidgetType(widgetType_e nType)
    {
        switch (nType)
        {
        case widgetType_e::WIDGET_TYPE_Recipe:
        {
            m_pUi->funcStackedWidget->setCurrentWidget(m_pUi->m_pRecipeWidget);
        }
        break;
        case widgetType_e::WIDGET_TYPE_Element:
        {
            m_pUi->funcStackedWidget->setCurrentWidget(m_pUi->m_pElementWidget);
        }
        break;
        default:
            break;
        }
    }

    void RecipeElementWidget::createData(QList<QList<QString>> listValue)
    {
        m_pUi->m_pRecipeWidget->createRecipeList(listValue);
        m_pUi->m_pElementWidget->createElementList(listValue);
    }

    void RecipeElementWidget::onCurrentIndexChanged(int nIndex)
    {
        setSelectWidgetType((widgetType_e)nIndex);
    }

}