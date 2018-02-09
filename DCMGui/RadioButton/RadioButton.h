/*
 *@file   RadioButton.h
 *@brief  
 * 
 *@author cc
 *@date   2014-06-30
 *
 */

#ifndef _DSGUI_RADIOBUTTON_H
#define _DSGUI_RADIOBUTTON_H

#include "DSGuiGlobal.h"
#include <QRadioButton>

namespace DSGUI
{
	class DS_GUI_EXPORT DSRadioButton : public QRadioButton
	{
		Q_OBJECT
	public:
        // ππ‘Ï
		DSRadioButton(QWidget* pParent = NULL);
        DSRadioButton(const QString& strText, QWidget* pParent = NULL);

	};
}

#endif // _DSGUI_RADIOBUTTON_H
