#ifndef _DSGUI_MENU_H
#define _DSGUI_MENU_H

#include "DSGuiGlobal.h"
#include <QMenu>

namespace DSGUI
{
	class DS_GUI_EXPORT DSMenu : public QMenu
	{
		Q_OBJECT
	public:
		explicit DSMenu(QWidget* pParent = NULL);
		explicit DSMenu(const QString& strTitle, QWidget* pParent = NULL);
	    
	};
}

#endif
