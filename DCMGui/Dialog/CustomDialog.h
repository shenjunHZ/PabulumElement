/*
 *@file   CustomDialog.h
 *@brief  
 * 
 *@author 28100
 *@date   2016-11
 *
 */

#ifndef __DSGUI_CUSTOMDIALOG_H
#define __DSGUI_CUSTOMDIALOG_H

#include "DSGuiGlobal.h"
#include "Dialog/Dialog.h"

namespace DSGUI
{
	class DSCustomDialogPrivate;
	class DSPushButton;

	class DS_GUI_EXPORT DSCustomDialog : public DSDialog
	{
		Q_OBJECT

	public:
		enum StandardButton {
			NoButton           = 0x00000000,
			Ok                 = 0x00000400,
			Other              = 0x00002000,
			Cancel             = 0x00400000,
		};
		Q_DECLARE_FLAGS(StandardButtons, StandardButton)

	public:
		DSCustomDialog(StandardButtons enumButtons = NoButton, QWidget* pParent = NULL, DialogFlags enumDialogFlags = 0);

		~DSCustomDialog();

	public:
		//¸²¸Ç
		void AddCentralWidget(QWidget* pWidget);

		QWidget* GetCentralWidget() const;

		void SetButtonText(StandardButtons enumButtons, QString strText);

		void SetButtonEnable(StandardButtons enumButtons, bool bEnable);

	
	signals:
		
		void SignalOkButtonClicked();

		void SignalCancelButtonClicked();

		void SignalOtherButtonClicked();

	private:
		QScopedPointer<DSCustomDialogPrivate> d_ptr;

	private:
		Q_PRIVATE_SLOT(d_func(), void OnButtonOtherClicked())
		Q_PRIVATE_SLOT(d_func(), void OnButtonOkClicked())
		Q_PRIVATE_SLOT(d_func(), void OnButtonCancelClicked())
		Q_DISABLE_COPY(DSCustomDialog)
		Q_DECLARE_PRIVATE(DSCustomDialog)
	};
}

Q_DECLARE_OPERATORS_FOR_FLAGS(DSGUI::DSCustomDialog::StandardButtons)

#endif // __DSGUI_CUSTOMDIALOG_H
