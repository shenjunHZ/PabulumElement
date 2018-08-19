#include "AbbreviationFunctionAdd.h"
#include "AppCommon/commonControl.h"
#include "ui_AbbreviationFunctionAdd.h"
#include "MySQL/MysqlDB.h"

#include <iostream>

namespace mainApp
{

    AbbreviationFunctionAdd::AbbreviationFunctionAdd(QWidget* pParent /*= nullptr*/)
        : QWidget(pParent),
        m_pUi(nullptr),
        m_pMysqlDB(nullptr),
        m_model(nullptr)
    {
        m_pUi = new Ui::AbbreviationFunctionAdd();
        m_pUi->setupUi(this);

        QFont font;
        font.setPixelSize(12);
        font.setPointSize(12);
        font.setFamily(QString::fromUtf8("Arial"));
        m_pUi->m_pTextEditDefinition->setCurrentFont(font);
        QStringList strHeaders;
        strHeaders  << "No." << QObject::tr("Recipe") << QObject::tr("Constituent");
        m_model = new QStandardItemModel(0, strHeaders.count());
        m_pUi->m_pAllTextEditDefinition->setModel(m_model);
        m_pUi->m_pAllTextEditDefinition->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_pUi->m_pAllTextEditDefinition->setColumnWidth(Recipe_View_Column_Num, 30);
        int begin = 0;
        foreach(QString name, strHeaders)
        {
            m_model->setHeaderData(begin, Qt::Horizontal, name);
            m_model->setHeaderData(begin, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
            begin++;
        }

        //QTextCursor& textCursor = m_pUi->m_pTextEditDefinition->textCursor();
        //QTextCharFormat charFormat;
        //charFormat.setFont(font);
        //textCursor.setCharFormat(charFormat);
        //m_pUi->m_pTextEditDefinition->setTextCursor(textCursor);

        ConnectSgn();
        //SET_MODULE_STYLE_BY_PATH("AbbreviationFunctionAdd");
    }

    AbbreviationFunctionAdd::~AbbreviationFunctionAdd()
    {

    }

    void AbbreviationFunctionAdd::SetAbbreviationTable(std::shared_ptr<MysqlDB::CMysqlDB> pMysqlDB)
    {
        m_pMysqlDB = pMysqlDB;
        showAllAbbreviations();
    }

    void AbbreviationFunctionAdd::ConnectSgn()
    {
        connect(m_pUi->m_btnSave,      SIGNAL(clicked()), this, SLOT(OnSaveClicked()));
        connect(m_pUi->m_btnCancel,    SIGNAL(clicked()), this, SLOT(OnCancelClicked()));
        connect(m_pUi->m_btnAllSearch, SIGNAL(clicked()), this, SLOT(onAllSearchClicked()));
        connect(m_pUi->m_pTextEditDefinition, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
        //connect(m_pUi->m_pTextEditDefinition, SIGNAL(currentCharFormatChanged()), this, SLOT(onTextChanged()));
        connect(m_pUi->m_pTextEditDefinition, SIGNAL(cursorPositionChanged()), this, SLOT(onCursorPositionChanged()));
    }

    void AbbreviationFunctionAdd::showAllAbbreviations()
    {
        if (nullptr != m_pMysqlDB)
        {
            std::map<QString, QString> materials = m_pMysqlDB->queryAllMaterial();
            int iCount = 0;
            for (auto material : materials)
            {
                int nRow = m_model->rowCount();
                QStandardItem* item = new QStandardItem();
                m_model->insertRow(nRow, item);

                m_model->setData(m_model->index(nRow, 0), iCount++);
                m_model->setData(m_model->index(nRow, 1), material.first);
                m_model->setData(m_model->index(nRow, 2), material.second);
            }
        }
    }

    bool AbbreviationFunctionAdd::AddDefinitionFromSQL(const AbbreviationInfo_s& sInfo)
    {
        {
            return m_pMysqlDB->addQuery(QString::fromStdString(sInfo.strAcronym), QString::fromStdString(sInfo.strDefinition));
        }

        return false;
    }

    void AbbreviationFunctionAdd::OnSaveClicked()
    {
        QString strAcronym = m_pUi->m_pLineEditAcronym->text();
        QString strDefinition = m_pUi->m_pTextEditDefinition->toPlainText();

        AbbreviationInfo_s sInfo;
        sInfo.strAcronym = strAcronym.toStdString();
        sInfo.strDefinition = strDefinition.toStdString();

        if (AddDefinitionFromSQL(sInfo))
        {
            m_pUi->m_pLineEditAcronym->clear();
            m_pUi->m_pTextEditDefinition->clear();

            emit sgnAddDefinition();
        }
    }

    void AbbreviationFunctionAdd::OnCancelClicked()
    {
        m_pUi->m_pLineEditAcronym->clear();
        m_pUi->m_pTextEditDefinition->clear();
    }

    void AbbreviationFunctionAdd::onTextChanged()
    {
        // when i clear the text in QTextEdie the font change back, so need to reset font.
        QFont font; 
        font.setPixelSize(12);
        font.setPointSize(12);
        font.setFamily(QString::fromUtf8("Arial"));
        m_pUi->m_pTextEditDefinition->setCurrentFont(font);
    }

    void AbbreviationFunctionAdd::onAllSearchClicked()
    {
        if (nullptr != m_model)
        {
            m_model->removeRows(0, m_model->rowCount());
        }

        showAllAbbreviations();
    }

}