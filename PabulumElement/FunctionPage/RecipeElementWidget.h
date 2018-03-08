#pragma once

#include <QtWidgets/QWidget>

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
        void getElementListData(QList<QString>& listElement, QList<float>& listConstituent, float& eachPer);

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