#ifndef __DSGUI_SORTFILTERPROXYMODEL_H__
#define __DSGUI_SORTFILTERPROXYMODEL_H__

#include "DSGuiGlobal.h"
#include <QSortFilterProxyModel>

namespace DSGUI
{
    class DS_GUI_EXPORT DSSortFilterProxyModel : public QSortFilterProxyModel
    {
        Q_OBJECT
    public:
        enum SortOrder
        {
            DefaultOrder,    // 默认排序
            AscendingOrder,  // 升序
            DescendingOrder, // 降序
        };

        enum FilterMode
        {
            KeepMatchKey   = 1,     // 保留匹配关键值
            FilterMatchKey = 2,     // 过滤掉匹配的关键值
        };
        
        enum MatchMode
        {
            DefaultMatch    = 0,   // 默认匹配方式（包含匹配）
            EqualMatch      = 1,   // 相同匹配
        };
    public:
        DSSortFilterProxyModel(QObject* pParent = NULL);
        ~DSSortFilterProxyModel();

    public:
        //设置过滤模式
        void SetFilterMode(FilterMode enumFilterMode);
        // 设置匹配方式
        void SetMatchMode(MatchMode enumMatchMode);

    public:
        // 设置排序方式
        void SetSortOrder(DSSortFilterProxyModel::SortOrder enumSortOrder = DSSortFilterProxyModel::DefaultOrder);

    protected:
        // 过滤实现处
        virtual bool filterAcceptsRow(int iSourceRow, const QModelIndex& miSourceParent) const;

    private:
        FilterMode m_enumFilterMode;    // 过滤方式
        MatchMode m_enumMatchMode;      // 匹配方式
    };
}

#endif 
