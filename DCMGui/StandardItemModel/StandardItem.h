/*
 *@file   StandardItem.h
 *@brief  
 * 
 *@author 
 *@date   2014-05-28
 *
 */

#ifndef _GUITOOLKIT_STANDARDARDITE_H
#define _GUITOOLKIT_STANDARDARDITE_H

#include "DSGuiGlobal.h"
#include <QStandardItemModel>

namespace DSGUI
{
    class DS_GUI_EXPORT CStandardItem 
        : public QStandardItem
    {
    public:
        // 构造
        CStandardItem();
        CStandardItem(const QString& strText);
        CStandardItem(const QIcon& icon, const QString& strText);

    public:
        // 设置不可用效果,此接口供item显示不可用效果
        void SetEnabled(bool bEnabled);

    public:
        // 设置item数据
        bool SetItemData(const QMap<int, QVariant>& mapRoles);
    public:
        // 重载此函数，特殊处理图标问题
        // 可通过设置CDecorationRole关键值来改变图标
        virtual QVariant data(int iRole = Qt::UserRole + 1) const;

    public:
        // 克隆item
        virtual QStandardItem* clone() const;

    protected:
        // 拷贝构造
        CStandardItem(const QStandardItem& otherItem);
    };
}

#endif
