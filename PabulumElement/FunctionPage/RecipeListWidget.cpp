#include "RecipeListWidget.h"
#include "HomePage/ViewDefine.h"
#include "ui_RecipeListWidget.h"

namespace mainApp
{

    RecipeListWidget::RecipeListWidget(QWidget* pParent /*= nullptr*/)
        : QWidget(pParent)
        , m_pUi(nullptr)
    {
        m_pUi = new Ui::RecipeListWidget();
        m_pUi->setupUi(this);

        initUI();
        connectSgn();
    }

    RecipeListWidget::~RecipeListWidget()
    {

    }

    void RecipeListWidget::initUI()
    {
        QStringList lstHeader;
        lstHeader << QObject::tr("Recipe") << QObject::tr("Constituent");
        m_model = new QStandardItemModel(0, lstHeader.count());

        m_pUi->m_listViewRecipe->setModel(m_model);
        m_pUi->m_listViewRecipe->setEditTriggers(QAbstractItemView::NoEditTriggers);
        int begin = 0;
        foreach(QString name, lstHeader)
        {
            m_model->setHeaderData(begin, Qt::Horizontal, name);
            m_model->setHeaderData(begin, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
            begin++;
        }
    }

    void RecipeListWidget::connectSgn()
    {

    }

    void RecipeListWidget::createRecipeList(QList<QList<QString>>& listVar)
    {
        QList<recipteData> listData;
        for (int iIndex = 1; iIndex < listVar.size(); iIndex++)
        {
            recipteData data;
            data.strRecipe = listVar[iIndex][Recipe_View_Column_MaterialName - 1];
            data.strValue = listVar[iIndex][Recipe_View_Column_MaterialCount - 1];

            listData.push_back(data);
        }

        m_model->removeRows(0, m_model->rowCount());
        qSort(listData.begin(), listData.end(), &compareBarData);

        for (int iData = 0; iData < listData.size(); iData++)
        {
            int nRow = m_model->rowCount();
            QStandardItem* item = new QStandardItem();
            m_model->insertRow(nRow, item);
            QString strConstituent = listData[iData].strValue + " g";

            m_model->setData(m_model->index(nRow, 0), listData[iData].strRecipe);   // ÅäÁÏ
            m_model->setData(m_model->index(nRow, 1), strConstituent);              // Åä·½
        }
    }

    void RecipeListWidget::resizeEvent(QResizeEvent *event)
    {
        m_pUi->m_listViewRecipe->setColumnWidth(0, this->width() / 2);
    }

}