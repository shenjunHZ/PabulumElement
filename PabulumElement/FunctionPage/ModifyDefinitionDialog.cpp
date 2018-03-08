#include "ModifyDefinitionDialog.h"

namespace mainApp
{

    ModifyDefinitionDialog::ModifyDefinitionDialog(QWidget* pParent /*= nullptr*/) : DSDialog(pParent),
        m_pUi(nullptr), 
        m_iPrimaryKey(0)
    {
        m_pUi = new Ui::ModifyDefinitionDialog();
        m_pUi->setupUi(this->GetCentralWidget());
        //this->SetTitle(QObject::tr("Modify Definition"));

        ConnectSgn();
    }

    ModifyDefinitionDialog::~ModifyDefinitionDialog()
    {

    }

    void ModifyDefinitionDialog::showDialog(uint64_t iPrimaryKey, std::string strDefinition)
    {
        m_pUi->m_textEdit->setText(QString::fromStdString(strDefinition));
        m_iPrimaryKey = iPrimaryKey;

        //this->setGeometry(mapFromGlobal(QCursor::pos()).rx(), mapFromGlobal(QCursor::pos()).ry(), width(), height());
        exec();
    }

    void ModifyDefinitionDialog::ConnectSgn()
    {
        connect(m_pUi->m_btnSave,   SIGNAL(clicked()), this, SLOT(onSaveDefinition()));
        connect(m_pUi->m_btnCancel, SIGNAL(clicked()), this, SLOT(onCancleDefinition()));
    }

    void ModifyDefinitionDialog::onSaveDefinition()
    {
        QString strText = m_pUi->m_textEdit->toPlainText();
        if (!strText.isEmpty())
        {
            emit sgnModifyDefinition(m_iPrimaryKey, strText.toStdString());
        }
        hide();
    }

    void ModifyDefinitionDialog::onCancleDefinition()
    {
        m_pUi->m_textEdit->clear();
        hide();
    }

}