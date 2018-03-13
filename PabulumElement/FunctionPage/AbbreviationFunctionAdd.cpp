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
        m_pMysqlDB(nullptr)
    {
        m_pUi = new Ui::AbbreviationFunctionAdd();
        m_pUi->setupUi(this);

        QFont font;
        font.setPixelSize(14);
        font.setPointSize(14);
        font.setFamily(QString::fromUtf8("Arial"));
        m_pUi->m_pTextEditDefinition->setCurrentFont(font);
        ConnectSgn();
        //SET_MODULE_STYLE_BY_PATH("AbbreviationFunctionAdd");
    }

    AbbreviationFunctionAdd::~AbbreviationFunctionAdd()
    {

    }

    void AbbreviationFunctionAdd::SetAbbreviationTable(std::shared_ptr<MysqlDB::CMysqlDB> pMysqlDB)
    {
        m_pMysqlDB = pMysqlDB;
    }

    void AbbreviationFunctionAdd::ConnectSgn()
    {
        connect(m_pUi->m_btnSave,   SIGNAL(clicked()), this, SLOT(OnSaveClicked()));
        connect(m_pUi->m_btnCancel, SIGNAL(clicked()), this, SLOT(OnCancelClicked()));
        connect(m_pUi->m_pTextEditDefinition, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
        connect(m_pUi->m_pTextEditDefinition, SIGNAL(cursorPositionChanged()), this, SLOT(onCursorPositionChanged()));
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
        font.setPixelSize(14);
        font.setPointSize(14);
        font.setFamily(QString::fromUtf8("Arial"));
        m_pUi->m_pTextEditDefinition->setCurrentFont(font);
    }

}