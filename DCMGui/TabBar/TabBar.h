#ifndef _DSGUI_TABBAR_H
#define _DSGUI_TABBAR_H

#include "DSGuiGlobal.h"
#include <QTabBar>

namespace DSGUI
{
	class DS_GUI_EXPORT DSTabBar : public QTabBar
	{
		Q_OBJECT
	public:
		DSTabBar(QWidget* pParent = NULL);
	};
}

#endif
