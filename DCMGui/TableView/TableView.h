/*
 *@file   TableView.h
 *@brief  表格控件
 * 
 *@author 
 *@date   2014-05-27
 *
 */

#ifndef _DSGUI_TABLEVIEW_H
#define _DSGUI_TABLEVIEW_H

#include "TableView/BaseView.h"

namespace DSGUI
{
    class DS_GUI_EXPORT DSTableView : public DSBaseView
    {
        Q_OBJECT
    public:
        DSTableView(QWidget* pParent = NULL);

    protected:
        // 当编辑可用时，鼠标单击会触发双击效果
        virtual bool edit(const QModelIndex& miIndex, EditTrigger enumTrigger, QEvent* pEvent);
    };

}

#endif
