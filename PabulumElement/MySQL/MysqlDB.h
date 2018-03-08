/*
Qt提供的对不同数据库的驱动支持：

Driver Type Description：
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
        strHostName: 数据库地址
        iPort: 数据库端口
        strUserName: 用户名
        strPassword: 密码
        */
        bool connectToSql(const QString& strHostName, const int& iPort, const QString& strUserName, const QString& strPassword);

        /*
        create table
        strTbale: 创建表名
        */
        bool createTable(QString& strTable);

        std::map<int, std::string> outputWithPreparedQuery(const QString &name);
        /* 
        add material 
        name: 配料名（787）
        expresion: 营养素含量（单价:4,蛋白质:88,钠:1.4,脂肪:3.2）
        展示的时候解析数据
        */
        bool addQuery(const QString& name, const QString& strDefinition);
        /*
        update meterial
        iParimaryKey: 存储ID号
        strDefinition: 
        */
        bool updateDefinition(uint64_t iPrimaryKey, std::string strDefinition);
        /*
        delete material
        id : 存储ID号
        */
        bool deleteQuery(const int id);
        /*
        query all material data
        */
        std::map<QString, QString> queryAllMaterial();

    private:
        /*
        table
        判断数据库中表格是否已存在
        */
        bool IsTableExist(QString& strTableName);

    private:
        QSqlDatabase m_Database;
        QString      m_MaterialTable;
    };
}
