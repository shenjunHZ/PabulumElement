#ifndef __DSGUI_DATEEDIT_H
#define __DSGUI_DATEEDIT_H


#include <QDateEdit>
#include "DSGuiGlobal.h"


namespace DSGUI
{
	class DS_GUI_EXPORT DSDateEdit : public QDateEdit
	{
		Q_OBJECT

	public:
		DSDateEdit(QWidget *pParent=NULL);
		~DSDateEdit();

	private:

	};
}


#endif // __DSGUI_DATEEDIT_H
