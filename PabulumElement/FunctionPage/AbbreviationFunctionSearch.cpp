#include "FunctionPage/AbbreviationFunctionSearch.h"
#include "FunctionPage/ModifyDefinitionDialog.h"
#include "AppCommon/commonControl.h"
#include "MySQL/MysqlDB.h"

#include <map>
#include <QtGui/QDesktopServices>
#include <QtCore/QUrl>

const int g_iDefinitionOffset = 4;

namespace mainApp
{
    AbbreviationFunctionSearch::AbbreviationFunctionSearch(QWidget *parent)
        : QWidget(parent),
        m_pUi(nullptr),
        m_pMysqlDB(nullptr),
        m_pModifyDefinitionDialog(nullptr)
    {
        m_pUi = new Ui::AbbreviationFunctionSearch();
        m_pUi->setupUi(this);
        m_vecDefinitionInfos.clear();
        m_pModifyDefinitionDialog = new ModifyDefinitionDialog();

        ConnectSgn();
        SET_MODULE_STYLE_BY_PATH("AbbreviationFunctionSearch");
    }

    AbbreviationFunctionSearch::~AbbreviationFunctionSearch()
    {
        delete m_pModifyDefinitionDialog;
        m_pModifyDefinitionDialog = nullptr;
    }

    void AbbreviationFunctionSearch::InitUI()
    {

    }

    void AbbreviationFunctionSearch::ConnectSgn()
    {
        connect(m_pUi->m_listWidgetDefinition, SIGNAL(sgnDeleteDefinition(uint64_t, QListWidgetItem*)), this, SLOT(OnDeleteDefinition(uint64_t, QListWidgetItem*)));
        connect(m_pUi->m_listWidgetDefinition, SIGNAL(sgnEditDefinition(uint64_t, QListWidgetItem*)),   this, SLOT(OnEditDefinition(uint64_t, QListWidgetItem*)));

        connect(m_pUi->m_listWidgetDefinition, SIGNAL(itemDoubleClicked(QListWidgetItem*)),             this, SLOT(OnItemDoubleClicked(QListWidgetItem*)));
        connect(m_pModifyDefinitionDialog,     SIGNAL(sgnModifyDefinition(uint64_t, std::string)),      this, SLOT(onModifyDefinition(uint64_t, std::string)));
    }

    void AbbreviationFunctionSearch::SetAbbreviationTable(std::shared_ptr<MysqlDB::CMysqlDB> pMysqlDB)
    {
        m_pMysqlDB = pMysqlDB;
    }

    bool AbbreviationFunctionSearch::SetAcronymText(const QString& strText)
    {
        if ("" == strText)
        {
            return false;
        }

        SearchDefinitionFromSQL(strText);
        return true;
    }

    bool AbbreviationFunctionSearch::ClearDefinition()
    {
        int nCount = m_pUi->m_listWidgetDefinition->count();

        for (int nIndexCount = nCount; nIndexCount > 0; nIndexCount--)
        {
            QListWidgetItem* pItem = m_pUi->m_listWidgetDefinition->item(nIndexCount - 1);
            m_pUi->m_listWidgetDefinition->removeItemWidget(pItem);
            delete pItem;
            pItem = nullptr;
        }
        m_pUi->m_listWidgetDefinition->clear();

        return true;
    }

    bool AbbreviationFunctionSearch::AddDefinition(const std::vector<AbbreviationInfo_s>& vecDefinition)
    {
        //QStringList strList;
        for (int iIndex = 0; iIndex < vecDefinition.size(); iIndex++)
        {
            //strList.push_back(QString::fromStdString(vecDefinition[iIndex].strDefinition));
            QString strDefinition = QString::fromStdString(vecDefinition[iIndex].strDefinition);
            if (!strDefinition.isEmpty())
            {
                QString strIndex = QString::number(iIndex + 1);
                QListWidgetItem *pItem = new QListWidgetItem(strIndex + ".  " + strDefinition);
                QFont font = pItem->font();
                font.setPixelSize(16);
                pItem->setFont(font);
                QStringList strList = strDefinition.split("\n");
                pItem->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
                //pItem->setToolTip(strDefinition);
                if (0 == iIndex % 2)
                {
                    //pItem->setBackgroundColor(QColor(201, 81, 0));
                    pItem->setBackgroundColor(QColor(58, 62, 67));
                }
                else
                {
                    pItem->setBackgroundColor(QColor(53, 57, 62));
                }
                pItem->setFlags(pItem->flags() & ~Qt::ItemIsSelectable);
                pItem->setData(Qt::UserRole, vecDefinition[iIndex].iPrimaryKey); 
                QSize size(100, 40 * strList.size());
                pItem->setSizeHint(size);
                m_pUi->m_listWidgetDefinition->addItem(pItem);
            }
        }

        return true;
    }

    bool AbbreviationFunctionSearch::AddDefinition(const AbbreviationInfo_s& Definition)
    {
        QString strDefinition = QString::fromStdString(Definition.strDefinition);
        if (!strDefinition.isEmpty())
        {
            int iIndex = m_pUi->m_listWidgetDefinition->count();
            QString strIndex = QString::number(iIndex + 1);
            QListWidgetItem *pItem = new QListWidgetItem(strIndex + ".  " + strDefinition);
            QFont font = pItem->font();
            font.setPixelSize(16);
            pItem->setFont(font);
            QStringList strList = strDefinition.split("\n");
            pItem->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
                
            if (0 == iIndex % 2)
            {
                pItem->setBackgroundColor(QColor(58, 62, 67));
            }
            else
            {
                pItem->setBackgroundColor(QColor(53, 57, 62));
            }
            pItem->setFlags(pItem->flags() & ~Qt::ItemIsSelectable);
            pItem->setData(Qt::UserRole, Definition.iPrimaryKey);
            QSize size(100, 40 * strList.size());
            pItem->setSizeHint(size);
            m_pUi->m_listWidgetDefinition->addItem(pItem);
        }

        return true;
    }

    bool AbbreviationFunctionSearch::SearchDefinitionFromSQL(const QString& strText)
    {
        m_vecDefinitionInfos.clear();
        std::map<int, MysqlDB::materialParamaters> mapDefinition = m_pMysqlDB->outputWithPreparedQuery(strText);
        std::map<int, MysqlDB::materialParamaters>::iterator itMap = mapDefinition.begin();
        for (; itMap != mapDefinition.end(); itMap++)
        {
            AbbreviationInfo_s info;
            info.iPrimaryKey = itMap->first;
            info.strDefinition = itMap->second.strDefinition;
            //info.strAcronym = strText.toStdString();
            info.strAcronym = itMap->second.strAcRonym;
            m_vecDefinitionInfos.push_back(info);

            //m_pUi->m_comboMaterial->addItem(info.strAcronym);
        }
        if (m_vecDefinitionInfos.size() < 1)
        {
            return false;
        }

        emit sgnAddComboItem(m_vecDefinitionInfos);
        // 查询到后展示第一个数据
        m_pUi->m_labelEditACronym->setText(QString::fromStdString(m_vecDefinitionInfos[0].strAcronym));
        ClearDefinition();
        return AddDefinition(m_vecDefinitionInfos[0]);
    }

    // 改变原料选择
    void AbbreviationFunctionSearch::onCurrentIndexChanged(int iIndex)
    {
        if (iIndex >= m_vecDefinitionInfos.size())
        {
            return;
        }

        m_pUi->m_labelEditACronym->setText(QString::fromStdString(m_vecDefinitionInfos[iIndex].strAcronym));
        ClearDefinition();
        AddDefinition(m_vecDefinitionInfos[iIndex]);
    }

    void AbbreviationFunctionSearch::OnDeleteDefinition(uint64_t iPrimaryKey, QListWidgetItem* pItem)
    {
        DeleteDefinition(iPrimaryKey, pItem);
    }

    void AbbreviationFunctionSearch::OnItemDoubleClicked(QListWidgetItem* pItem)
    {
        if (nullptr == pItem)
        {
            return;
        }

        QString strHttp = "";
        std::count_if(m_vecDefinitionInfos.begin(), m_vecDefinitionInfos.end(),
            [&strHttp, pItem] (AbbreviationInfo_s info) 
        {
            if (pItem->data(Qt::UserRole).toInt() == info.iPrimaryKey)
            {
                QString strDefinition = QString::fromStdString(info.strDefinition);
                if (strDefinition.contains("http://"))
                {
                    int iIdex = strDefinition.indexOf("http://");
                    if (iIdex >= 0)
                    {
                        strHttp = strDefinition.mid(iIdex);
                        return true;
                    }
                }
                else if (strDefinition.contains("https://"))
                {
                    int iIdex = strDefinition.indexOf("https://");
                    if (iIdex >= 0)
                    {
                        strHttp = strDefinition.mid(iIdex);
                        return true;
                    }
                }
            }
            return false;
        });

        if (!strHttp.isEmpty())
        {
            QDesktopServices::openUrl(QUrl(strHttp));
        }
    }

    void AbbreviationFunctionSearch::OnEditDefinition(uint64_t iPrimaryKey, QListWidgetItem* pItem)
    {
        editDefinition(iPrimaryKey, pItem);
    }

    void AbbreviationFunctionSearch::onModifyDefinition(uint64_t iPrimaryKey, std::string strDefinition)
    {
        bool bRec = m_pMysqlDB->updateDefinition(iPrimaryKey, strDefinition);

        if (bRec)
        {
            QString strText = m_pUi->m_labelEditACronym->text();
            ClearDefinition();
            SearchDefinitionFromSQL(strText);

            emit sgnModifyDefinition();
        }
    }

    bool AbbreviationFunctionSearch::DeleteDefinition(uint64_t iPrimaryKey, QListWidgetItem* pItem)
    {
        if (nullptr == pItem)
        {
            return false;
        }

        bool bRec = m_pMysqlDB->deleteQuery(iPrimaryKey);
        
        if (bRec)
        {
            m_pUi->m_listWidgetDefinition->removeItemWidget(pItem);
            delete pItem;
            pItem = nullptr;
            m_pUi->m_listWidgetDefinition->update();

            emit sgnDelDefinition();
        }

        return bRec;
    }


    bool AbbreviationFunctionSearch::editDefinition(uint64_t iPrimaryKey, QListWidgetItem* pItem)
    {
        if (nullptr == m_pModifyDefinitionDialog || nullptr == pItem)
        {
            return false;
        }

        QString strText = pItem->text();
        QString strDefinetion = strText.right(strText.length() - g_iDefinitionOffset);
        QRect rect = this->geometry();
        QPoint point = mapToGlobal(this->pos());
        m_pModifyDefinitionDialog->setGeometry((point.x() + (this->width() - m_pModifyDefinitionDialog->width()) / 2),
            (point.y() + (this->height() - m_pModifyDefinitionDialog->height()) / 2),
            m_pModifyDefinitionDialog->width(), m_pModifyDefinitionDialog->height());
        m_pModifyDefinitionDialog->showDialog(iPrimaryKey, strDefinetion.toStdString());

        return true;
    }

} // end namesapce mainApp

