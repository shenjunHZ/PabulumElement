#ifndef _DSGUI_COMBOBOXPOPUPCONTAINER_H
#define _DSGUI_COMBOBOXPOPUPCONTAINER_H

#include "DSGuiGlobal.h"
#include <QWidget>

namespace DSGUI
{
	class DS_GUI_EXPORT DSComboBoxPopupContainer : public QWidget
	{
		Q_OBJECT
	public:
		DSComboBoxPopupContainer(QWidget* pParent = NULL);

	protected:
		virtual void mousePressEvent(QMouseEvent* pEventvent);
	};
}

#endif // _DSGUI_COMBOBOXPOPUPCONTAINER_H
