#pragma once

#include <QtCore/QObject>
#include <QAxObject>

namespace mainApp
{
    class WordFileOperation : public QObject
    {
        Q_OBJECT

    public:
        WordFileOperation();
        ~WordFileOperation();

        bool openFile(QString& strDotFile, bool bVisible = true);

        void saveFile(QString sSaveFilePath);

        void closeFile();

        bool replaceText(QString sLabel, QString sText);

        bool replacePic(QString sLabel, QString sFile);
        // insert a table 
        QAxObject *insertTable(QString sLabel, int row, int column);
        // insert a table and set table title
        QAxObject *insertTable(QString sLabel, int row, int column, QStringList headList);
         
        void setColumnWidth(QAxObject *table, int column, int width);

        void SetTableCellString(QAxObject *table, int row, int column, QString text);

    private:

        QAxObject *m_pWord;           // Word application
        QAxObject *m_pWorkDocuments;  // Word documents
        QAxObject *m_pWorkDocument;   // specific document  

        QString m_sFile;
        bool    m_bIsOpen;
        bool    m_bNewFile;
    };
}