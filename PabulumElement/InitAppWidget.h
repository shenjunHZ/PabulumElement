#pragma once

#include <QtWidgets/QWidget>

#include "Dialog/Dialog.h"

namespace Ui
{
    class InitAppWidget;
}

namespace mainApp
{
    typedef enum class mainwidgetType
    {
        MAIN_WIDGET_TYPE_Main = 0,
        MAIN_WIDGET_TYPE_RecipeElement = 1,
    }mainwidgetType_e;

    class MainAppWidget;
    class RecipeElementWidget;

    class InitAppWidget : public DSGUI::DSDialog
    {
        Q_OBJECT

    public:
        InitAppWidget(QWidget* pParent = nullptr);
        ~InitAppWidget();

    private slots:
        void onNextWidget();
        void onFrontWidget();

    private:
        void connectSgn();

    private:
        Ui::InitAppWidget*   m_pUi;
        MainAppWidget*       m_pMainAppWidget;
        RecipeElementWidget* m_pRecipeElementWidget;
    };
}