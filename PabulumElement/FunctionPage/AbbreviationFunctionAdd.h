/*
@tool    Abbreviation add Function interface
@author  sj
@data    2017-9-8
@version 1.0
*/
#pragma once

#include <QtWidgets/QWidget>
#include <memory>

#include "HomePage/ViewDefine.h"

namespace Ui
{
    class AbbreviationFunctionAdd;
}

namespace MysqlDB
{
    class CMysqlDB;
}

namespace mainApp
{
    class AbbreviationFunctionAdd : public QWidget
    {
        Q_OBJECT

    public:
        AbbreviationFunctionAdd(QWidget* pParent = nullptr);
        ~AbbreviationFunctionAdd();
        // search from sql
        void SetAbbreviationTable(std::shared_ptr<MysqlDB::CMysqlDB> pMysqlDB);

        //void SetSQLType(const SQLType_e& type);

    signals:
        void sgnAddDefinition();

    protected:
        //void mousePressEvent(QMouseEvent *event);

    private:
        void ConnectSgn();
        // search from sql
        bool AddDefinitionFromSQL(const AbbreviationInfo_s& sInfo);

    private slots:
        void OnSaveClicked();
        void OnCancelClicked();
        void onTextChanged();
        //void onCursorPositionChanged();

    private:
        Ui::AbbreviationFunctionAdd*    m_pUi;
        //SqliteDB::AbbreviationTable*    m_pAbbreviationTable;
        std::shared_ptr<MysqlDB::CMysqlDB>              m_pMysqlDB;
        //SQLType_e                       m_sqlType;
    };
}