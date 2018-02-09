/*
 *@file   MenuCustomCombox.h
 *@brief  弹出框(弹出菜单)
 * 
 *@author 28100
 *@date   2017-02-28
 *
 */
#ifndef _DSGUI_MENUCOMBOX_H
#define _DSGUI_MENUCOMBOX_H

#include "ComboBox.h"
#include <QVector>

namespace DSGUI
{
	class DSMenuCustomComboxPrivate;

	class DS_GUI_EXPORT DSMenuCustomCombox : public DSComboBox
	{
		Q_OBJECT

	public:
		DSMenuCustomCombox(QWidget *parent);
		~DSMenuCustomCombox();

		void InitMenu(QMap<int, QString>& mapMainMenu, QMap<int, QMap<int, QString> >& mapCascadingSubMenu);
		void GetCurrentChosenItem(QVector<int>& vecChosenItems);

	signals:
		void SignalItemChange(int nMainItem, int nSubItem);

	protected:
		// 事件
		virtual bool event(QEvent* pEvent);

		// 鼠标事件
		virtual void mousePressEvent(QMouseEvent* pEvent);

		// 弹出下拉框
		virtual void showPopup();

		// 隐藏下拉框
		virtual void hidePopup();

	private:
		QScopedPointer<DSMenuCustomComboxPrivate> d_ptr;

	private:
		Q_DECLARE_PRIVATE(DSMenuCustomCombox)
		Q_DISABLE_COPY(DSMenuCustomCombox)
		Q_PRIVATE_SLOT(d_func(), void OnMainMenuActionHover())

	private:
		
	};
}

#endif // _DSGUI_MENUCOMBOX_H
