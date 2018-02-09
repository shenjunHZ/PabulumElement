/*
 *@file   CustomComboBox.h
 *@brief  自定义弹出框
 * 
 *@author cc
 *@date   2014-07-08
 *
 */

#ifndef _DSGUI_CUSTOMCOMBOBOX_H
#define _DSGUI_CUSTOMCOMBOBOX_H

#include "ComboBox.h"
#include <QScopedPointer>

namespace DSGUI
{
    class DSCustomComboBoxPrivate;
    class DSComboBoxPopupContainer;
	/**  类名：DSCustomComboBox
	 *   说明  自定义弹出框
	**/
	class DS_GUI_EXPORT DSCustomComboBox : public DSComboBox
	{
        Q_OBJECT
	public:
		// 构造 
		DSCustomComboBox(QWidget* pParent = NULL);
        // 析构
        ~DSCustomComboBox();

    public:
        // 设置弹出框容器 
        void SetPopupContainer(DSComboBoxPopupContainer* pWnd);
        DSComboBoxPopupContainer* GetPopupContainer() const;

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
        QScopedPointer<DSCustomComboBoxPrivate> d_ptr;

    private:
        Q_DECLARE_PRIVATE(DSCustomComboBox)
        Q_DISABLE_COPY(DSCustomComboBox)
	};
}

#endif

