/*
 *@file   CascadingListWidget.h
 *@brief  二级级联列表（组合框弹出控件）
 * 
 *@author 28100
 *@date   2017-01-23
 *
 */
#ifndef _DSGUI_CASCADINGLISTWIDGET_H
#define _DSGUI_CASCADINGLISTWIDGET_H

#include "DSGuiGlobal.h"
#include "ComboBoxPopupContainer.h"
#include "ListWidget/ListWidget.h"
#include "TableView/BaseViewItemDelegate.h"

namespace DSGUI
{
	class DS_GUI_EXPORT DSCascadingListWidget : public DSComboBoxPopupContainer
	{
		enum ItemDataRole {
			MainListDateRole = Qt::UserRole + 1,
			CascadingListRole = Qt::UserRole + 2,
		};
		Q_OBJECT

	public:
		DSCascadingListWidget(QWidget *parent = NULL);
		~DSCascadingListWidget();

		void InitDate(QMap<int, QString> mapMainListData, QMap<int, QMap<int, QString> > mapCascadingRelation);

		const QMap<int, QString>* GetCascadingMapByMainListItem(int nMainlistItemValue);
		void SetCascadingListVisible(bool bVisible);
		void AdjustListSize();

	signals:
		void SignalMainListItemClicked(int nItemValue, QString strItemName);
		void SignalCascadingListItemClicked(int nItemValue, QString strItemName);
		void SignalCascadingListVisibleChange(bool bVisible);

	protected slots:
		void OnMainListItemEnter(QListWidgetItem* pItem);
		void OnMainListItemClicked(QListWidgetItem* pItem);
		void OnCascadingListItemClicked(QListWidgetItem* pItem);

	private:
		DSListWidget* m_pMainList;			//第一级列表
		DSListWidget* m_pCascadingList;		//第二级列表
		
		QMap<int, QString> m_mapMainListData;					//第一级列表数据
		QMap<int, QMap<int, QString> > m_mapCascadingRelation;	//一级列表数据与二级数据 关系组合表（Key：一级数据键值 Value: 一级数据对应的二级数据组合）
		int			  m_pItemHeight;
	};
}

#endif // _DSGUI_CASCADINGLISTWIDGET_H
