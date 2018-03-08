#include "ListWidgetDefinition.h"
#include "ListWidgetItemRightAction.h"

#include <QtGui/QCursor>

namespace mainApp
{

    ListWidgetDefinition::ListWidgetDefinition(QWidget* pParent/* = nullptr*/)
        : QListWidget(pParent),
        m_pRightAction(nullptr)
    {
        m_pRightAction = new ListWidgetItemRightAction(this);
        ConnectSgn();
    }

    ListWidgetDefinition::~ListWidgetDefinition()
    {

    }

    void ListWidgetDefinition::ConnectSgn()
    {
        //qRegisterMetaType<uint64_t>("uint64_t");
        connect(m_pRightAction, SIGNAL(sgnDeleteDefinition(uint64_t, QListWidgetItem*)), this, SIGNAL(sgnDeleteDefinition(uint64_t, QListWidgetItem*)));
        connect(m_pRightAction, SIGNAL(sgnEditDefinition(uint64_t, QListWidgetItem*)),   this, SIGNAL(sgnEditDefinition(uint64_t, QListWidgetItem*)));
    }

    void ListWidgetDefinition::contextMenuEvent(QContextMenuEvent *ev)
    {
        QListWidgetItem* pItem = this->itemAt(mapFromGlobal(QCursor::pos()));
        if ( nullptr != pItem)
        {
            uint64_t iPrimaryKey = pItem->data(Qt::UserRole).toUInt();
            m_pRightAction->DoAction(iPrimaryKey, pItem);
        }
    }

} // end namespace mainApp