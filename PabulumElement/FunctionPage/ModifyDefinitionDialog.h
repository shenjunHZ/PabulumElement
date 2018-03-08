/*
@tool    modify definition
@author  sj
@data    2018-1-11
@version 1.0
*/
#pragma once

#include "Dialog/Dialog.h"
#include "ui_ModifyDefinitionDialog.h"

#include <QtWidgets/QWidget>

namespace Ui
{
    class ModifyDefinitionDialog;
}

namespace mainApp
{
    class ModifyDefinitionDialog : public DSGUI::DSDialog
    {
        Q_OBJECT

    public:
        ModifyDefinitionDialog(QWidget* pParent = nullptr);
        ~ModifyDefinitionDialog();

        void showDialog(uint64_t iPrimaryKey, std::string strDefinition);

    private:
        void ConnectSgn();

    signals:
        void sgnModifyDefinition(uint64_t iPrimaryKey, std::string strText);

    private slots:
        void onSaveDefinition();
        void onCancleDefinition();

    private:
        Ui::ModifyDefinitionDialog* m_pUi;
        uint64_t                    m_iPrimaryKey;
    };
}