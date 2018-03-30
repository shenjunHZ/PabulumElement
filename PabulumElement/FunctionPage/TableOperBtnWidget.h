/*
@function   operation button widget
@author  sj
@data    2018-1-24
@version 1.0
*/
#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QVector>
#include <QtWidgets/QPushButton>
#include <QtGui/QStandardItem>

#include "PushButton/PushButton.h"

namespace mainApp
{
    typedef enum tableOperBtnWidget
    {
        Table_Operate_Btn_Delete = 0,
    }tableOperBtnWidget_e;

    class TableOperBtnWidget : public QWidget
    {
        Q_OBJECT

    public:
        TableOperBtnWidget(QWidget* pParent = nullptr);
        ~TableOperBtnWidget();

        void addButtnon(QPushButton* btn);
        void showEditButton();
        void setTableOperIndex(QStandardItem* pItem);

    signals:
        void sgnTableOperIndex(QStandardItem* pItem);

    protected:
        virtual void enterEvent(QEvent *ev);

    public:
        void allBtnHide();

    private:
        QVector<QPushButton*>	m_vecBtn;
        QStandardItem*          m_pStandardItem;
    };
}
