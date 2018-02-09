/*
 *@file   ScrollBar.h
 *@brief  
 * 
 *@author cc
 *@date   2014-06-19
 *
 */

#ifndef __DSGUI_SCROLLBAR_H
#define __DSGUI_SCROLLBAR_H

#include "DSGuiGlobal.h"
#include <QScrollBar>

namespace DSGUI
{
	class DS_GUI_EXPORT DSScrollBar : public QScrollBar
	{
		Q_OBJECT
	public:
		DSScrollBar(QWidget* pParent = NULL);
        DSScrollBar(Qt::Orientation enumOrientation, QWidget* pParent = NULL);

	};

    class DS_GUI_EXPORT DSHorScrollBar : public DSScrollBar
    {
        Q_OBJECT
    public:
        DSHorScrollBar(QWidget* pParent = NULL);
    };

    class DS_GUI_EXPORT DSVerScrollBar : public DSScrollBar
    {
        Q_OBJECT
    public:
        DSVerScrollBar(QWidget* pParent = NULL);
    };
}

#endif
