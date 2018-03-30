#include "TableOperBtnWidget.h"

const int g_iBtnLeftOffset = 20;

namespace mainApp
{

    TableOperBtnWidget::TableOperBtnWidget(QWidget* pParent /*= nullptr*/)
        : QWidget(pParent)
        , m_pStandardItem(nullptr)
    {

    }

    TableOperBtnWidget::~TableOperBtnWidget()
    {

    }

    void TableOperBtnWidget::addButtnon(QPushButton* btn)
    {
        if (btn == NULL)
        {
            return;
        }

        btn->setParent(this);
        m_vecBtn.push_back(btn);
    }

    void TableOperBtnWidget::allBtnHide()
    {
        for (int i = 0; i < m_vecBtn.size(); i++)
        {
            m_vecBtn[i]->hide();
        }
    }

    void TableOperBtnWidget::showEditButton()
    {
        if (m_vecBtn.isEmpty())
        {
            return;
        }

        allBtnHide();

        m_vecBtn[Table_Operate_Btn_Delete]->setGeometry(g_iBtnLeftOffset, 6, m_vecBtn[Table_Operate_Btn_Delete]->width(), m_vecBtn[Table_Operate_Btn_Delete]->height());
        m_vecBtn[Table_Operate_Btn_Delete]->show();
    }

    void TableOperBtnWidget::enterEvent(QEvent *ev)
    {
        emit sgnTableOperIndex(m_pStandardItem);
    }

    void TableOperBtnWidget::setTableOperIndex(QStandardItem* pItem)
    {
        m_pStandardItem = pItem; // 指示上层操作item
    }
}