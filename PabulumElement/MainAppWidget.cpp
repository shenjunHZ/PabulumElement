#include "MainAppWidget.h"
#include "ui_MainAppWidget.h"
#include "commonControl.h"
#include "ExecFileOperation.h"
#include "Tools/Dir.h"
#include "TableOperBtnWidget.h"
#include "MessageBox/MessageBox.h"
#include "RecipeElementWidget.h"

#include <QtGui/QPixmap>
#include <QtCore/QString>

namespace mainApp
{
    MainAppWidget::MainAppWidget(QWidget* pParent /*= nullptr*/)
        : QWidget(pParent)
        , m_pUi(nullptr)
        , m_pExcelFile(nullptr)
        , m_model(nullptr)
        , m_pCurEnteredItem(nullptr)
        , m_pRecipeElementWidget(nullptr)
    {
        m_pUi = new Ui::MainAppWidget();
        m_pUi->setupUi(this);

        initUI();
        connectSgn();
        SET_MODULE_STYLE_BY_PATH("MainAppWidget");
    }

    MainAppWidget::~MainAppWidget()
    {
        m_pRecipeElementWidget = nullptr;
    }

    void MainAppWidget::initUI()
    {
        QString strExcelFile = DSGUI::DSDir::GetCurrentPath() + "/PabulumElementTale.xlsx";
        m_pExcelFile = new ExecFileOperation(strExcelFile);
        QRegExp regx("^(([0-9]+\\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\\.[0-9]+)|([0-9]*[1-9][0-9]*))$");
        QValidator *validator = new QRegExpValidator(regx, m_pUi->m_editElement);
        m_pUi->m_editElement->setValidator(validator);

        QVariant var;
        if (m_pExcelFile->readSheetAllData(var))
        {
            m_pExcelFile->castVariantToList(var, m_listData);
        }
        for (int iRecipe = 1; iRecipe < m_listData.size(); iRecipe++)
        {
            QVariant var = m_listData[iRecipe][0];
            QString strRecipe = var.toString();

            if (!strRecipe.isEmpty())
            {
                m_pUi->m_cmbRecipe->addItem(strRecipe);
            }
        }

        initListCtrl();
    }

    void MainAppWidget::connectSgn()
    {
        connect(m_pUi->m_btnAdd,    SIGNAL(clicked()), this, SLOT(onAddRecipe()));
        connect(m_pUi->m_btnNext,   SIGNAL(clicked()), this, SIGNAL(sgnNextWidget()));
        connect(m_pUi->m_btnCreate, SIGNAL(clicked()), this, SLOT(onCreateData()));
        connect(m_pUi->m_btnClear,  SIGNAL(clicked()), this, SLOT(onClearList()));
    }

    void MainAppWidget::initListCtrl()
    {
        QStringList lstHeader;
        QList<QVariant> listVar = m_listData[0];
        for (int iIndex = 1; iIndex < listVar.size() && listVar[iIndex].isValid(); iIndex++)
        {
            if (1 == iIndex)
            {
                lstHeader <<"No." << QObject::tr("Recipe") << QObject::tr("Constituent") << listVar[iIndex].toString();
            }
            else
            {
                lstHeader<< listVar[iIndex].toString();
            }
        }
        lstHeader << QObject::tr("Operator");

        m_model = new QStandardItemModel(0, lstHeader.count());
        m_pUi->m_listViewRecipe->setModel(m_model);
        m_pUi->m_listViewRecipe->setColumnWidth(Recipe_View_Column_Num, 30);
        int begin = 0;
        foreach(QString name, lstHeader)
        {
            m_model->setHeaderData(begin, Qt::Horizontal, name);
            m_model->setHeaderData(begin, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
            begin++;
        }
    }

    void MainAppWidget::tableOperateBtn(int nRow, int nCol, QStandardItem* item)
    {
        if (m_model == nullptr)
        {
            return;
        }

        TableOperBtnWidget* pOperateWidget = new TableOperBtnWidget(this);

        // 删除按钮
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

    void MainAppWidget::setRecipeElementWidget(RecipeElementWidget* pWidget)
    {
        m_pRecipeElementWidget = pWidget;
    }

    void MainAppWidget::onTableOperIndex(QStandardItem* pItem)
    {
        m_pCurEnteredItem = pItem;
    }

    void MainAppWidget::onAddRecipe()
    {
        int iIndex = m_pUi->m_cmbRecipe->currentIndex();
        QString strData = m_pUi->m_cmbRecipe->currentText();
        QString strValue = m_pUi->m_editElement->text();
        if(strValue.isEmpty())
        {
            return;
        }

        if (strData == m_listData[iIndex + 1][0])
        {
            //新增记录，直接插入新行
            int nRow = m_model->rowCount();
            /*****************************/
            if (nRow > 2)
            {
                return;
            }
            /*****************************/
            QStandardItem* item = new QStandardItem();
            m_model->insertRow(nRow, item);

            QString strText = QString("%1").arg(nRow + 1);
            m_model->setData(m_model->index(nRow, Recipe_View_Column_Num), strText); // 序号
            m_model->setData(m_model->index(nRow, Recipe_View_Column_Num + 1), strData); // 配料
            m_model->setData(m_model->index(nRow, Recipe_View_Column_Num + 2), strValue); // 配方

            for (int iRecipe = 1; iRecipe < m_listData[iIndex].size(); iRecipe++)
            {
                // 含量
                QString strTemp = m_listData[iIndex + 1][iRecipe].toString();
                m_model->setData(m_model->index(nRow, Recipe_View_Column_Num + 2 + iRecipe), m_listData[iIndex + 1][iRecipe].toString());
            }

            tableOperateBtn(nRow, Recipe_View_Column_Num + 1 + m_listData[iIndex].size(), item);
            QStandardItem *tempItem = new QStandardItem(); // 最后一个添加总是没有对齐
            m_model->insertRow(nRow + 1, tempItem);
            m_model->removeRow(nRow + 1);
        }
    }

    void MainAppWidget::onDelBtnClicked()
    {
        // 弹出“是否确定删除”提示框
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

    void MainAppWidget::onCreateData()
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

    void MainAppWidget::onClearList()
    {
        if (nullptr != m_model)
        {
            m_model->removeRows(0, m_model->rowCount());
        }
    }

}