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
        //bool bRet = m_pAxObject->setControl("Excel.Application"); // 连接excel控件
        m_pAxObject = new QAxObject("Excel.Application", this);
        if (!m_pAxObject)
        {
            DSGUI::DSMessageNotify::Instance().AddTextNotification(QObject::tr("Application excel filed!"));
            return;
        }
        QVariant var = m_pAxObject->dynamicCall("SetVisible (bool Visible)", "false"); // 不显示窗体
        m_pAxObject->setProperty("DisplayAlerts", false); // 不显示任何警告

        m_pWorkBooks = m_pAxObject->querySubObject("WorkBooks"); // 获取工作簿集合

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
        QVariant varTitle = m_pAxObject->property("Caption"); // 获取标题
        QString strTitle = varTitle.toString();

        m_pWorkBook = m_pAxObject->querySubObject("ActiveWorkBook"); // 获取当前工作簿
        m_pWorkSheets = m_pWorkBook->querySubObject("Sheets"); // 获取工作表集合
        m_pWorkSheet = m_pWorkSheets->querySubObject("Item(int)", g_iWorkSheetIndex); //获取工作表集合的表1

        return true;
    }

    bool ExecFileOperation::readSheetAllData(QVariant& var)
    {
        if (!m_pWorkSheet || m_pWorkSheet->isNull())
        {
            DSGUI::DSMessageNotify::Instance().AddTextNotification(QObject::tr("Read excel filed!"));
            return false;
        }

        QAxObject* pUsedRange = m_pWorkSheet->querySubObject("UsedRange"); // 读取所有范围
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
            listRes.push_back(rowData); // 按行内容存放
        }
        return true;
    }

    void ExecFileOperation::closeExecFile()
    {
        if (!m_pWorkBook || !m_pAxObject)
        {
            return;
        }
        m_pWorkBook->dynamicCall("Close()"); // 关闭工作簿
        m_pAxObject->dynamicCall("Quit()"); // 关闭excel
    }

}