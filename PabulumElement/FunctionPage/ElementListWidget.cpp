#include "ElementListWidget.h"
#include "ui_ElementListWidget.h"

constexpr int ELEMENTCOLUMN = 0;
constexpr int CONTENTCOLUMN = 2;
constexpr int NRVCOLUMN = 3;

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
        targetTable = {
            { QObject::tr("energy"),{ QObject::tr("kj"), 1.0f,   17.0f } },
            { QObject::tr("protein"),{ QObject::tr("g"),  0.1f, 0.5f } },
            { QObject::tr("fat"),{ QObject::tr("g"),  0.1f, 0.5f } },
            { QObject::tr("saturated fat"),{ QObject::tr("g"),  0.1f, 0.1f } },
            { QObject::tr("trans fat"),{ QObject::tr("g"),  0.1f, 0.3f } },
            { QObject::tr("monounsaturated fatty fat"),{ QObject::tr("g"),  0.1f, 0.1f } },
            { QObject::tr("polyunsaturated fatty fat"),{ QObject::tr("g"),  0.1f, 0.1f } },
            { QObject::tr("cholesterol"),{ QObject::tr("mg"), 1.0f,   5.0f } },
            { QObject::tr("carbohydrate"),{ QObject::tr("g"),  0.1f, 0.5f } },
            { QObject::tr("sugar"),{ QObject::tr("g"),  0.1f, 0.5f } },
            { QObject::tr("dietary fiber"),{ QObject::tr("g"),  0.1f, 0.5f } },
            { QObject::tr("sodium"),{ QObject::tr("mg"), 1.0f,   5.0f } },
            { QObject::tr("vitamin A"),{ QObject::tr("ug"), 1.0f,   8.0f } },
            { QObject::tr("vitamin D"),{ QObject::tr("ug"), 0.1f, 0.1f } },
            { QObject::tr("vitamin E"),{ QObject::tr("mg"), 0.01f, 0.28f } },
            { QObject::tr("vitamin K"),{ QObject::tr("ug"), 0.1f,  1.6f } },
            { QObject::tr("vitamin B1"),{ QObject::tr("mg"), 0.01f, 0.03f } },
            { QObject::tr("vitamin B2"),{ QObject::tr("mg"), 0.01f, 0.03f } },
            { QObject::tr("vitamin B6"),{ QObject::tr("mg"), 0.01f, 0.03f } },
            { QObject::tr("vitamin B12"),{ QObject::tr("ug"), 0.01f, 0.05f } },
            { QObject::tr("vitamin C"),{ QObject::tr("mg"), 0.1f,  2.0f } },
            { QObject::tr("niacin"),{ QObject::tr("mg"), 0.01f, 0.28f } },
            { QObject::tr("folic acid"),{ QObject::tr("ug"), 1.0f,    8.0f } },
            { QObject::tr("pantothenic acid"),{ QObject::tr("mg"), 0.01, 0.10 } },
            { QObject::tr("biotin"),{ QObject::tr("ug"), 0.1f,  0.6f } },
            { QObject::tr("choline"),{ QObject::tr("mg"), 0.1f,  9.0f } },
            { QObject::tr("phosphorus"),{ QObject::tr("mg"), 1.0f,    14.0f } },
            { QObject::tr("potassium"),{ QObject::tr("mg"), 1.0f,    20.0f } },
            { QObject::tr("magnesium"),{ QObject::tr("mg"), 1.0f,    6.0f } },
            { QObject::tr("calcium"),{ QObject::tr("mg"), 1.0f,    8.0f } },
            { QObject::tr("iron"),{ QObject::tr("mg"), 0.1f,  0.3f } },
            { QObject::tr("zinc"),{ QObject::tr("mg"), 0.01f, 0.30f } },
            { QObject::tr("iodine"),{ QObject::tr("ug"), 0.1f,  3.0f } },
            { QObject::tr("selenium"),{ QObject::tr("ug"), 0.1f,  1.0f } },
            { QObject::tr("copper"),{ QObject::tr("mg"), 0.01f, 0.03f } },
            { QObject::tr("fluorine"),{ QObject::tr("mg"), 0.01f, 0.02f } },
            { QObject::tr("manganese"),{ QObject::tr("mg"), 0.01f, 0.06f } }
        };
        valueTable = {
            { QObject::tr("energy"),           8400.0f },
            { QObject::tr("protein"),          60.0f },
            { QObject::tr("fat"),              60.0f },
            { QObject::tr("saturated fat"),    20.0f },
            { QObject::tr("cholesterol"),      300.0f },
            { QObject::tr("carbohydrate"),     300.0f },
            { QObject::tr("dietary fiber"),    25.0f },
            { QObject::tr("vitamin A"),        800.0f },
            { QObject::tr("vitamin D"),        5.0f },
            { QObject::tr("vitamin E"),        14.0f },
            { QObject::tr("vitamin K"),        80.0f },
            { QObject::tr("vitamin B1"),       1.4f },
            { QObject::tr("vitamin B2"),       1.4f },
            { QObject::tr("vitamin B6"),       1.4f },
            { QObject::tr("vitamin B12"),      2.4f },
            { QObject::tr("vitamin C"),        100.0f },
            { QObject::tr("niacin"),           14.0f },
            { QObject::tr("folic acid"),       400.0f },
            { QObject::tr("pantothenic acid"), 5.0f },
            { QObject::tr("biotin"),           30.0f },
            { QObject::tr("choline"),          450.0f },
            { QObject::tr("calcium"),          800.0f },
            { QObject::tr("phosphorus"),       700.0f },
            { QObject::tr("potassium"),        2000.0f },
            { QObject::tr("sodium"),           2000.0f },
            { QObject::tr("magnesium"),        300.0f },
            { QObject::tr("iron"),             15.0f },
            { QObject::tr("zinc"),             15.0f },
            { QObject::tr("iodine"),           150.0f },
            { QObject::tr("selenium"),         50.0f },
            { QObject::tr("copper"),           1.5f },
            { QObject::tr("fluorine"),         1.0f },
            { QObject::tr("manganese"),        3.0f }
        };

        initUI();
        connectSgn();
    }

    ElementListWidget::~ElementListWidget()
    {

    }

    void ElementListWidget::initUI()
    {
        QStringList lstHeader;
        lstHeader << QObject::tr("Project") << QObject::tr("Each(") + m_strValue + " g)"
            << QObject::tr("Each(") + "100 g)" << QObject::tr("pabulum reference");
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

    void ElementListWidget::resizeEvent(QResizeEvent *event)
    {
        m_pUi->m_listViewElement->setColumnWidth(0, this->width() / 3);
        m_pUi->m_listViewElement->setColumnWidth(1, this->width() / 3);
    }

    void ElementListWidget::refreshHeaderData()
    {
        QStringList lstHeader;
                lstHeader << QObject::tr("Project") << QObject::tr("Each(") + m_strValue + " g)"
            << QObject::tr("Each(") + "100 g)" << QObject::tr("pabulum reference");

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
        m_listNRV.clear();
        m_listUnit.clear();
        m_eachPer = 0.0;
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
        changeConstituentToHundredEachPer(m_listConstituent, m_listConstituentHundred);
        refreshHeaderData();

        calculateEnergy(); 
        addElementToList(m_listElement, m_listConstituent, m_listConstituentHundred, m_eachPer);
        calculateUnitAndNRV(m_listElement, m_listConstituentHundred);
    }

    // 转换到每份100克的数据
    void ElementListWidget::changeConstituentToHundredEachPer(const QList<float>& listConstituent, QList<float>& listConstituentHundred)
    {
        m_listConstituentHundred.clear();
        for each (float constituent in listConstituent)
        {
            constituent = constituent * 100 / m_eachPer;

            listConstituentHundred.push_back(constituent);
        }
    }

    // 添加到营养成份表
    // to do 重构
    void ElementListWidget::addElementToList(QList<QString> listElement, QList<float> listConstituent, 
        QList<float> listConstituentHundred, float& eachPer)
    {
        // 能量
        bool bAddElement = false;
        int iIndex = 0;
        for each (QString element in listElement)
        {
            if (0 == element.compare(QObject::tr("energy")))
            {
                bAddElement = true;
                int nRow = m_model->rowCount();
                QStandardItem* item = new QStandardItem();
                m_model->insertRow(nRow, item);

                m_model->setData(m_model->index(nRow, 0), listElement[iIndex]);
                m_model->setData(m_model->index(nRow, 1), calculateConstituentValue(listElement[iIndex], listConstituent[iIndex], true));
                m_model->setData(m_model->index(nRow, 2), calculateConstituentValue(listElement[iIndex], listConstituentHundred[iIndex]));
                m_model->setData(m_model->index(nRow, 3), calculateNRVReferenceValue(listElement[iIndex], listConstituentHundred[iIndex]));

                listElement.removeAt(iIndex);
                listConstituent.removeAt(iIndex);
                listConstituentHundred.removeAt(iIndex);
                break;
            }
            iIndex++;
        }

        // 蛋白质
        bAddElement = false;
        iIndex = 0;
        for each (QString element in listElement)
        {
            if (0 == element.compare(QObject::tr("protein")))
            {
                bAddElement = true;
                int nRow = m_model->rowCount();
                QStandardItem* item = new QStandardItem();
                m_model->insertRow(nRow, item);

                m_model->setData(m_model->index(nRow, 0), listElement[iIndex]);
                m_model->setData(m_model->index(nRow, 1), calculateConstituentValue(listElement[iIndex], listConstituent[iIndex], true));
                m_model->setData(m_model->index(nRow, 2), calculateConstituentValue(listElement[iIndex], listConstituentHundred[iIndex]));
                m_model->setData(m_model->index(nRow, 3), calculateNRVReferenceValue(listElement[iIndex], listConstituentHundred[iIndex]));

                listElement.removeAt(iIndex);
                listConstituent.removeAt(iIndex);
                listConstituentHundred.removeAt(iIndex);
                break;
            }
            iIndex++;
        }
        if (!bAddElement)
        {
            int nRow = m_model->rowCount();
            QStandardItem* item = new QStandardItem();
            m_model->insertRow(nRow, item);

            m_model->setData(m_model->index(nRow, 0), QObject::tr("protein"));
            float fValue = 0.0;
            m_model->setData(m_model->index(nRow, 1), calculateConstituentValue(QObject::tr("protein"), fValue, true));
            m_model->setData(m_model->index(nRow, 2), calculateConstituentValue(QObject::tr("protein"), fValue));
            m_model->setData(m_model->index(nRow, 3), calculateNRVReferenceValue(QObject::tr("protein"), fValue));

            m_listElement.push_back(QObject::tr("protein"));
            m_listConstituent.push_back(fValue);
            m_listConstituentHundred.push_back(fValue);
        }

        // 脂肪
        bAddElement = false;
        iIndex = 0;
        for each (QString element in listElement)
        {
            if (0 == element.compare(QObject::tr("fat")))
            {
                bAddElement = true;
                int nRow = m_model->rowCount();
                QStandardItem* item = new QStandardItem();
                m_model->insertRow(nRow, item);

                m_model->setData(m_model->index(nRow, 0), listElement[iIndex]);
                m_model->setData(m_model->index(nRow, 1), calculateConstituentValue(listElement[iIndex], listConstituent[iIndex], true));
                m_model->setData(m_model->index(nRow, 2), calculateConstituentValue(listElement[iIndex], listConstituentHundred[iIndex]));
                m_model->setData(m_model->index(nRow, 3), calculateNRVReferenceValue(listElement[iIndex], listConstituentHundred[iIndex]));

                listElement.removeAt(iIndex);
                listConstituent.removeAt(iIndex);
                listConstituentHundred.removeAt(iIndex);
                break;
            }
            iIndex++;
        }
        if (!bAddElement)
        {
            int nRow = m_model->rowCount();
            QStandardItem* item = new QStandardItem();
            m_model->insertRow(nRow, item);

            m_model->setData(m_model->index(nRow, 0), QObject::tr("fat"));
            float fValue = 0.0;
            m_model->setData(m_model->index(nRow, 1), calculateConstituentValue(QObject::tr("fat"), fValue, true));
            m_model->setData(m_model->index(nRow, 2), calculateConstituentValue(QObject::tr("fat"), fValue));
            m_model->setData(m_model->index(nRow, 3), calculateNRVReferenceValue(QObject::tr("fat"), fValue));

            m_listElement.push_back(QObject::tr("fat"));
            m_listConstituent.push_back(fValue);
            m_listConstituentHundred.push_back(fValue);
        }

        // 反式脂肪
        bAddElement = false;
        iIndex = 0;
        for each (QString element in listElement)
        {
            if (0 == element.compare(QObject::tr("trans fat")))
            {
                bAddElement = true;
                int nRow = m_model->rowCount();
                QStandardItem* item = new QStandardItem();
                m_model->insertRow(nRow, item);

                m_model->setData(m_model->index(nRow, 0), listElement[iIndex]);
                m_model->setData(m_model->index(nRow, 1), calculateConstituentValue(listElement[iIndex], listConstituent[iIndex], true));
                m_model->setData(m_model->index(nRow, 2), calculateConstituentValue(listElement[iIndex], listConstituentHundred[iIndex]));
                m_model->setData(m_model->index(nRow, 3), calculateNRVReferenceValue(listElement[iIndex], listConstituentHundred[iIndex]));

                listElement.removeAt(iIndex);
                listConstituent.removeAt(iIndex);
                listConstituentHundred.removeAt(iIndex);
                break;
            }
            iIndex++;
        }
        if (!bAddElement)
        {
            int nRow = m_model->rowCount();
            QStandardItem* item = new QStandardItem();
            m_model->insertRow(nRow, item);

            m_model->setData(m_model->index(nRow, 0), QObject::tr("trans fat"));
            float fValue = 0.0;
            m_model->setData(m_model->index(nRow, 1), calculateConstituentValue(QObject::tr("trans fat"), fValue, true));
            m_model->setData(m_model->index(nRow, 2), calculateConstituentValue(QObject::tr("trans fat"), fValue));
            m_model->setData(m_model->index(nRow, 3), calculateNRVReferenceValue(QObject::tr("trans fat"), fValue));

            m_listElement.push_back(QObject::tr("trans fat"));
            m_listConstituent.push_back(fValue);
            m_listConstituentHundred.push_back(fValue);
        }

        // 碳水化合物
        bAddElement = false;
        iIndex = 0;
        for each (QString element in listElement)
        {
            if (0 == element.compare(QObject::tr("carbohydrate")))
            {
                bAddElement = true;
                int nRow = m_model->rowCount();
                QStandardItem* item = new QStandardItem();
                m_model->insertRow(nRow, item);

                m_model->setData(m_model->index(nRow, 0), listElement[iIndex]);
                m_model->setData(m_model->index(nRow, 1), calculateConstituentValue(listElement[iIndex], listConstituent[iIndex], true));
                m_model->setData(m_model->index(nRow, 2), calculateConstituentValue(listElement[iIndex], listConstituentHundred[iIndex]));
                m_model->setData(m_model->index(nRow, 3), calculateNRVReferenceValue(listElement[iIndex], listConstituentHundred[iIndex]));

                listElement.removeAt(iIndex);
                listConstituent.removeAt(iIndex);
                listConstituentHundred.removeAt(iIndex);
                break;
            }
            iIndex++;
        }
        if (!bAddElement)
        {
            int nRow = m_model->rowCount();
            QStandardItem* item = new QStandardItem();
            m_model->insertRow(nRow, item);

            m_model->setData(m_model->index(nRow, 0), QObject::tr("carbohydrate"));
            float fValue = 0.0;
            m_model->setData(m_model->index(nRow, 1), calculateConstituentValue(QObject::tr("carbohydrate"), fValue, true));
            m_model->setData(m_model->index(nRow, 2), calculateConstituentValue(QObject::tr("carbohydrate"), fValue));
            m_model->setData(m_model->index(nRow, 3), calculateNRVReferenceValue(QObject::tr("carbohydrate"), fValue));

            m_listElement.push_back(QObject::tr("carbohydrate"));
            m_listConstituent.push_back(fValue);
            m_listConstituentHundred.push_back(fValue);
        }

        // 膳食纤维
        bAddElement = false;
        iIndex = 0;
        for each (QString element in listElement)
        {
            if (0 == element.compare(QObject::tr("dietary fiber")))
            {
                bAddElement = true;
                int nRow = m_model->rowCount();
                QStandardItem* item = new QStandardItem();
                m_model->insertRow(nRow, item);

                m_model->setData(m_model->index(nRow, 0), listElement[iIndex]);
                m_model->setData(m_model->index(nRow, 1), calculateConstituentValue(listElement[iIndex], listConstituent[iIndex], true));
                m_model->setData(m_model->index(nRow, 2), calculateConstituentValue(listElement[iIndex], listConstituentHundred[iIndex]));
                m_model->setData(m_model->index(nRow, 3), calculateNRVReferenceValue(listElement[iIndex], listConstituentHundred[iIndex]));

                listElement.removeAt(iIndex);
                listConstituent.removeAt(iIndex);
                listConstituentHundred.removeAt(iIndex);
                break;
            }
            iIndex++;
        }
        if (!bAddElement)
        {
            int nRow = m_model->rowCount();
            QStandardItem* item = new QStandardItem();
            m_model->insertRow(nRow, item);

            m_model->setData(m_model->index(nRow, 0), QObject::tr("dietary fiber"));
            float fValue = 0.0;
            m_model->setData(m_model->index(nRow, 1), calculateConstituentValue(QObject::tr("dietary fiber"), fValue, true));
            m_model->setData(m_model->index(nRow, 2), calculateConstituentValue(QObject::tr("dietary fiber"), fValue));
            m_model->setData(m_model->index(nRow, 3), calculateNRVReferenceValue(QObject::tr("dietary fiber"), fValue));

            m_listElement.push_back(QObject::tr("dietary fiber"));
            m_listConstituent.push_back(fValue);
            m_listConstituentHundred.push_back(fValue);
        }

        // 钠
        bAddElement = false;
        iIndex = 0;
        for each (QString element in listElement)
        {
            if (0 == element.compare(QObject::tr("sodium")))
            {
                bAddElement = true;
                int nRow = m_model->rowCount();
                QStandardItem* item = new QStandardItem();
                m_model->insertRow(nRow, item);

                m_model->setData(m_model->index(nRow, 0), listElement[iIndex]);
                m_model->setData(m_model->index(nRow, 1), calculateConstituentValue(listElement[iIndex], listConstituent[iIndex], true));
                m_model->setData(m_model->index(nRow, 2), calculateConstituentValue(listElement[iIndex], listConstituentHundred[iIndex]));
                m_model->setData(m_model->index(nRow, 3), calculateNRVReferenceValue(listElement[iIndex], listConstituentHundred[iIndex]));

                listElement.removeAt(iIndex);
                listConstituent.removeAt(iIndex);
                listConstituentHundred.removeAt(iIndex);
                break;
            }
            iIndex++;
        }
        if (!bAddElement)
        {
            int nRow = m_model->rowCount();
            QStandardItem* item = new QStandardItem();
            m_model->insertRow(nRow, item);

            m_model->setData(m_model->index(nRow, 0), QObject::tr("sodium"));
            float fValue = 0.0;
            m_model->setData(m_model->index(nRow, 1), calculateConstituentValue(QObject::tr("sodium"), fValue, true));
            m_model->setData(m_model->index(nRow, 2), calculateConstituentValue(QObject::tr("sodium"), fValue));
            m_model->setData(m_model->index(nRow, 3), calculateNRVReferenceValue(QObject::tr("sodium"), fValue));

            m_listElement.push_back(QObject::tr("sodium"));
            m_listConstituent.push_back(fValue);
            m_listConstituentHundred.push_back(fValue);
        }

        // other
        for (int iIndex = 0; iIndex < listElement.size() && iIndex < listConstituent.size() 
            && iIndex < listConstituentHundred.size(); iIndex++)
        {
            int nRow = m_model->rowCount();
            QStandardItem* item = new QStandardItem();
            m_model->insertRow(nRow, item);

            m_model->setData(m_model->index(nRow, 0), listElement[iIndex]);        
            m_model->setData(m_model->index(nRow, 1), calculateConstituentValue(listElement[iIndex], listConstituent[iIndex], true));
            m_model->setData(m_model->index(nRow, 2), calculateConstituentValue(listElement[iIndex], listConstituentHundred[iIndex]));
            // using 100 each per calculate the NRV Reference
            m_model->setData(m_model->index(nRow, 3), calculateNRVReferenceValue(listElement[iIndex], listConstituentHundred[iIndex]));
        }
    }

    void ElementListWidget::calculateEnergy()
    {
        if (m_listElement.size() != m_listConstituent.size())
        {
            return;
        }

        int iIndex = 0;
        float fEnergy = 0.0;
        for each (QString strElement in m_listElement)
        {
            if (0 == strElement.compare(QObject::tr("protein")))
            {
                fEnergy += m_listConstituent[iIndex] * 17; // according to standard file
            }
            else if (0 == strElement.compare(QObject::tr("fat")))
            {
                fEnergy += m_listConstituent[iIndex] * 37;
            }
            else if (0 == strElement.compare(QObject::tr("carbohydrate")))
            {
                fEnergy += m_listConstituent[iIndex] * 17;
            }
            else if (0 == strElement.compare(QObject::tr("dietary fiber")))
            {
                fEnergy += m_listConstituent[iIndex] * 8;
            }
            iIndex++;
        }

        m_listElement.push_front(QObject::tr("energy"));
        m_listConstituent.push_front(fEnergy);
        m_listConstituentHundred.push_front(fEnergy * 100 / m_eachPer);
    }

    QString ElementListWidget::calculateConstituentValue(QString& strElement, float& fConstituent, bool bAddUnit/* = false*/)
    {
        QString strTempConstituent = "";
        auto it = targetTable.find(strElement);
        if(it != targetTable.end())
        {
            ReferenceTarget target = it->second;
            if (QObject::tr("mg") == target.strUnit)
            {
                fConstituent *= 1000;
            }
            else if (QObject::tr("ug") == target.strUnit)
            {
                fConstituent *= 1000 * 1000;
            }

            if (target.iRetainPlace > 0.9 && target.iRetainPlace < 1.1)
            {
                int iConstituent = fConstituent + 0.5;
                fConstituent = iConstituent;
            }
            else if (target.iRetainPlace > 0.09 && target.iRetainPlace < 0.11)
            {
                int iConstituent = fConstituent * 10 + 0.5;
                fConstituent = iConstituent / 10.0;
            }
            else if (target.iRetainPlace > 0.009 && target.iRetainPlace < 0.011)
            {
                int iConstituent = fConstituent * 100 + 0.5;
                fConstituent = iConstituent / 100.0;
            }

            if (QObject::tr("g") == target.strUnit)
            {
                strTempConstituent = QString::number(fConstituent, 'f', 1) + target.strUnit;
            }
            else
            {
                strTempConstituent = QString("%1 ").arg(fConstituent) + target.strUnit;
            }

            // m_listUnit.push_back(target.strUnit);
        }
        return strTempConstituent;
    }

    QString ElementListWidget::calculateNRVReferenceValue(QString& strElement, float& fConstituent)
    {
        QString strReferenceTmp = "";
        auto it = valueTable.find(strElement);
        if(it != valueTable.end())
        {
            strReferenceTmp = QString("%1%2").arg((int)(fConstituent / it->second * 100 + 0.5)).arg("%");
          //  m_listNRV.push_back(strReferenceTmp);
        }
        else if (0 == strElement.compare(QObject::tr("trans fat")))
        {
         //   m_listNRV.push_back(strReferenceTmp);
        }

        return strReferenceTmp;
    }

    void ElementListWidget::calculateUnitAndNRV(const QList<QString>& listElement, const QList<float>& m_listConstituentHundred)
    {
        int iIndex = 0;
        for each (QString element in listElement)
        {
            auto it = targetTable.find(element);
            if (it != targetTable.end())
            {
                ReferenceTarget target = it->second;
                m_listUnit.push_back(target.strUnit);
            }
            else
            {
                m_listUnit.push_back("");
            }

            QString strReferenceTmp = "";
            auto itValue = valueTable.find(element);
            if (itValue != valueTable.end())
            {
                strReferenceTmp = QString("%1%2").arg((int)(m_listConstituentHundred[iIndex] / itValue->second * 100 + 0.5)).arg("%");
                m_listNRV.push_back(strReferenceTmp);
            }
            else if (0 == element.compare(QObject::tr("trans fat")))
            {
                m_listNRV.push_back(strReferenceTmp);
            }
            else
            {
                m_listNRV.push_back(strReferenceTmp);
            }

            iIndex++;
        }
    }

    void ElementListWidget::getElementListData(std::vector<nutrientContentTable>& contentTable, float& eachPer)
    {
        if (nullptr == m_model)
        {
            return;
        }

        for (int iRow = 0; iRow < m_model->rowCount(); iRow++)
        {
            nutrientContentTable content;
            for (int iCol = 0; iCol < m_model->columnCount(); iCol++)
            {
                if (ELEMENTCOLUMN == iCol)
                {
                    content.strElement = m_model->data(m_model->index(iRow, iCol)).toString();
                }
                else if (CONTENTCOLUMN == iCol)
                {
                    content.strContentPenHundred = m_model->data(m_model->index(iRow, iCol)).toString();
                }
                else if (NRVCOLUMN == iCol)
                {
                    content.strNRV = m_model->data(m_model->index(iRow, iCol)).toString();
                }
            }
            contentTable.push_back(content);
        }

        eachPer = 100.0;//m_eachPer; // now hard code used
    }

}