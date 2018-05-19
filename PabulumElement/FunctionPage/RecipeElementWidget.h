#pragma once

#include <QtWidgets/QWidget>

#include "HomePage/ViewDefine.h"

namespace Ui
{
    class RecipeElementWidget;
}

namespace mainApp
{
    typedef enum class widgetType
    {
        WIDGET_TYPE_Recipe = 0,
        WIDGET_TYPE_Element = 1,
    }widgetType_e;

    class RecipeElementWidget : public QWidget
    {
        Q_OBJECT

    public:
        RecipeElementWidget(QWidget* pParent = nullptr);
        ~RecipeElementWidget();

        void createData(QList<QList<QString>> listValue);
        void getElementListData(std::vector<nutrientContentTable>& contentTable, float& eachPer);
        void getSortRecipeList(QList<QString>& listSortRecipe);

    private:
        void initUI();
        void connectSgn();
        void setSelectWidgetType(widgetType_e nType);

    signals:
        void sgnFrontWidget();
        void sgnExport();

    private slots:
        void onCurrentIndexChanged(int nIndex);
        void onExport();

    private:
        Ui::RecipeElementWidget* m_pUi;
    };
}