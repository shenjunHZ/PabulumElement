/*
@tool    Abbreviation Search Function interface
@author  sj
@data    2017-9-8
@version 1.0
*/
#pragma once

#include <QWidget>
#include <memory>

#include "ui_AbbreviationFunctionSearch.h"
#include "HomePage/ViewDefine.h"

namespace Ui
{
    class AbbreviationFunctionSearch;
}
namespace MysqlDB
{
    class CMysqlDB;
}

namespace mainApp
{
    class ModifyDefinitionDialog;

    class AbbreviationFunctionSearch : public QWidget
    {
        Q_OBJECT

    public:
        AbbreviationFunctionSearch(QWidget *parent = Q_NULLPTR);
        ~AbbreviationFunctionSearch();

        // set search word text
        bool SetAcronymText(const QString& strText);
        // db table
        void SetAbbreviationTable(std::shared_ptr<MysqlDB::CMysqlDB> pMysqlDB);

        //void SetSQLType(const SQLType_e& type);

    signals:
        void sgnModifyDefinition();
        void sgnDelDefinition();
        void sgnAddComboItem(const std::vector<AbbreviationInfo_s>&);

    private:
        void InitUI();
        void ConnectSgn();
        // add definition list info
        bool AddDefinition(const std::vector<AbbreviationInfo_s>& vecDefinition);
        // add definition info
        bool AddDefinition(const AbbreviationInfo_s& Definition);
        // search from sql
        bool SearchDefinitionFromSQL(const QString& strText);
        // clear definition list info
        bool ClearDefinition();
        // delete definition by Primary Key
        bool DeleteDefinition(uint64_t iPrimaryKey, QListWidgetItem* pItem);
        // modify definition by Primary Key
        bool editDefinition(uint64_t iPrimaryKey, QListWidgetItem* pItem);

    private slots:
        void OnDeleteDefinition(uint64_t iPrimaryKey, QListWidgetItem* pItem);
        void OnItemDoubleClicked(QListWidgetItem* pItem);
        void OnEditDefinition(uint64_t iPrimaryKey, QListWidgetItem* pItem);
        void onModifyDefinition(uint64_t iPrimaryKey, std::string strDefinition);
        void onCurrentIndexChanged(int iIndex);

    private:
        Ui::AbbreviationFunctionSearch* m_pUi;

        std::shared_ptr<MysqlDB::CMysqlDB>              m_pMysqlDB;
        std::vector<AbbreviationInfo_s> m_vecDefinitionInfos;
        ModifyDefinitionDialog*         m_pModifyDefinitionDialog;
    };

} // end namesapce mainApp
