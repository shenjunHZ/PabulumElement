/*
@function    use for operation exec file
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
        ExecFileOperation(QString strFilePathName);
        ~ExecFileOperation();

        bool readSheetAllData(QVariant& var);
        bool castVariantToList(const QVariant& var, QList<QList<QVariant>>& listRes);

    private:
        void init();
        bool openExecFile();
        void closeExecFile();

    private:
        QString m_filePathName;
        QAxObject* m_pAxObject;
        QAxObject* m_pWorkBooks;
        QAxObject* m_pWorkBook;
        QAxObject* m_pWorkSheets;
        QAxObject* m_pWorkSheet;
    };
}