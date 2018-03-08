/*
@tool    add right key function use for mouse right click
@author  sj
@data    2017-9-16
@version 1.0
*/
#pragma once

#include <QtCore/QObject>
#include <QtCore/QPoint>
#include <QtWidgets/QWidget>
#include <QtWidgets/QAction>
#include <QtWidgets/QListWidget>

#include "Menu/Menu.h"

namespace mainApp
{
    class ListWidgetItemRightAction : public QObject
    {
        Q_OBJECT

    public:
        ListWidgetItemRightAction(QWidget* pParent, DSGUI::DSMenu* pMenu = nullptr);
        virtual ~ListWidgetItemRightAction();

        virtual int DoAction(uint64_t iPrimaryKey, QListWidgetItem* pItem);

    signals:
        void sgnDeleteDefinition(uint64_t iPrimaryKey, QListWidgetItem* pItem);
        void sgnEditDefinition(uint64_t iPrimaryKey, QListWidgetItem* pItem);

    private:
        void Do(QAction* pAction, uint64_t iPrimaryKey, QListWidgetItem* pItem);
        void initUi();

    private:
        DSGUI::DSMenu*     m_pMenu;
        QAction*           m_pActDelete;
        QAction*           m_pActUpdate; 
    };
}
