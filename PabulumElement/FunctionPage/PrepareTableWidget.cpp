#include "PrepareTableWidget.h"
#include "ui_PrepareTableWidget.h"
#include "AppCommon/commonControl.h"
#include "AppCommon/WordFileOperation.h"
#include "HomePage/ViewDefine.h"
#include "AppCommon/ExecFileOperation.h"
#include "AppCommon/WaitingWidget.h"
#include "Tools/Dir.h"
#include "TableOperBtnWidget.h"
#include "MessageBox/MessageBox.h"
#include "MessageNotify/MessageNotify.h"
#include "RecipeElementWidget.h"
#include "MySQL/MysqlDB.h"
#include "libdsl/dslbase.h"
#include "libdsl/DPrintLog.h"

#include <QtGui/QPixmap>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtWidgets/QFileDialog>
#include <Ole2.h>

const int g_ContaintElement = 2;
const int g_StartElement = 4;
const int g_SaveFileWaitTime = 1 * 60;

namespace mainApp
{
    PrepareTableWidget::PrepareTableWidget(QWidget* pParent /*= nullptr*/)
        : QWidget(pParent)
        , m_pUi(nullptr)
        , m_pExcelFile(nullptr)
        , m_pWordFile(nullptr)
        , m_model(nullptr)
        , m_modelTmp(nullptr)
        , m_pCurEnteredItem(nullptr)
        , m_pRecipeElementWidget(nullptr)
        , m_pMysqlDB(nullptr)
        , m_pWaitingWidget(nullptr)
        , m_pThread(nullptr)
    {
        m_pUi = new Ui::PrepareTableWidget();
        m_pUi->setupUi(this);

        initUI();
        connectSgn();
        SET_MODULE_STYLE_BY_PATH("PrepareTableWidget");
    }

    PrepareTableWidget::~PrepareTableWidget()
    {
        //m_pWaitingWidget->setQuit(true);
        m_pRecipeElementWidget = nullptr;
        SAFE_DELETE(m_pWordFile);
        SAFE_DELETE(m_pExcelFile);
    }

    void PrepareTableWidget::initUI()
    {
        // read execl file
//         QString strExcelFile = DSGUI::DSDir::GetCurrentPath() + "/PabulumElementTale.xlsx";
         m_pExcelFile = new ExecFileOperation();
         m_pWordFile = new WordFileOperation();

         QRegExp regx("^(([0-9]+\\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\\.[0-9]+)|([0-9]*[1-9][0-9]*))$");
         QValidator *validator = new QRegExpValidator(regx, m_pUi->m_editElement);
         m_pUi->m_editElement->setValidator(validator);
         m_pUi->m_editContent->setValidator(validator);
 
        // product type
        // 其他类特殊膳食食品（运动营养食品 - 补充蛋白类）
        m_pUi->m_cmbProductType->addItem(QObject::tr("Other types of special dietary food (sports nutrition food - protein supplement class)"));
        // 其他类特殊膳食食品（运动营养食品-补充能量类）
        m_pUi->m_cmbProductType->addItem(QObject::tr("Other types of special dietary food (sports nutrition food - supplement energy class)"));
        // 其他类特殊膳食食品（运动营养食品-控制能量类-能量替代-部分代餐）
        m_pUi->m_cmbProductType->addItem(QObject::tr("Other types of special dietary food (sports nutrition food - control energy - energy alternative - part of the meal)"));
        // 其他类特殊膳食食品（运动营养食品-控制能量类-能量替代-完全代餐）
        m_pUi->m_cmbProductType->addItem(QObject::tr("Other types of special dietary food (sports nutrition food - control energy - energy alternative - full meal)"));
        // 其他类特殊膳食食品（运动营养食品-促进能量消耗-固态）
        m_pUi->m_cmbProductType->addItem(QObject::tr("Other types of special dietary food (sports nutrition food - promote energy consumption - solid)"));
        // 其他类特殊膳食食品（运动营养食品-速度力量类）
        m_pUi->m_cmbProductType->addItem(QObject::tr("Other types of special dietary food (sports nutrition food - speed strength class)"));
        // 其他类特殊膳食食品（运动营养食品-耐力类）
        m_pUi->m_cmbProductType->addItem(QObject::tr("Other types of special dietary food (sports nutrition food - endurance class)"));
        // 其他类特殊膳食食品（运动营养食品-运动后恢复类）
        m_pUi->m_cmbProductType->addItem(QObject::tr("Other types of special dietary food (sports nutrition food - recovery after exercise class)"));
        // 冷加工糕点
        m_pUi->m_cmbProductType->addItem(QObject::tr("Cold working pastry"));
        // 固体饮料
        m_pUi->m_cmbProductType->addItem(QObject::tr("Solid beverage"));
        // 方便食品
        m_pUi->m_cmbProductType->addItem(QObject::tr("Convenience foods"));
        // 代用茶
        m_pUi->m_cmbProductType->addItem(QObject::tr("Substitute of tea"));
        // 淀粉糖（葡萄糖分装）
        m_pUi->m_cmbProductType->addItem(QObject::tr("Starch sugar (glucose partial shipments)"));

        // applay person
        m_pUi->m_cmbApplayPerson->addItem("");
        // 需要补充蛋白质的人群
        m_pUi->m_cmbApplayPerson->addItem(QObject::tr("People need protein"));
        // 需要控制体重的人群
        m_pUi->m_cmbApplayPerson->addItem(QObject::tr("The need to control the weight of the crowd"));
        // 需要补充能量的人群
        m_pUi->m_cmbApplayPerson->addItem(QObject::tr("People need to supplement energy"));
        // 速度力量类运动人群
        m_pUi->m_cmbApplayPerson->addItem(QObject::tr("Speed strength class sports population"));
        // 耐力类运动人群
        m_pUi->m_cmbApplayPerson->addItem(QObject::tr("Endurance sports population"));
        // 运动后恢复类运动人群
        m_pUi->m_cmbApplayPerson->addItem(QObject::tr("Recovery after exercise class sports population"));

        // product standard
        m_pUi->m_cmbProductStandard->addItem(QObject::tr("GB 24154"));
        m_pUi->m_cmbProductStandard->addItem(QObject::tr("Q/HHM0003S"));
        m_pUi->m_cmbProductStandard->addItem(QObject::tr("Q/HHM0004S"));
        m_pUi->m_cmbProductStandard->addItem(QObject::tr("Q/HHM0005S"));
        m_pUi->m_cmbProductStandard->addItem(QObject::tr("Q/HHM0006S"));
        m_pUi->m_cmbProductStandard->addItem(QObject::tr("Q/HHM0007S"));
        m_pUi->m_cmbProductStandard->addItem(QObject::tr("Q/HHM0008S"));
        m_pUi->m_cmbProductStandard->addItem(QObject::tr("Q/HHM0009S"));
        m_pUi->m_cmbProductStandard->addItem(QObject::tr("Q/HHM00010S"));
        m_pUi->m_cmbProductStandard->addItem(QObject::tr("Q/HHM00011S"));
        m_pUi->m_cmbProductStandard->addItem(QObject::tr("Q/HHM00012S"));
        m_pUi->m_cmbProductStandard->addItem(QObject::tr("GB/T 29602"));
        m_pUi->m_cmbProductStandard->addItem(QObject::tr("GH/T 1091"));

        m_pUi->m_cmbExpirationDate->addItem(QObject::tr("6 months"));
        m_pUi->m_cmbExpirationDate->addItem(QObject::tr("9 months"));
        m_pUi->m_cmbExpirationDate->addItem(QObject::tr("12 months"));
        m_pUi->m_cmbExpirationDate->addItem(QObject::tr("15 months"));
        m_pUi->m_cmbExpirationDate->addItem(QObject::tr("18 months"));
        m_pUi->m_cmbExpirationDate->addItem(QObject::tr("24 months"));

        // save condition
        // 阴凉、通风、干燥处
        m_pUi->m_cmbStornCondition->addItem(QObject::tr("A cool, ventilated, dry place"));
        // 置阴凉干燥处（25摄氏度以下，相对湿度小于55%）密封保存，冷藏更佳
        m_pUi->m_cmbStornCondition->addItem(QObject::tr("Buy a cool and dry place (below 25 degrees Celsius, less than 55% relative humidity) seal preservation, cold storage is better"));

        // explane for something
        std::vector<QString> vecDatas;
        // 产品中含新资源食品原料  ，产品最大食用量为  千克/天。
        vecDatas.push_back(QObject::tr("Product contains new resource food raw materials, products consumption for kg/day"));
        // 产品非婴幼儿食品，婴幼儿不宜食用
        vecDatas.push_back(QObject::tr("The infant food products, is not suitable for infants and young children"));
        m_pUi->m_cmbExplane->setData(vecDatas);

        // warm remained
        vecDatas.clear();
        // 由于农产品受采摘季节和地域的影响，不同产品批次颜色略有差异，不影响产品品质
        vecDatas.push_back(QObject::tr("Because of the influence of the agricultural harvest season and region, batch slightly different color, different products will not affect the product quality"));
        // 产品硬脆度和温度有直接关系，冬季产品相对硬实，不影响产品品质
        vecDatas.push_back(QObject::tr("Hard brittleness and temperature is directly related to product, winter products is relatively hard, do not affect product quality"));
        // 本品含有巧克力，气温超过28℃易融化，请将产品放置于阴凉干燥处储存
        vecDatas.push_back(QObject::tr("This product contains chocolate, temperature more than 28 degree is easy to melt, please place the products stored in a cool and dry place"));
        m_pUi->m_cmbRemainder->setData(vecDatas);

        // eat method
        vecDatas.clear();
        // 开袋即食
        vecDatas.push_back(QObject::tr("Open bags of instant"));
        // 取适量产品冲入温水中，搅拌均匀后食用
        vecDatas.push_back(QObject::tr("Take proper amount into the warm water, stir well after eating"));
        // 开袋即食或取适量产品冲入一定量的热水中，搅拌均匀静置片刻后，食用
        vecDatas.push_back(QObject::tr("Open bags of instant or take a suitable amount of product into a certain amount of hot water, stir well let stand a moment later, to eat"));
        // 建议每餐    支，每日      次
        vecDatas.push_back(QObject::tr("Advice at every meal, the daily times"));
        m_pUi->m_cmbEdibleFunction->setData(vecDatas);

        initListCtrl();
        m_pWaitingWidget = new WaitingWidget(this);
        m_pWaitingWidget->SetTimeOut(g_SaveFileWaitTime);
    }

    void PrepareTableWidget::connectSgn()
    {
        connect(m_pUi->m_btnAdd,           SIGNAL(clicked()),     this, SLOT(onAddRecipe()));
        connect(m_pUi->m_btnNext,          SIGNAL(clicked()),     this, SIGNAL(sgnNextWidget()));
        connect(m_pUi->m_btnCreate,        SIGNAL(clicked()),     this, SLOT(onCreateData()));
        connect(m_pUi->m_btnClear,         SIGNAL(clicked()),     this, SLOT(onClearList()));
        connect(m_pUi->m_btnRecipeExcel,   SIGNAL(clicked()),     this, SLOT(onInportRecipeExcel()));
        connect(m_pUi->m_editFilterRecipe, SIGNAL(textChanged(const QString &)), this, SLOT(onTextChanged(const QString &)));
    }

    void PrepareTableWidget::SetAbbreviationTable(std::shared_ptr<MysqlDB::CMysqlDB> pMysqlDB)
    {
        m_pMysqlDB = pMysqlDB;

        m_mapMaterials.clear();
        m_mapMaterials = m_pMysqlDB->queryAllMaterial();

        initDatabaseCombobox();
        //initListCtrl();
    }

    // 原料下拉菜单
    void PrepareTableWidget::initDatabaseCombobox()
    {
        decodeDefinition(m_mapContains, m_mapMaterials);
        m_pUi->m_cmbRecipe->clear();

        for each (auto material in m_mapContains)
        {
            QString strRecipe = material.first;
            if (!strRecipe.isEmpty())
            {
                m_pUi->m_cmbRecipe->addItem(strRecipe);
            }
        }
    }

    // 原料过滤显示
    void PrepareTableWidget::onTextChanged(const QString & text)
    {
        m_pUi->m_cmbRecipe->clear();

        for each (auto material in m_mapContains)
        {
            QString strRecipe = material.first;
            if(!strRecipe.isEmpty() && strRecipe.contains(m_pUi->m_editFilterRecipe->text()))
            {
                m_pUi->m_cmbRecipe->addItem(strRecipe);
            }
        }
    }

    // 原料定义解析，成分含量
    void PrepareTableWidget::decodeDefinition(std::map<QString, std::map<QString, QString>>& mapContains,
        std::map<QString, QString>& mapMaterials)
    {
        if (mapMaterials.size() < 1)
        {
            return;
        }
        mapContains.clear();
        std::map<QString, QString> mapContaint;
        //m_listElements.clear();

        for each (auto material in mapMaterials)
        {
            mapContaint.clear();
            QString strRecipe = material.first;
            QString strDefinition = material.second;
            QStringList strListElements = strDefinition.split(";"); // each element
            if (strListElements.isEmpty())
            {
                continue;
            }
            foreach(QString element, strListElements)
            {
                QStringList strListElement = element.split(":"); // each containt
                if (g_ContaintElement != strListElement.size())
                {
                    continue;
                }
                mapContaint[strListElement[0]] = strListElement[1];

                std::vector<QString>::iterator it = std::find(m_listElements.begin(), m_listElements.end(), strListElement[0]);
                if (it == m_listElements.end() && QObject::tr("code") != strListElement[0] 
                   && QObject::tr("Recipe") != strListElement[0] && QObject::tr("Price") != strListElement[0])
                {
                    float fValue = strListElement[1].toFloat();
                    if (fValue < 100.0 && fValue > -0.0001)
                    {
                        //m_listElements.push_back(strListElement[0]); // no need to add, listElements use for have added material
                    }
                }
            }

            if (mapContaint.size() > 0)
            {
                mapContains[strRecipe] = mapContaint;
            }
        }
    }

    void PrepareTableWidget::tableOperateBtn(int nRow, int nCol, QStandardItem* item)
    {
        if (m_model == nullptr)
        {
            return;
        }

        TableOperBtnWidget* pOperateWidget = new TableOperBtnWidget(this);

        QPushButton* btnDel = new QPushButton(pOperateWidget);
        btnDel->setGeometry(0, 0, 16, 16);
        btnDel->setMinimumSize(QSize(16, 16));
        btnDel->setMaximumSize(QSize(16, 16));
        btnDel->setObjectName("btnDel");
        btnDel->setToolTip(tr("Delete"));

        connect(btnDel, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));

        pOperateWidget->addButtnon(btnDel);
        connect(pOperateWidget, SIGNAL(sgnTableOperIndex(QStandardItem*)), this, SLOT(onTableOperIndex(QStandardItem*)));
        m_pUi->m_listViewRecipe->setIndexWidget(m_model->index(nRow, nCol), pOperateWidget);

        pOperateWidget->showEditButton();
        pOperateWidget->setTableOperIndex(item);
    }

    void PrepareTableWidget::setRecipeElementWidget(RecipeElementWidget* pWidget)
    {
        m_pRecipeElementWidget = pWidget;
    }

    void PrepareTableWidget::onTableOperIndex(QStandardItem* pItem)
    {
        m_pCurEnteredItem = pItem;
    }

    void PrepareTableWidget::onDelBtnClicked()
    {
//    		if (DSGUI::DSMessageBox::Ok != DSGUI::DSMessageBox::ShowInformation(m_pUi->m_listViewRecipe, QObject::tr("Notice"),
//      			QObject::tr("Sure to delete this recipe?"), DSGUI::DSMessageBox::Ok | DSGUI::DSMessageBox::Cancel))
//    		{
//    			return;
//    		}
        if (m_pCurEnteredItem == nullptr)
        {
            return;
        }
        QModelIndex index = m_pCurEnteredItem->index();

        // 删除list中相应行
        m_model->removeRow(index.row());
        // 更新序列号
        int nCount = m_model->rowCount(); 
        for (int i = 0; i < nCount; i++)
        {
            QString strText = QString("%1").arg(i + 1);
            m_model->setData(m_model->index(i, Recipe_View_Column_Num), strText);
        }
    }

    void PrepareTableWidget::onCreateData()
    {
        if (nullptr == m_pRecipeElementWidget || nullptr == m_model)
        {
            return;
        }

        int iColumn = m_model->columnCount();
        int iRow = m_model->rowCount();
        QList<QList<QString>> listValue;
        bool bHead = true;
        for (int iIndexRow = 0; iIndexRow < iRow + 1; iIndexRow++)
        {
            QList<QString> listTemp;
            if (bHead)
            {
                for (int iIndex = 1; iIndex < iColumn - 1; iIndex++)
                {
                    QVariant var = m_model->headerData(iIndex, Qt::Horizontal);
                    listTemp.push_back(var.toString());
                }
                bHead = false;
            }
            else
            {
                for (int iIndexColumn = 1; iIndexColumn < iColumn - 1; iIndexColumn++)
                {
                    QVariant var = m_model->data(m_model->index(iIndexRow - 1, Recipe_View_Column_Num + iIndexColumn));
                    listTemp.push_back(var.toString());
                }
            }
            listValue.push_back(listTemp);
        }
        
        m_pRecipeElementWidget->createData(listValue);
        emit sgnNextWidget();
    }

    void PrepareTableWidget::onClearList()
    {
        if (nullptr != m_model)
        {
            m_model->removeRows(0, m_model->rowCount());
        }
    }

    void PrepareTableWidget::onExport()
    {
         QString strPath = QDir::currentPath();
         QString strName = m_pUi->m_editOfficialName->text();
         if (strName.isEmpty())
         {
              DSGUI::DSMessageNotify::Instance().AddTextNotification(QObject::tr("Official Name is empty!"));
         }
         QString strFileName = strPath + "/OutputFiles/Official/" + strName; // output document
         QString strExcelFileName = strPath + "/OutputFiles/Recipe/" + strName; // output excel

         std::thread pThread(&PrepareTableWidget::waitForSaveFiles, this, strFileName, strExcelFileName); // thread
         m_pWaitingWidget->StartWaiting();
         pThread.join();

         DSGUI::DSMessageNotify::Instance().AddTextNotification(QObject::tr("Export file end!"));
    }

    // for word
    // to do 重构
    void PrepareTableWidget::prepareOfficialData()
    {
        m_pWordFile->replaceText("OfficialName", m_pUi->m_editOfficialName->text()); // bookmark replace for official name
        m_pWordFile->replaceText("ProductName", m_pUi->m_editProductName->text());

        m_pWordFile->replaceText("ProductType", m_pUi->m_cmbProductType->currentText());
        m_pWordFile->replaceText("ApplyPerson", m_pUi->m_cmbApplayPerson->currentText());

        m_pWordFile->replaceText("Recipe", getRecipeData());
        m_pWordFile->replaceText("Explain", m_pUi->m_cmbExplane->currentText());

        m_pWordFile->replaceText("WarmReminder", m_pUi->m_cmbRemainder->currentText());
        m_pWordFile->replaceText("AllergyReminder", m_pUi->m_editAllergy->text());

        m_pWordFile->replaceText("KeepingCondition", m_pUi->m_cmbStornCondition->currentText());
        m_pWordFile->replaceText("EatingMethod", m_pUi->m_cmbEdibleFunction->currentText());

        m_pWordFile->replaceText("NetContent", m_pUi->m_editContent->text());
        m_pWordFile->replaceText("ProductStandard", m_pUi->m_cmbProductStandard->currentText());

        m_pWordFile->replaceText("ExpirationDate", m_pUi->m_cmbExpirationDate->currentText());     

        //QList<QString> listElement;
        //QList<QString> listUnit;
        //QList<QString> listNRV;
        //QList<float> listConstituent;
        std::vector<nutrientContentTable> contentTable;
        float eachPer;
        m_pRecipeElementWidget->getElementListData(contentTable, eachPer);
        QStringList lstHeader;
        QString strValue = QString("%1").arg(eachPer); 
        lstHeader << QObject::tr("Project") << QObject::tr("Each(") + strValue + " g)" << QObject::tr("pabulum reference");
        QAxObject *pObject = m_pWordFile->insertTable("Table", contentTable.size() + 1, lstHeader.size(), lstHeader);
        if (pObject)
        {
            int nRow = 0;
            for each (nutrientContentTable content in contentTable)
            {
                m_pWordFile->SetTableCellString(pObject, nRow + 2, 1, content.strElement);
                m_pWordFile->SetTableCellString(pObject, nRow + 2, 2, content.strContentPenHundred);
                m_pWordFile->SetTableCellString(pObject, nRow + 2, 3, content.strNRV);

                nRow++;
            }
        }
    }

    QString PrepareTableWidget::getRecipeData()
    {
        //int iCount = m_model->rowCount();
        QString strRecipeData = "";
        QList<QString> listSortRecipe;
        m_pRecipeElementWidget->getSortRecipeList(listSortRecipe);
        int iCount = listSortRecipe.size();

        for (int nRow = 0; nRow < iCount; nRow++)
        { 
            QVariant varData = listSortRecipe[nRow];//m_model->data(m_model->index(nRow, Recipe_View_Column_Num + 2)); // 物料名称
            strRecipeData += varData.toString() + ",";
        }

        strRecipeData = strRecipeData.left(strRecipeData.length() - 1);
        return strRecipeData;
    }

    // 导入excel配置清单
    void PrepareTableWidget::onInportRecipeExcel()
    {
        QString strFilePath = QFileDialog::getOpenFileName(this, tr("Inport Recipe Table"), "", tr("*.xls"));
        if (strFilePath.isEmpty())
        {
            return;
        }
        std::thread pThread(&PrepareTableWidget::inportRecipeExcel, this, strFilePath);
        m_pWaitingWidget->StartWaiting();
        pThread.join();

        // after read excel then process date out of thread, if in thread gui have some unknown problems
        if (!m_listData.isEmpty() && m_listData[0].size() >= g_StartElement
            && QObject::tr("code") == m_listData[0][0]) // code recipe constituent price
        {
            m_listElements.clear();

            for (int iIndex = g_StartElement; iIndex < m_listData[0].size(); iIndex++)
            {
                if (0 != m_listElements.size() && m_listElements[0] == m_listData[0][iIndex].toString())
                {
                    break;
                }
                m_listElements.push_back(m_listData[0][iIndex].toString());
            }

            updateListCtrl();
            addRecipeFromExcel(m_listData);
        }
    }

    void PrepareTableWidget::inportRecipeExcel(QString strFilePath)
    {
        HRESULT result = OleInitialize(0);
        if (!strFilePath.isEmpty() && nullptr != m_pExcelFile)
        {
            m_listData.clear();
            m_pUi->m_btnRecipeExcel->setText(strFilePath);
            m_pUi->m_btnRecipeExcel->setToolTip(strFilePath);
            m_pExcelFile->setFilePathName(strFilePath);
            if (!m_pExcelFile->openExecFile())
            {
                m_pWaitingWidget->StopWaiting();
                return;
            }
            QVariant var;
            if (m_pExcelFile->readSheetAllData(var))
            {
                m_pExcelFile->castVariantToList(var, m_listData);
            }
        }
        OleUninitialize();
        m_pWaitingWidget->StopWaiting();
    }

    void PrepareTableWidget::addRecipeFromExcel(QList<QList<QVariant>>& listData)
    {
        for (int iDataIndex = 1; iDataIndex < listData.size(); iDataIndex++)
        {
            int nRow = m_model->rowCount();
            QStandardItem* item = new QStandardItem();
            m_model->insertRow(nRow, item);

            // NO.
            QString strText = QString("%1").arg(nRow + 1);
            m_model->setData(m_model->index(nRow, Recipe_View_Column_Num), strText);
            for (int iIndex = 0; iIndex < m_listElements.size() + Recipe_View_Column_MaterialPrice; iIndex++)
            {
                // material code
                if (!QString::localeAwareCompare(listData[0][iIndex].toString(), QObject::tr("code")))
                {
                    m_model->setData(m_model->index(nRow, Recipe_View_Column_MaterialCode), listData[iDataIndex][iIndex].toString());
                }
                // material name
                else if (!QString::localeAwareCompare(listData[0][iIndex].toString(), QObject::tr("Recipe")))
                {
                    m_model->setData(m_model->index(nRow, Recipe_View_Column_MaterialName), listData[iDataIndex][iIndex].toString());
                }
                // material count
                else if (!QString::localeAwareCompare(listData[0][iIndex].toString(), QObject::tr("Constituent")))
                {
                    m_model->setData(m_model->index(nRow, Recipe_View_Column_MaterialCount), listData[iDataIndex][iIndex].toString());
                }
                // material price
                else if (!QString::localeAwareCompare(listData[0][iIndex].toString(), QObject::tr("Price")))
                {
                    m_model->setData(m_model->index(nRow, Recipe_View_Column_MaterialPrice), listData[iDataIndex][iIndex].toString());
                }
                // material element Eecipe
                else
                {
                    std::vector<QString>::iterator it = std::find(m_listElements.begin(), m_listElements.end(), listData[0][iIndex].toString());
                    if (it != m_listElements.end())
                    {
                        int iCount = it - m_listElements.begin();
                        m_model->setData(m_model->index(nRow, Recipe_View_Column_MaterialPrice + 1 + iCount), listData[iDataIndex][iIndex].toString());
                    }
                }
            }

            tableOperateBtn(nRow, Recipe_View_Column_MaterialPrice + 1 + m_listElements.size(), item);
            QStandardItem *tempItem = new QStandardItem();
            m_model->insertRow(nRow + 1, tempItem);
            m_model->removeRow(nRow + 1);
        }
    }

    void PrepareTableWidget::updateListCtrl()
    {
       // QStringList lstHeader;
        m_lstHeader.clear();
        if (nullptr != m_model)
        {
            m_model->removeRows(0, m_model->rowCount());
            delete m_model;
            m_model = nullptr;
        }
        //QList<QVariant> listVar = m_listData[0];

        for (int iIndex = 0; iIndex < m_listElements.size(); iIndex++)
        {
            if (0 == iIndex)
            {
                m_lstHeader << "No." << QObject::tr("code") << QObject::tr("Recipe")
                    << QObject::tr("Constituent") << QObject::tr("Price")
                    << m_listElements[iIndex];
            }
            else
            {
                m_lstHeader << m_listElements[iIndex];
            }
        }
        m_lstHeader << QObject::tr("Operator");

        m_model = new QStandardItemModel(0, m_lstHeader.count());
        m_pUi->m_listViewRecipe->setModel(m_model);
        m_pUi->m_listViewRecipe->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_pUi->m_listViewRecipe->setColumnWidth(Recipe_View_Column_Num, 30);
        int begin = 0;
        foreach(QString name, m_lstHeader)
        {
            m_model->setHeaderData(begin, Qt::Horizontal, name);
            m_model->setHeaderData(begin, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
            begin++;
        }
    }

    // list ctrl
    void PrepareTableWidget::initListCtrl()
    {
        //QStringList lstHeader;
        m_lstHeader.clear();
        m_listElements.clear();
        if (nullptr != m_model)
        {
            m_model->removeRows(0, m_model->rowCount());
            delete m_model;
            m_model = nullptr;
        }


        m_lstHeader << "No." << QObject::tr("code") << QObject::tr("Recipe")
            << QObject::tr("Constituent") << QObject::tr("Price");

        //m_lstHeader << QObject::tr("Operator");

        m_model = new QStandardItemModel(0, m_lstHeader.count());
        m_pUi->m_listViewRecipe->setModel(m_model);
        m_pUi->m_listViewRecipe->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_pUi->m_listViewRecipe->setColumnWidth(Recipe_View_Column_Num, 30);
        int begin = 0;
        foreach(QString name, m_lstHeader)
        {
            m_model->setHeaderData(begin, Qt::Horizontal, name);
            m_model->setHeaderData(begin, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
            begin++;
        }
    }

    bool PrepareTableWidget::needRefreshListCtrl(const QString& strTitle)
    {
        QStringList strList = m_lstHeader.filter(strTitle);
        if (!strList.isEmpty() /*|| (nullptr != m_model && 0 == m_model->rowCount())*/)
        {
            return false;
        }

        return true;
    }

    void PrepareTableWidget::onAddRecipe()
    {
        int iIndex = m_pUi->m_cmbRecipe->currentIndex();
        QString strData = m_pUi->m_cmbRecipe->currentText();
        QString strValue = m_pUi->m_editElement->text();
        if (strValue.isEmpty())
        {
            return;
        }

        int nRow = m_model->rowCount();
        /**************test using***************/
//         if (nRow > 22)
//         {
//             return;
//         }
        /*****************************/
        std::map<QString, QString> mapContain = m_mapContains[strData];
        bool bNeedRefresh = false;
        for each (auto contain in mapContain)
        {
            if (QObject::tr("code") == contain.first || QObject::tr("Recipe") == contain.first 
                || QObject::tr("Price") == contain.first)
            {
                continue;
            }
            if (needRefreshListCtrl(contain.first))
            {
                bNeedRefresh = true;
                
                bool bContainElement = false;
                for each (auto var in m_listElements)
                {
                    if (contain.first == var)
                    {
                        bContainElement = true;
                        break;
                    }
                }
                if (!bContainElement)
                {
                    m_listElements.push_back(contain.first);
                }

                QStringList strOperator = m_lstHeader.filter(QObject::tr("Operator"));
                int iCount = m_lstHeader.size();
                if (!strOperator.isEmpty())
                {
                    deleteOperatorWidget();
                    m_lstHeader[iCount - 1] = contain.first;
                }
                else
                {
                    m_lstHeader << contain.first;
                }
            }
        }
        if (bNeedRefresh)
        {
            addHeadListCtrl();
        }
        
        QStandardItem* item = new QStandardItem();
        m_model->insertRow(nRow, item);
        QString strText = QString("%1").arg(nRow + 1);
        m_model->setData(m_model->index(nRow, Recipe_View_Column_Num), strText); // NO.
        m_model->setData(m_model->index(nRow, Recipe_View_Column_MaterialName), strData);  // material name
        m_model->setData(m_model->index(nRow, Recipe_View_Column_MaterialCount), strValue); // material count

        for each (auto elements in mapContain) // e.g. code:HM0001
        {
            if (!QString::localeAwareCompare(elements.first, QObject::tr("code")))
            {
                m_model->setData(m_model->index(nRow, Recipe_View_Column_MaterialCode), elements.second); // material code
            }
            else if (!QString::localeAwareCompare(QObject::tr("Price"), elements.first))
            {
                m_model->setData(m_model->index(nRow, Recipe_View_Column_MaterialPrice), elements.second); // material price
            }
            else
            {
                std::vector<QString>::iterator it = std::find(m_listElements.begin(), m_listElements.end(), elements.first);
                if (it != m_listElements.end())
                {
                    QStringList strList = m_lstHeader.filter(elements.first);
                    if (strList.isEmpty())
                    {
                        QStringList strOperator = m_lstHeader.filter(QObject::tr("Operator"));
                        int iCount = m_lstHeader.size();
                        if (!strOperator.isEmpty())
                        {
                            m_lstHeader[iCount - 1] = elements.first;
                        }
                        else
                        {
                            m_lstHeader << elements.first;
                        }
                        //m_lstHeader << elements.first; // if head have not contain this element add
                        bNeedRefresh = true;
                    }

                    int iCount = it - m_listElements.begin();
                    m_model->setData(m_model->index(nRow, Recipe_View_Column_MaterialPrice + 1 + iCount), elements.second); // material element Eecipe
                }
            } 
        }
        if (bNeedRefresh)
        {
            m_lstHeader << QObject::tr("Operator");
            addHeadListCtrl();
            for (int iIndex = 0; iIndex < m_model->rowCount(); iIndex++)
            {
                QStandardItem* pItem = m_model->item(iIndex);
                tableOperateBtn(iIndex, Recipe_View_Column_MaterialPrice + 1 + m_listElements.size(), pItem);
                QStandardItem *tempItem = new QStandardItem();
                m_model->insertRow(nRow + 1, tempItem);
                m_model->removeRow(nRow + 1);
            }
        }
        else
        {
            tableOperateBtn(nRow, Recipe_View_Column_Num + 5 + m_listElements.size(), item);
            QStandardItem *tempItem = new QStandardItem();
            m_model->insertRow(nRow + 1, tempItem);
            m_model->removeRow(nRow + 1);
        }
    }

    void PrepareTableWidget::addHeadListCtrl()
    {
        //m_modelTmp = new QStandardItemModel(0, m_lstHeader.count());
        //int nRow = m_modelTmp->rowCount();
        m_model->setColumnCount(m_lstHeader.size());
        int begin = 0;
        foreach(QString name, m_lstHeader)
        {
            m_model->setHeaderData(begin, Qt::Horizontal, name);
            m_model->setHeaderData(begin, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
            begin++;
        }
    }

    void PrepareTableWidget::addContainElementType(QList<QVariant>& listData)
    {
        if (listData.size() > Recipe_View_Column_MaterialPrice)
        {
            int iSize = listData.size();
            for (int iIndex = Recipe_View_Column_MaterialPrice; iIndex < iSize; iIndex++)
            {
                listData.push_back(listData[iIndex]);
            }
        }
    }

    void PrepareTableWidget::addContainElementValue(QList<QVariant>& listData)
    {
        if (listData.size() > Recipe_View_Column_MaterialPrice)
        {
            int iSize = listData.size();
            for (int iIndex = Recipe_View_Column_MaterialPrice; iIndex < iSize; iIndex++)
            {
                float fValue = listData[Recipe_View_Column_MaterialCount - 1].toFloat() * listData[iIndex].toFloat() / 100;
                listData.push_back(fValue);
            }
        }
    }

    void PrepareTableWidget::waitForSaveFiles(QString strFileName, QString strExcelFileName)
    {
        QString strDotFile = QDir::currentPath() + "/Documents/OfficialTemplate.dot"; // word template
        if (nullptr == m_pWordFile || nullptr == m_pExcelFile)
        {
            return;
        }
        HRESULT result = OleInitialize(0);
        if(S_OK != result)
        {
            DLOG_ERR("OleInitialize filed result: %d", result);
        }
        
        // for word
        bool bOpen = m_pWordFile->openFile(strDotFile, false);
        if (!bOpen)
        {
            DLOG_ERR("Open dot file filed: %s", strDotFile.toStdString().c_str());
            DSGUI::DSMessageNotify::Instance().AddTextNotification(QObject::tr("Open dot file filed!"));
            m_pWaitingWidget->StopWaiting();
            return;
        }
       prepareOfficialData();
       m_pWordFile->saveFile(strFileName);
       m_pWordFile->closeFile();

       // for excel
       //strExcelFileName.replace("/", "\\");

       m_pExcelFile->setFilePathName(strExcelFileName);
       m_pExcelFile->openExecFile();
       QList<QList<QVariant>> listVar;
       QList<QVariant> listData;
       foreach(QString strHead, m_lstHeader)
       {
           if (strHead == "No." || strHead == QObject::tr("Operator"))
           {
               continue;
           }
           listData.push_back(strHead);
       }
       addContainElementType(listData); // protein... protein...
       listVar.push_back(listData);
       listData.clear();

       for (int nRow = 0; nRow < m_model->rowCount(); nRow++)
       {
           for (int nColumn = 1; nColumn < m_model->columnCount() - 1; nColumn++)
           {
               QVariant varData = m_model->data(m_model->index(nRow, nColumn));
               listData.push_back(varData);
           }
           addContainElementValue(listData);
           listVar.push_back(listData);
           listData.clear();
       }

       m_pExcelFile->writeCurrentSheet(listVar);
       m_pExcelFile->closeExecFile();

       OleUninitialize();
       m_pWaitingWidget->StopWaiting();
     }

    void PrepareTableWidget::deleteOperatorWidget()
    {
        int row = m_model->rowCount();
        for (int iIndex = 0; iIndex < row; iIndex++)
        {
            TableOperBtnWidget* pWidget = static_cast<TableOperBtnWidget*>(m_pUi->m_listViewRecipe->indexWidget(m_model->index(iIndex, m_lstHeader.size() - 1)));
            if (nullptr != pWidget)
            {
                pWidget->allBtnHide();
            }
        }
    }

}