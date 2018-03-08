#include "ListWidgetItemRightAction.h"

const int g_iItemActionDelete = 0;
const int g_iItemActionEdit = 1;

namespace mainApp
{
    
    ListWidgetItemRightAction::ListWidgetItemRightAction(QWidget* pParent, DSGUI::DSMenu* pMenu /*= nullptr*/)
        : QObject(pParent),
        m_pMenu(pMenu),
        m_pActDelete(nullptr),
        m_pActUpdate(nullptr)
    {
        if (nullptr == m_pMenu)
        {
            m_pMenu = new DSGUI::DSMenu();
        }

        initUi();
    }

    ListWidgetItemRightAction::~ListWidgetItemRightAction()
    {
        delete m_pMenu;
        m_pMenu = nullptr;
    }

    void ListWidgetItemRightAction::initUi()
    {
        m_pActDelete = m_pMenu->addAction(QObject::tr("Delete Definition  "));
        m_pActDelete->setIcon(QIcon("./skin/DustyBlue/AbbreviationApplication/del-p.png"));
        m_pActDelete->setData(g_iItemActionDelete);

        m_pActUpdate = m_pMenu->addAction(QObject::tr("Edit Definition  "));
        m_pActUpdate->setIcon(QIcon("./skin/DustyBlue/AbbreviationApplication/edit-p.png"));
        m_pActUpdate->setData(g_iItemActionEdit);
    }

    int ListWidgetItemRightAction::DoAction(uint64_t iPrimaryKey, QListWidgetItem* pItem)
    {
        QAction* pAction = m_pMenu->exec(QCursor::pos());
        Do(pAction, iPrimaryKey, pItem);

        return 0;
    }

    void ListWidgetItemRightAction::Do(QAction* pAction, uint64_t iPrimaryKey, QListWidgetItem* pItem)
    {
        if (nullptr == pAction)
        {
            return;
        }

        //int iTest = pAction->data().toInt();
        switch (pAction->data().toInt())
        {
        case g_iItemActionDelete:
            emit sgnDeleteDefinition(iPrimaryKey, pItem);
            break;
        case g_iItemActionEdit:
            emit sgnEditDefinition(iPrimaryKey, pItem);
            break;
        default:
            break;
        }
    }

}