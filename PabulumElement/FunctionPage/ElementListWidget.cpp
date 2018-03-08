#include "ElementListWidget.h"
#include "HomePage/ViewDefine.h"
#include "ui_ElementListWidget.h"

namespace mainApp
{

    ElementListWidget::ElementListWidget(QWidget* pParent /*= nullptr*/)
        : QWidget(pParent)
        , m_pUi(nullptr)
        , m_strValue("")
        , m_model(nullptr)
    {
        m_pUi = new Ui::ElementListWidget();
        m_pUi->setupUi(this);

        initUI();
        connectSgn();
    }

    ElementListWidget::~ElementListWidget()
    {

    }

    void ElementListWidget::initUI()
    {
        QStringList lstHeader;
        lstHeader << QObject::tr("Project") << QObject::tr("Each(") + m_strValue + " g)"<<QObject::tr("pabulum reference");
        m_model = new QStandardItemModel(0, lstHeader.count());

        m_pUi->m_listViewElement->setModel(m_model);
        int begin = 0;
        foreach(QString name, lstHeader)
        {
            m_model->setHeaderData(begin, Qt::Horizontal, name);
            m_model->setHeaderData(begin, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
            begin++;
        }
    }

    void ElementListWidget::refreshHeaderData()
    {
        QStringList lstHeader;
        lstHeader << QObject::tr("Project") << QObject::tr("Each(") + m_strValue + " g)" << QObject::tr("pabulum reference");

        int begin = 0;
        foreach(QString name, lstHeader)
        {
            m_model->setHeaderData(begin, Qt::Horizontal, name);
            m_model->setHeaderData(begin, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
            begin++;
        }
    }

    void ElementListWidget::connectSgn()
    {

    }

    // list(MaterialCode    MaterialName    Recipe    Price)
    void ElementListWidget::createElementList(QList<QList<QString>>& listVar)
    {
        if (listVar.isEmpty())
        {
            return;
        }
        m_model->removeRows(0, m_model->rowCount());
        //float eachPer = 0.0;          // 总成分
        //QList<QString> listElement;   // 蛋白质、脂肪..
        m_listElement.clear();
        //QList<float> listConstituent; // 含量列表
        m_listConstituent.clear();

                                      // each element e.g. protein etc
        bool bFistElement = true;
        for (int iElement = Recipe_View_Column_MaterialCount + 1; iElement < listVar[0].size(); iElement++)
        {
            m_listElement.push_back(listVar[0][iElement]);

            float fTempConstituent = 0.0; // 原料成分
                                          // 配料
            for (int iIndex = 1; iIndex < listVar.size(); iIndex++) // the first row is headline
            {
                fTempConstituent += listVar[iIndex][Recipe_View_Column_MaterialCount - 1].toFloat() * listVar[iIndex][iElement].toFloat() / 100;

                if (bFistElement)
                {
                    m_eachPer += listVar[iIndex][Recipe_View_Column_MaterialCount - 1].toFloat();
                }
            }
            bFistElement = false;
            m_listConstituent.push_back(fTempConstituent);
        }

        m_strValue = QString("%1").arg(m_eachPer);
        refreshHeaderData();
        addElementToList(m_listElement, m_listConstituent, m_eachPer);
    }

    void ElementListWidget::addElementToList(QList<QString>& listElement, QList<float>& listConstituent, float& eachPer)
    {
        for (int iIndex = 0; iIndex < listElement.size() && iIndex < listConstituent.size(); iIndex++)
        {
            int nRow = m_model->rowCount();
            QStandardItem* item = new QStandardItem();
            m_model->insertRow(nRow, item);
            m_model->setData(m_model->index(nRow, 0), listElement[iIndex]);  // 

            QString strUnit = QObject::tr("g");
            float fElementReference = listConstituent[iIndex];
            if (fElementReference < 0.001)
            {
                fElementReference *= 1000 * 1000;
                strUnit = QObject::tr("ug");
            }
            else if (fElementReference < 1)
            {
                fElementReference *= 1000;
                strUnit = QObject::tr("mg");
            }
            QString strTempConstituent = QString("%1").arg(fElementReference);
            m_model->setData(m_model->index(nRow, 1), strTempConstituent + strUnit);  // 成分值

            QString strPercent = "";
            if (eachPer > 0.000001)
            {
                strPercent = QString("%1%2").arg(listConstituent[iIndex] / eachPer * 100).arg("%");
                m_model->setData(m_model->index(nRow, 2), strPercent);  // 成分百分比例
            }
        }
    }

    void ElementListWidget::resizeEvent(QResizeEvent *event)
    {
        m_pUi->m_listViewElement->setColumnWidth(0, this->width() / 3);
        m_pUi->m_listViewElement->setColumnWidth(1, this->width() / 3);
    }

    void ElementListWidget::getElementListData(QList<QString>& listElement, QList<float>& listConstituent, float& eachPer)
    {
        listElement = m_listElement;
        listConstituent = m_listConstituent;
        eachPer = m_eachPer;
    }

}