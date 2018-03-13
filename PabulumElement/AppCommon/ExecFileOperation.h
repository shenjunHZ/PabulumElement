/*
@function    use for operation excel file
@author  sj
@data    2018-1-23
@version 1.0
*/
#pragma once

#include <QString>
#include <QtCore/QScopedPointer>
#include <ActiveQt/QAxObject>

namespace mainApp
{
    class ExecFileOperation : public QAxObject
    {
        Q_OBJECT

    public:
        ExecFileOperation(/*QString strFilePathName*/);
        ~ExecFileOperation();

        bool readSheetAllData(QVariant& var);
        bool ExecFileOperation::writeCurrentSheet(const QList<QList<QVariant> > &cells);
        void setFilePathName(QString strFilePathName);
        bool openExecFile();
        void closeExecFile();
        bool castVariantToList(const QVariant& var, QList<QList<QVariant>>& listRes);
        void saveFile();

    private:
        void init();
        void castListListVariant2Variant(const QList<QList<QVariant>> &cells, QVariant& var);
        void convertToColName(int data, QString &res);
        QString to26AlphabetString(int data);

    private:
        bool    m_bNewFile;
        QString m_filePathName;
        QAxObject* m_pAxObject;
        QAxObject* m_pWorkBooks;
        QAxObject* m_pWorkBook;
        QAxObject* m_pWorkSheets;
        QAxObject* m_pWorkSheet;
    };
}