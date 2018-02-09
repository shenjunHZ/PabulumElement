/*
 *@file   CheckBox.h
 *@brief  
 * 
 *@author cc
 *@date   2014-06-18
 *
 */

#ifndef _DSGUI_CHECKBOX_H
#define _DSGUI_CHECKBOX_H

#include "DSGuiGlobal.h"
#include <QCheckBox>

namespace DSGUI
{
	class DS_GUI_EXPORT DSCheckBox : public QCheckBox
	{
		Q_OBJECT
	public:
        // ππ‘Ï
		DSCheckBox(QWidget* pParent = NULL);
        DSCheckBox(const QString& strText, QWidget* pParent = NULL);

	};
}

#endif // _DSGUI_CHECKBOX_H
