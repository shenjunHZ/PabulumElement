#include "MultipleComboBox.h"

#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QCheckBox>

namespace mainApp
{

    MultipleComboBox::MultipleComboBox(QWidget* pParent /*= nullptr*/)
        : DSGUI::DSComboBox(pParent)
        , m_pListWidget(nullptr)
        , m_pLineEdit(nullptr)
        , m_bSelected(true)
        , m_strSelectedText("")
    {
        initUI();

        const_cast<QAbstractItemView*>(this->view())->setMinimumWidth(600);
    }

    MultipleComboBox::~MultipleComboBox()
    {

    }

    void MultipleComboBox::initUI()
    {
        m_pListWidget = new QListWidget(this);
        m_pLineEdit = new QLineEdit(this);

        this->setModel(m_pListWidget->model());
        this->setView(m_pListWidget);
        this->setLineEdit(m_pLineEdit);
        m_pLineEdit->setReadOnly(true);
        connect(m_pLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(onTextChanged(const QString &)));
    }

    void MultipleComboBox::setData(std::vector<QString> vecDatas)
    {
        if (vecDatas.size() < 1)
        {
            return;
        }

        for (int i = 0; i < vecDatas.size(); i++)
        {
            QListWidgetItem* pItem = new QListWidgetItem(m_pListWidget);
            //m_pListWidget->addItem(pItem);
            pItem->setData(Qt::UserRole, vecDatas[i]);

            QCheckBox* pCheckBox = new QCheckBox(this);
            pCheckBox->setText(QStringLiteral("%1").arg(vecDatas[i]));
            pCheckBox->setToolTip(QString("%1").arg(vecDatas[i]));
            m_pListWidget->addItem(pItem);
            m_pListWidget->setItemWidget(pItem, pCheckBox);
            connect(pCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(int)));
        }
    }

    void MultipleComboBox::onStateChanged(int iState)
    {
        m_bSelected = true;
        QString strSelectedData = "";
        m_strSelectedText.clear();

        QCheckBox *pSenderCheckBox;
        int nCount = m_pListWidget->count();
        for (int i = 0; i < nCount; ++i)
        {
            QListWidgetItem *pItem = m_pListWidget->item(i);
            QWidget *pWidget = m_pListWidget->itemWidget(pItem);
            QCheckBox *pCheckBox = (QCheckBox *)pWidget;
            if (pCheckBox->isChecked())
            {
                QString strText = pCheckBox->text();
                strSelectedData.append(strText).append(";");
            }
        }
        if (strSelectedData.endsWith(";"))
        {
            strSelectedData.remove(strSelectedData.count() - 1, 1);
        }
        if (!strSelectedData.isEmpty())
        {
            //ui.comboBox->setEditText(strSelectedData);
            m_strSelectedText = strSelectedData;
            m_pLineEdit->setText(strSelectedData);
            m_pLineEdit->setToolTip(strSelectedData);
        }
        else
        {
            m_pLineEdit->clear();
            //ui.comboBox->setEditText("");
        }
        m_bSelected = false;
    }

    void MultipleComboBox::onTextChanged(QString strText)
    {
        if (!m_bSelected)
        {
            m_pLineEdit->setText(m_strSelectedText);
        }
    }

}