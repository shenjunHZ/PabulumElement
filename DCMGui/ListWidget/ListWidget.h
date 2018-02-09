/*
 *@file   DSListWidget.h
 *@brief  
 * 
 *@author cc
 *@date   2014-06-13
 *
 */

#ifndef _GUITOOLKIT_LISTWIDGET_H
#define _GUITOOLKIT_LISTWIDGET_H

#include "DSGuiGlobal.h"
#include <QtGui/QListWidget>

namespace DSGUI
{
	/**  类名：CListWidget
	*    说明 树型列表控件
	**/
	class DS_GUI_EXPORT DSListWidget : public QListWidget
	{
		Q_OBJECT
	public:
		// 构造
		DSListWidget(QWidget* pParent = NULL);
	};
}

#endif //_GUITOOLKIT_LISTWIDGET_H
