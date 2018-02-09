/*
 *@file   StandardItemModel.h
 *@brief  
 * 
 *@author cc
 *@date   2014-08-25
 *
 */

#ifndef _GUITOOLKIT_STANDARDARDITEMODEL_H
#define _GUITOOLKIT_STANDARDARDITEMODEL_H

#include "DSGuiGlobal.h"
#include <QStandardItemModel>

namespace DSGUI
{
    class DSStandardItemModelPrivate;

    class DS_GUI_EXPORT DSStandardItemModel 
        : public QStandardItemModel
    {
        Q_OBJECT
    public:
        // 构造
        DSStandardItemModel(QObject* pParent = NULL);
        ~DSStandardItemModel();

    public:
        // 重载获取数据
        virtual QVariant data(const QModelIndex& miIndex, int iRole = Qt::DisplayRole) const;

    public:
        // 数据映射
        // 列iProxyColumn的iProxyRole的数据从列iSourceColumn的iSourceRole获取
        // iProxyColumn为-1表示所有列都映射
        void AddKeyMapping(int iProxyColumn, int iProxyRole, int iSourceColumn, int iSourceRole);
    private:
        QScopedPointer<DSStandardItemModelPrivate> d_ptr;

    private:
        Q_DECLARE_PRIVATE(DSStandardItemModel)
        Q_DISABLE_COPY(DSStandardItemModel)
    };
}

#endif
