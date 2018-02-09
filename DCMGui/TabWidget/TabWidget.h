#ifndef _DSGUI_TABWIDGET_H
#define _DSGUI_TABWIDGET_H

#include "DSGuiGlobal.h"
#include <QTabWidget>

namespace DSGUI
{
	class DS_GUI_EXPORT DSTabWidget : public QTabWidget
	{
		Q_OBJECT
	public:
		DSTabWidget(QWidget* pParent = NULL);
	};
}

#endif
