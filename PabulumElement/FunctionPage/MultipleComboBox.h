#pragma once

#include <QtWidgets/QComboBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLineEdit>

#include <ComboBox/ComboBox.h>

namespace mainApp
{
    class MultipleComboBox : public DSGUI::DSComboBox
    {
        Q_OBJECT

    public:
        MultipleComboBox(QWidget* pParent = nullptr);
        ~MultipleComboBox();

        void initUI();
        void setData(std::vector<QString> vecDatas);

    private slots:
        void onStateChanged(int iState);
        void onTextChanged(QString strText);

    private:
        QListWidget*    m_pListWidget;
        QLineEdit*      m_pLineEdit;
        bool            m_bSelected;
        QString         m_strSelectedText;
    };
}