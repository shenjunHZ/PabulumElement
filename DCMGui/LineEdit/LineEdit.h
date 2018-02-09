/*
 *@file   DSLineEdit.h
 *@brief  
 * 
 *@author 
 *@date   2014-05-27
 *
 */

#ifndef __DSGUI_DSLINEEDIT_H
#define __DSGUI_DSLINEEDIT_H

#include "DSGuiGlobal.h"
#include <QLineEdit>
#include <QLabel>

namespace DSGUI
{
	/**  @class CLineEdit
	 *   @brief ±à¼­¿ò
	 */
	class DS_GUI_EXPORT DSLineEdit : public QLineEdit
	{
		Q_OBJECT

	Q_PROPERTY(bool error READ errorState WRITE setErrorState)

	public:
		DSLineEdit(QWidget* pParent = NULL);
		~DSLineEdit();

		bool errorState() const{return m_bErrorState;}
		void setErrorState(bool bState){m_bErrorState = bState;}
		void showErrorHint(bool bState, QString errMsg = "");

	private:
		bool m_bErrorState;
		QLabel*	 m_pHintLab;
	};
}

#endif
