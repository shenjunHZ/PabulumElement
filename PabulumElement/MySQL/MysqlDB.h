/*
Qt�ṩ�ĶԲ�ͬ���ݿ������֧�֣�

Driver Type Description��
QDB2        IBM DB2
QIBASE      Borland InterBase Driver
QMYSQL      MySQL Driver
QOCI        Oracle Call Interface Driver
QODBC       ODBC Driver (includes Microsoft SQL Server)
QPSQL       PostgreSQL Driver
QSQLITE     SQLite version 3 or above
QSQLITE2    SQLite version 2
QTDS        Sybase Adaptive Server

*/
#pragma once

#include <vector>
#include <QtSql/QSqlDatabase>
#include <map>

namespace MysqlDB
{
    class CMysqlDB
    {
    public:
        CMysqlDB();
        ~CMysqlDB();

        /*
        connect database
        strHostName: ���ݿ��ַ
        iPort: ���ݿ�˿�
        strUserName: �û���
        strPassword: ����
        */
        bool connectToSql(const QString& strHostName, const int& iPort, const QString& strUserName, const QString& strPassword);

        /*
        create table
        strTbale: ��������
        */
        bool createTable(QString& strTable);

        std::map<int, std::string> outputWithPreparedQuery(const QString &name);
        /* 
        add material 
        name: ��������787��
        expresion: Ӫ���غ���������:4,������:88,��:1.4,֬��:3.2��
        չʾ��ʱ���������
        */
        bool addQuery(const QString& name, const QString& strDefinition);
        /*
        update meterial
        iParimaryKey: �洢ID��
        strDefinition: 
        */
        bool updateDefinition(uint64_t iPrimaryKey, std::string strDefinition);
        /*
        delete material
        id : �洢ID��
        */
        bool deleteQuery(const int id);
        /*
        query all material data
        */
        std::map<QString, QString> queryAllMaterial();

    private:
        /*
        table
        �ж����ݿ��б���Ƿ��Ѵ���
        */
        bool IsTableExist(QString& strTableName);

    private:
        QSqlDatabase m_Database;
        QString      m_MaterialTable;
    };
}
