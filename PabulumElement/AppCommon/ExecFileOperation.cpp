#include "ExecFileOperation.h"

#include <MessageNotify/MessageNotify.h>

const int g_iWorkSheetIndex = 1;

namespace mainApp
{

    ExecFileOperation::ExecFileOperation(/*QString strFilePathName*/)
        : m_filePathName(""),
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
        closeExecFile();

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

        //openExecFile();
    }

    void ExecFileOperation::setFilePathName(QString strFilePathName)
    {
        m_filePathName = strFilePathName;
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
            listRes.push_back(rowData); // accord to the row data
        }
        return true;
    }

    void ExecFileOperation::castListListVariant2Variant(const QList<QList<QVariant>> &cells, QVariant& var)
    {
        var.setValue<QList<QList<QVariant>>>(cells);
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

    bool ExecFileOperation::writeCurrentSheet(const QList<QList<QVariant> > &cells)
    {
        if (cells.size() <= 0)
        {
            return false;
        }
        if (nullptr == m_pWorkSheet || m_pWorkSheet->isNull())
        {
            return false;
        }
        int row = cells.size();
        int col = cells.at(0).size();
        QString rangStr;
        convertToColName(col, rangStr);
        rangStr += QString::number(row);
        rangStr = "A1:" + rangStr;
        //qDebug() << rangStr;
        QAxObject *range = m_pWorkSheet->querySubObject("Range(const QString&)", rangStr);
        if (NULL == range || range->isNull())
        {
            return false;
        }
        bool succ = false;
        QVariant var;
        castListListVariant2Variant(cells, var);
        succ = range->setProperty("Value", var);
        delete range;
        return succ;
    }

    // brief 把列数转换为excel的字母列号
    // param data 大于0的数
    // return 字母列号，如1->A 26->Z 27 AA
    void ExecFileOperation::convertToColName(int data, QString &res)
    {
        Q_ASSERT(data > 0 && data < 65535);
        int tempData = data / 26;
        if (tempData > 0)
        {
            int mode = data % 26;
            convertToColName(mode, res);
            convertToColName(tempData, res);
        }
        else
        {
            res = (to26AlphabetString(data) + res);
        }
    }

    // brief 数字转换为26字母
    // 1->A 26->Z
    QString ExecFileOperation::to26AlphabetString(int data)
    {
        QChar ch = data + 0x40;//A对应0x41
        return QString(ch);
    }

}