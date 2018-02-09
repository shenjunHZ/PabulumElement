/*
@function    main widget
@author  sj
@data    2018-1-22
@version 1.0
*/
#pragma once

#include <QtWidgets/QWidget>
#include <QtGui/QStandardItem>

namespace Ui
{
    class MainAppWidget;
}

namespace mainApp
{
    class ExecFileOperation;
    typedef enum
    {
        Recipe_View_Column_Num = 0,
    }RecipeViewColumn_e;

    class RecipeElementWidget;

    class MainAppWidget : public QWidget
    {
        Q_OBJECT

    public:
        MainAppWidget(QWidget* pParent = nullptr);
        ~MainAppWidget();

        void setRecipeElementWidget(RecipeElementWidget* pWidget);

    private:
        void initUI();
        void initListCtrl();
        void connectSgn();
        void tableOperateBtn(int nRow, int nCol, QStandardItem* item);

    signals:
        void sgnNextWidget();
        void sgnCreateData();

    private slots:
        void onAddRecipe();
        void onTableOperIndex(QStandardItem* pItem);
        void onDelBtnClicked();
        void onCreateData();
        void onClearList();

    private:
        Ui::MainAppWidget*     m_pUi;
        ExecFileOperation*     m_pExcelFile;
        QList<QList<QVariant>> m_listData;
        QStandardItemModel*	   m_model;
        QStandardItem*         m_pCurEnteredItem;         //  Û±Íµ±«∞item
        RecipeElementWidget* m_pRecipeElementWidget;
    };
}