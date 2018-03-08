/*
@function    recipe table
@author  sj
@data    2018-1-25
@version 1.0
*/
#pragma once

#include <QtWidgets/QWidget>
#include <QtGui/QStandardItem>

namespace Ui
{
    class RecipeListWidget;
}

namespace mainApp
{
    typedef struct recipteData
    {
        QString strRecipe;
        QString strValue;
    }recipteData;

    // °´³É·ÖÅÅÐò
    bool static compareBarData(const recipteData &barAmount1, const recipteData &barAmount2)
    {
        if (barAmount1.strValue.toFloat() >= barAmount2.strValue.toFloat())
        {
            return true;
        }
        return false;
    }

    class RecipeListWidget : public QWidget
    {
        Q_OBJECT

    public:
        RecipeListWidget(QWidget* pParent = nullptr);
        ~RecipeListWidget();

        void createRecipeList(QList<QList<QString>>& listVar);

    protected:
        void resizeEvent(QResizeEvent *event);

    private:
        void initUI();
        void connectSgn();

    private:
        Ui::RecipeListWidget* m_pUi;
        QStandardItemModel*	   m_model;
    };
}