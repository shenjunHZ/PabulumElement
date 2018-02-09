/*
 *@file   DSComboBox.h
 *@brief  
 * 
 *@author 
 *@date   2014-05-27
 *
 */

#ifndef __DSGUI_COMBOBOX_H
#define __DSGUI_COMBOBOX_H

#include "DSGuiGlobal.h"
#include <QComboBox>

namespace DSGUI
{
	class DS_GUI_EXPORT DSComboBox : public QComboBox
	{
		Q_OBJECT
	public:
		DSComboBox(QWidget* pParent = NULL);

	};
}

#endif
