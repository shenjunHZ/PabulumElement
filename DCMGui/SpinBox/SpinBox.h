/*
 *@file   SpinBox.h
 *@brief  
 * 
 *@author cc
 *@date   2014-06-18
 *
 */

#ifndef _DSGUI_SPINBOX_H
#define _DSGUI_SPINBOX_H

#include "DSGuiGlobal.h"
#include <QSpinBox>

namespace DSGUI
{
    class DS_GUI_EXPORT DSSpinBox : public QSpinBox
    {
        Q_OBJECT
    public:
        DSSpinBox(QWidget* pParent = NULL);
    };
}

#endif // _GUITOOLKIT_CSPINBOX_H
