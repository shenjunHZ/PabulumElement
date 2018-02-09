/*
 *@file   ProgressBar.h
 *@brief  
 * 
 *@author cc
 *@date   2014-06-21
 *
 */

#ifndef _DSGUI_PROGRESSBAR_H
#define _DSGUI_PROGRESSBAR_H

#include "DSGuiGlobal.h"
#include <QProgressBar>

namespace DSGUI
{
	class DS_GUI_EXPORT DSProgressBar : public QProgressBar
	{
		Q_OBJECT
	public:
		DSProgressBar(QWidget* pParent = NULL);
	};

    class DSCustomProgressBar : public QWidget
    {
        Q_OBJECT
    public:
        DSCustomProgressBar(QWidget* pParent = NULL);

    protected:
        void paintEvent(QPaintEvent *);

    private:
        void initStyleOption(QStyleOptionProgressBar *) const;

        QSize minimumSizeHint() const;
    };
}

#endif
