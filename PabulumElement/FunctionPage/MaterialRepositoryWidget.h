/*
@tool    Abbreviation Search Main interface
@author  sj
@data    2017-9-3
@version 1.0
*/
#pragma once

#include <QtWidgets/QWidget>
#include <memory>

#include "Dialog/Dialog.h"

namespace Ui
{
    class MaterialRepositoryWidget;
}

namespace MysqlDB
{
    class CMysqlDB;
}

namespace mainApp
{

    typedef enum class widgetType
    {
        WIDGET_TYPE_SEARCH = 0,
        WIDGET_TYPE_ADD    = 1,
        WIDGET_TYPE_DELETE = 2,
        WIDGET_TYPE_UPDATE = 3,
        WIDGET_TYPE_UNKNOW = 4,
    }widgetType_e;

    class MaterialRepositoryWidget : public DSGUI::DSDialog
    {
        Q_OBJECT

    public:
        MaterialRepositoryWidget(std::shared_ptr<MysqlDB::CMysqlDB> ptrMysqlDB, QWidget* pParent = nullptr);
        ~MaterialRepositoryWidget();

    private:
        void InitUI();
        void SetSelectWidgetType(widgetType_e nType);
        void ConnectSgn();
        bool createTable();
        void ShowNotifyDlg(const QString& strNotify) const;

    signals:
        void sgnShowNotifyDlg(QString& strNotify);
        void sgnAddDefinition();
        void sgnModifyDefinition();
        void sgnDelDefinition();

    private slots:
        void OnCurrentIndexChanged(int nIndex);
        void OnSearchBtnClicked(QString& strSearchWord);
        //void OnConfigWidgetShow();
        void OnShowNotifyDlg(QString& strNotify);
        //void OnConnectSQL(SQLConnectInfo_s& info);

    private:
        Ui::MaterialRepositoryWidget*              m_pUi;
        //ConfigSQLConnectInfo*           m_pConfigWidget;
        //SqliteDB::CSqliteDB*            m_pSqliteDB; // local SQL
        //SqliteDB::AbbreviationTable*    m_pAbbreviationTable;
        std::shared_ptr<MysqlDB::CMysqlDB>              m_pMysqlDB;
        //SQLType_e                       m_sqlType;
    };
}