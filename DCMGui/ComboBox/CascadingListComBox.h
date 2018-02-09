/*
 *@file   CascadingListWidget.h
 *@brief  二级级联列表组合框
 * 
 *@author 28100
 *@date   2017-01-23
 *
 */
#ifndef _DSGUI_CASCADINGLISTCOMBOX_H
#define _DSGUI_CASCADINGLISTCOMBOX_H

#include <QWidget>

#include "DSGuiGlobal.h"
#include "CustomComboBox.h"
#include "CascadingListWidget.h"

namespace DSGUI
{
	class DS_GUI_EXPORT DSCascadingListComBox : public DSCustomComboBox
	{
		Q_OBJECT

	public:
		DSCascadingListComBox(QWidget *parent = NULL);
		~DSCascadingListComBox();

	public:
		void InitDate(QMap<int, QString> mapMainListData, QMap<int, QMap<int, QString> > mapCascadingRelation);
		void GetCurrentChosenItem(QVector<int>& vecChosenItems);

	protected:
		// 弹出下拉框
		virtual void showPopup();

	protected slots:
		void OnMainListItemClicked(int nItemValue, QString strItemName);
		void OnCascadingListItemClicked(int nItemValue, QString strItemName);
		void OnCascadingListVisibleChange(bool bVisible);

	private:
		DSCascadingListWidget*  m_pCascadingListWidget;
		QVector<int>			m_vecCurrentChosenItem;
	};
}

#endif // _DSGUI_CASCADINGLISTCOMBOX_H
