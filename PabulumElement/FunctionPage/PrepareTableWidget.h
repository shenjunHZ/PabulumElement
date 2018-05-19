/*
@function    main widget
@author  sj
@data    2018-1-22
@version 1.0
*/
#pragma once

#include <QtWidgets/QWidget>
#include <QtGui/QStandardItem>
#include <memory>
#include <thread>
#include <unordered_map>
#include "HomePage/ViewDefine.h"

namespace Ui
{
    class PrepareTableWidget;
}

namespace MysqlDB
{
    class CMysqlDB;
}

namespace mainApp
{
    class ExecFileOperation;
    class WordFileOperation;
    class RecipeElementWidget;
    class WaitingWidget;

    class PrepareTableWidget : public QWidget
    {
        Q_OBJECT

    public:
        PrepareTableWidget(QWidget* pParent = nullptr);
        ~PrepareTableWidget();

        void setRecipeElementWidget(RecipeElementWidget* pWidget);
        void SetAbbreviationTable(std::shared_ptr<MysqlDB::CMysqlDB> pMysqlDB);

    private:
        void initUI();
        void initListCtrl();
        void updateListCtrl();
        void connectSgn();
        void tableOperateBtn(int nRow, int nCol, QStandardItem* item);
        void decodeDefinition(std::map<QString, std::map<QString, QString>>& mapContains,
            std::map<QString, QString>& mapMaterials);
        void prepareOfficialData();
        QString getRecipeData();
        void initDatabaseCombobox();
        void addRecipeFromExcel(QList<QList<QVariant>>& listData);
        bool needRefreshListCtrl(const QString& strTitle);
        void addHeadListCtrl();
        void addContainElementType(QList<QVariant>& listData);
        void addContainElementValue(QList<QVariant>& listData);

        void waitForSaveFiles(QString strFileName, QString strExcelFileName);
        void deleteOperatorWidget();
        void inportRecipeExcel(QString strFilePath);

    signals:
        void sgnNextWidget();
        void sgnCreateData();

    private slots:
        void onAddRecipe();
        void onTableOperIndex(QStandardItem* pItem);
        void onDelBtnClicked();
        void onCreateData();
        void onClearList();
        void onExport();
        void onInportRecipeExcel();
        void onTextChanged(const QString & text);

    private:
        Ui::PrepareTableWidget*    m_pUi;
        ExecFileOperation*         m_pExcelFile;
        WordFileOperation*         m_pWordFile;
        QList<QList<QVariant>>     m_listData;     // data from excel
        std::map<QString, QString> m_mapMaterials; // data from database
        std::map<QString, std::map<QString, QString>> m_mapContains;  // after decode data form database
        QStandardItemModel*        m_model;
        QStandardItemModel*        m_modelTmp;
        QStringList                m_lstHeader;
        std::vector<QString>       m_listElements; // all elements by have add materials
        QStandardItem*             m_pCurEnteredItem;         
        RecipeElementWidget*       m_pRecipeElementWidget;
        WaitingWidget*             m_pWaitingWidget;
        std::shared_ptr<MysqlDB::CMysqlDB> m_pMysqlDB;
        std::thread*               m_pThread;
    };
}