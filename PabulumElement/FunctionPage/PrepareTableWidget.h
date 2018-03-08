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
        void decodeDefinition(std::map<QString, std::map<QString, QString>>& mapContains, std::map<QString, QString>& mapMaterials);
        void prepareOfficialData();
        QString getRecipeData();
        void initDatabaseCombobox();
        void addRecipeFromExcel(QList<QList<QVariant>>& listData);
        bool needRefreshListCtrl(const QString& strTitle);
        void addHeadListCtrl();

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

    private:
        Ui::PrepareTableWidget*    m_pUi;
        ExecFileOperation*         m_pExcelFile;
        WordFileOperation*         m_pWordFile;
        QList<QList<QVariant>>     m_listData;     // data from excel
        std::map<QString, QString> m_mapMaterials; // data from database
        QStringList                m_lstHeader;
        QStandardItemModel*        m_model;
        QStandardItemModel*        m_modelTmp;
        std::map<QString, std::map<QString, QString>> m_mapContains;  // after decode data form database
        std::vector<QString>       m_listElements; // all elements by add materials
        QStandardItem*         m_pCurEnteredItem;         
        RecipeElementWidget* m_pRecipeElementWidget;
        std::shared_ptr<MysqlDB::CMysqlDB> m_pMysqlDB;
    };
}