#include "MysqlDB.h"
#include "libdsl/DStr.h"
#include "libdsl/DPrintLog.h"

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QtSql/QSqlError>
#include <QtCore/QVariant>
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>
#include <QString>

namespace MysqlDB
{

    CMysqlDB::CMysqlDB() : m_MaterialTable("")
    {
 		//qDebug() << QSqlDatabase::drivers();
 		//qDebug() << QCoreApplication::libraryPaths();

        m_Database = QSqlDatabase::addDatabase("QMYSQL", "MySqlLink");
    }

    CMysqlDB::~CMysqlDB()
    {
        m_Database.close();
    }

    bool CMysqlDB::connectToSql(const QString& strHostName, const int& iPort, const QString& strUserName, const QString& strPassword)
    {
        m_Database.close();
 
        m_Database.setHostName(strHostName);
        m_Database.setPort(iPort);
        m_Database.setDatabaseName("MaterialsDataBase");
        m_Database.setUserName(strUserName);
        m_Database.setPassword(strPassword);
        QString strLogInfo;
        QString strPort = QString::number(iPort);
        strLogInfo = "host: " + strHostName + ",port: " + strPort + ",Name: " + strUserName + ",Password: " + strPassword;
        DLOG_INFO("%s", strLogInfo.toStdString().c_str());

        bool bOpen = m_Database.open();
        if (!bOpen)
        {
            QString strErr = m_Database.lastError().databaseText();
            DLOG_ERR("Open mysql database error: %s", strErr.toStdString().c_str());

            QString strErrCode = m_Database.lastError().nativeErrorCode();
            QString strText = m_Database.lastError().text();
            DLOG_ERR("mysql database error code: %s, error info: %s", 
                strErrCode.toStdString().c_str(), strText.toStdString().c_str());
        }
        return bOpen;
    }

    bool CMysqlDB::IsTableExist(QString& strTableName)
    {
        char szInfo[256] = { 0 };
        dsl::DStr::sprintf_x(szInfo, sizeof(szInfo), "SELECT table_name FROM information_schema.TABLES WHERE table_name ='%s';",
            strTableName.toStdString().c_str());
        QString strQuery = QString::fromStdString(szInfo);

        QSqlQuery query = QSqlQuery::QSqlQuery(m_Database);
        bool bQuery = query.exec(strQuery);
        if (!bQuery)
        {
            return true;
        }

        while (query.next())
        {
            QSqlRecord record = query.record(); // ���ر��β�ѯ���м�¼
            if (record.count() > 0)
            {
                return true;
            }
        }
        return false;
    }

    bool CMysqlDB::createTable(QString& strTable)
    {
        /******************************************************************************************
        ������		���ֶδ�С�Ǹ���server db������
        ID						bigint,						�Զ����
        ACRONYM 				varchar(64),				������
        DEFINITION				varchar(512),				�����и��ɷֵĶ���
        ******************************************************************************************/
        m_MaterialTable = strTable;
        bool bFlag = false;
        if (IsTableExist(strTable))
        {
            bFlag = true;
        }
        else
        {
            char szCreateTbSql[1024] = { 0 };
            dsl::DStr::sprintf_x(szCreateTbSql, sizeof(szCreateTbSql),
                "CREATE TABLE %s(ID bigint NOT NULL PRIMARY KEY,\
                ACRONYM varchar(64) NOT NULL,\
                DEFINITION varchar(512) NOT NULL);", strTable.toStdString().c_str());
            QString strQuery = QString::fromStdString(szCreateTbSql);

            QSqlQuery query = QSqlQuery::QSqlQuery(m_Database);
            bFlag = query.exec(strQuery);
        }

        return bFlag;
        // ���������о�����һ���л���е���ϣ���ֵ��Ψһ�ر�ʶ���е�ÿһ��(�����ظ�)��
        // ���� AUTOINCREMENT �Զ����
    }

    bool CMysqlDB::addQuery(const QString& name, const QString& strDefinition)
    {
        if (!m_Database.isOpen())
        {
            return false;
        }
        
        int lastId = 0;
        
        QString sql = QString::fromStdString("select * from %1 order by ID desc limit 1").arg(m_MaterialTable); // ��ȡ���һ����Ϣ
        QSqlQuery query = QSqlQuery::QSqlQuery(m_Database);
        query.exec(sql);

        while (query.next())
        {
            lastId = query.value("ID").toInt();
        }

        int newId = lastId + 1;
        QSqlQuery queryTemp = QSqlQuery::QSqlQuery(m_Database);
        sql = QString::fromStdString("INSERT INTO %1 (ID, ACRONYM, DEFINITION) VALUES (:ID, :ACRONYM, :DEFINITION)").arg(m_MaterialTable);
        queryTemp.prepare(sql);
        queryTemp.bindValue(":ID", newId);
        queryTemp.bindValue(":ACRONYM", name);
        queryTemp.bindValue(":DEFINITION", strDefinition);
        bool bRec = queryTemp.exec();

        return bRec;
    }
    
    /**
    * 
    * @param username
    */
    std::map<int, std::string> CMysqlDB::outputWithPreparedQuery(const QString& name)
    {
        QString sql = QString::fromStdString("SELECT * FROM %1 WHERE ACRONYM=:ACRONYM").arg(m_MaterialTable);
        QSqlQuery query = QSqlQuery::QSqlQuery(m_Database);  
        query.prepare(sql);

        query.bindValue(":ACRONYM", name);
        query.exec();
        std::map<int, std::string> outPutExpression;
        while (query.next()) // loop
        {
            QString output = query.value("DEFINITION").toString();

            int iId = query.value("ID").toInt();
            outPutExpression[iId] = output.toStdString();
        }

        return  outPutExpression;
    }

    bool CMysqlDB::deleteQuery(const int id)
    {
        QSqlQuery query = QSqlQuery::QSqlQuery(m_Database);

        QString strNum = QString::number(id);
        QString strSQL = QString::fromStdString("delete from %1 where ID = %2").arg(m_MaterialTable).arg(strNum);

        return query.exec(strSQL); //delete from MeterialsDataBase where ID = '" + id + "'
    }

    std::map<QString, QString> CMysqlDB::queryAllMaterial()
    {
        char szSelectSql[1024] = { 0 };
        dsl::DStr::sprintf_x(szSelectSql, sizeof(szSelectSql),
            "select * from %s", m_MaterialTable.toStdString().c_str());
        std::map<QString, QString> mapMaterials;

        QString strQuery = QString::fromStdString(szSelectSql);
        QSqlQuery query = QSqlQuery::QSqlQuery(m_Database);
        bool bQuery = query.exec(strQuery);
        if (!bQuery)
        {
            return mapMaterials;
        }

        while (query.next())
        {
            QSqlRecord record = query.record();
            int iCount = record.count(); // fields count "id key value%"
            //for (int i = 0; i < record.count(); i++)
            {
                QString strAcronym = record.value("ACRONYM").toString();
                QString strDefinition = record.value("DEFINITION").toString();
                mapMaterials[strAcronym] = strDefinition;
            }
        }
        return mapMaterials;
    }

    bool CMysqlDB::updateDefinition(uint64_t iPrimaryKey, std::string strDefinition)
    {
        char szSelectSql[1024] = { 0 };

        dsl::DStr::sprintf_x(szSelectSql, sizeof(szSelectSql),
            "UPDATE %s SET DEFINITION = '%s' WHERE ID = %lu;", m_MaterialTable.toStdString().c_str(), strDefinition.c_str(), iPrimaryKey);

        QString strQuery = QString::fromStdString(szSelectSql);
        QSqlQuery query = QSqlQuery::QSqlQuery(m_Database);
        return query.exec(strQuery);
    }

}