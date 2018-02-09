/*
 *@file   TreeView.h
 *@brief  
 * 
 *@author cc
 *@date   2014-06-20
 *
 */

#ifndef _DSGUI_TREEVIEW_H
#define _DSGUI_TREEVIEW_H

#include "TableView/BaseView.h"

namespace DSGUI
{
	class DS_GUI_EXPORT DSTreeView : public DSBaseView
	{
		Q_OBJECT
    public:
        /** @enum ExpandState
         *  @brief item展开收缩状态
         */
        enum ExpandState
        {
            AllCollapse,        // 所有都收缩（包括子节点）
            CollapseAndExpand,  // 存在展开和收缩（包括子节点）
            AllExpand           // 所有都展开（包括子节点）
        };
	public:
        // 构造
		DSTreeView(QWidget* pParent = NULL);
		~DSTreeView();

    public:
        // 设置model
        virtual void setModel(QAbstractItemModel* pModel);

    public:
        // 设置视图checkbox是否自动改变
        void SetAutoChangeCheckbox(bool bAutoChangeCheckbox);

	public:
        // 展开所有，包括其子节点
        void ExpandAll(const QModelIndex& miParent);
        // 收缩所有，包括其子节点
        void CollapseAll(const QModelIndex& miParent);
		// 获取树形列表展开收缩状态,如果不存在子节点就返回无效
		bool GetExpandState(ExpandState& enumExpandState, const QModelIndex& miParent = QModelIndex()) const;

	protected slots:
        // 数据改变
		virtual void dataChanged(const QModelIndex& miTopLeft, const QModelIndex& miBottomRight);
        // 更新checkbox状态
		void OnUpdateCheckState(const QModelIndex& miIndex);

    private:
        // 更新子节点checkbox状态
        void UpdateChildCheckState(const QModelIndex& miParent);

    private:
        bool m_bAutoChangeCheckbox; // 是否自动改变勾选状态
	};
}

#endif //_GUITOOLKIT_TREEVIEW_H
