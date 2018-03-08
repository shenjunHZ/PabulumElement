/*
@tool    ListWidgetDefinition 实现鼠标事件
@author  sj
@data    2017-9-12
@version 1.0
*/

#pragma once

#include <QtWidgets/QListWidget>
#include <QtGui/QContextMenuEvent>

namespace mainApp
{
    class ListWidgetItemRightAction;

    class ListWidgetDefinition : public QListWidget
    {
        Q_OBJECT

    public:
        ListWidgetDefinition(QWidget* pParent = nullptr);
        ~ListWidgetDefinition();

    signals:
        void sgnDeleteDefinition(uint64_t iPrimaryKey, QListWidgetItem* pItem);
        void sgnEditDefinition(uint64_t iPrimaryKey, QListWidgetItem* pItem);

    protected:
        void contextMenuEvent(QContextMenuEvent *ev);

    private:
        void ConnectSgn();

    private:
        ListWidgetItemRightAction*   m_pRightAction;
    };

} // end namespace mainApp