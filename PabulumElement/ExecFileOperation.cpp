#include "ExecFileOperation.h"

#include <MessageNotify/MessageNotify.h>

const int g_iWorkSheetIndex = 1;

namespace mainApp
{

    ExecFileOperation::ExecFileOperation(QString strFilePathName)
        : m_filePathName(strFilePathName),
        m_pAxObject(nullptr),
        m_pWorkBooks(nullptr),
        m_pWorkBook(nullptr),
        m_pWorkSheets(nullptr),
        m_pWorkSheet(nullptr)
    {
        init();
    }

    ExecFileOperation::~ExecFileOperation()
    {
        openExecFile();

        m_pWorkSheet = nullptr;
        m_pWorkSheets = nullptr;
        m_pWorkBook = nullptr;
        m_pWorkBooks = nullptr;
        delete m_pAxObject;
        m_pAxObject = nullptr;
    }

    void ExecFileOperation::init()
    {
        //m_pAxObject = new QAxObject(this);
        //bool bRet = m_pAxObject->setControl("Excel.Application"); // ����excel�ؼ�
        m_pAxObject = new QAxObject("Excel.Application", this);
        if (!m_pAxObject)
        {
            DSGUI::DSMessageNotify::Instance().AddTextNotification(QObject::tr("Application excel filed!"));
            return;
        }
        QVariant var = m_pAxObject->dynamicCall("SetVisible (bool Visible)", "false"); // ����ʾ����
        m_pAxObject->setProperty("DisplayAlerts", false); // ����ʾ�κξ���

        m_pWorkBooks = m_pAxObject->querySubObject("WorkBooks"); // ��ȡ����������

        openExecFile();
    }

    bool ExecFileOperation::openExecFile()
    {
        if (m_filePathName.isEmpty())
        {
            DSGUI::DSMessageNotify::Instance().AddTextNotification(QObject::tr("Open excel filed!"));
            return false;
        }

        QVariant var = m_pWorkBooks->dynamicCall("Open (const QString&)", m_filePathName);
        int iVar = var.toInt();
        QVariant varTitle = m_pAxObject->property("Caption"); // ��ȡ����
        QString strTitle = varTitle.toString();

        m_pWorkBook = m_pAxObject->querySubObject("ActiveWorkBook"); // ��ȡ��ǰ������
        m_pWorkSheets = m_pWorkBook->querySubObject("Sheets"); // ��ȡ��������
        m_pWorkSheet = m_pWorkSheets->querySubObject("Item(int)", g_iWorkSheetIndex); //��ȡ�������ϵı�1

        return true;
    }

    bool ExecFileOperation::readSheetAllData(QVariant& var)
    {
        if (!m_pWorkSheet || m_pWorkSheet->isNull())
        {
            DSGUI::DSMessageNotify::Instance().AddTextNotification(QObject::tr("Read excel filed!"));
            return false;
        }

        QAxObject* pUsedRange = m_pWorkSheet->querySubObject("UsedRange"); // ��ȡ���з�Χ
        if (!pUsedRange || pUsedRange->isNull())
        {
            DSGUI::DSMessageNotify::Instance().AddTextNotification(QObject::tr("Read excel filed!"));
            return false;
        }

        var = pUsedRange->dynamicCall("Value");
        delete pUsedRange;
        pUsedRange = nullptr;
        closeExecFile();

        return true;
    }

    bool ExecFileOperation::castVariantToList(const QVariant& var, QList<QList<QVariant>>& listRes)
    {
        QVariantList varRows = var.toList();
        if (varRows.isEmpty())
        {
            return false;
        }

        int rowCount = varRows.size();
        for (int iIndex = 0; iIndex < rowCount; iIndex++)
        {
            QVariantList rowData = varRows[iIndex].toList();
            listRes.push_back(rowData); // �������ݴ��
        }
        return true;
    }

    void ExecFileOperation::closeExecFile()
    {
        if (!m_pWorkBook || !m_pAxObject)
        {
            return;
        }
        m_pWorkBook->dynamicCall("Close()"); // �رչ�����
        m_pAxObject->dynamicCall("Quit()"); // �ر�excel
    }

}