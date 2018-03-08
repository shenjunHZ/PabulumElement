#pragma once

#include <QtWidgets/QWidget>
#include <memory>

#include "Dialog/Dialog.h"

namespace Ui
{
    class MaterialAnalyzeWidget;
}
namespace MysqlDB
{
    class CMysqlDB;
}

namespace mainApp
{
    typedef enum class mainwidgetType
    {
        MAIN_WIDGET_TYPE_Main = 0,
        MAIN_WIDGET_TYPE_RecipeElement = 1,
    }mainwidgetType_e;

    class PrepareTableWidget;
    class RecipeElementWidget;

    class MaterialAnalyzeWidget : public DSGUI::DSDialog
    {
        Q_OBJECT

    public:
        MaterialAnalyzeWidget(std::shared_ptr<MysqlDB::CMysqlDB> ptrMysqlDB, QWidget* pParent = nullptr);
        ~MaterialAnalyzeWidget();

    private slots:
        void onNextWidget();
        void onFrontWidget();
        void onUpdateDefinition();

    private:
        void connectSgn();

    private:
        Ui::MaterialAnalyzeWidget*   m_pUi;
        PrepareTableWidget*          m_pPrepareTableWidget;
        RecipeElementWidget*         m_pRecipeElementWidget;

        std::shared_ptr<MysqlDB::CMysqlDB> m_pMysqlDB;
    };
}