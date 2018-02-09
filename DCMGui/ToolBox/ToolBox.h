/*
 *@file   DSToolBox.h
 *@brief  
 * 
 *@author cc
 *@date   2014-06-13
 *
 */

#ifndef _DSGUI_TOOLBOX_H
#define _DSGUI_TOOLBOX_H

#include "DSGuiGlobal.h"
#include <QToolBox>

namespace DSGUI
{
	class DS_GUI_EXPORT DSToolBox : public QToolBox
	{
		Q_OBJECT
	public:
        // ππ‘Ï
		DSToolBox(QWidget* pParent = NULL);
	};
}

#endif
