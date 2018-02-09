#ifndef TIMEEDIT_H
#define TIMEEDIT_H

#include "DSGuiGlobal.h"
#include <QTimeEdit>


namespace DSGUI
{

	class DS_GUI_EXPORT DSTimeEdit : public QTimeEdit
	{
		Q_OBJECT

	public:
		DSTimeEdit(QWidget *pParent=NULL);
		~DSTimeEdit();

	private:

	};
}


#endif // TIMEEDIT_H
