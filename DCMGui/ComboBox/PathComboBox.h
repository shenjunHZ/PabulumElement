/*
 *@file   PathComboBox.h
 *@brief  路径选择控件
 * 
 *@author cc
 *@date   2016-12-03
 *
 */

#ifndef _DSGUI_PATHCOMBOBOX_H
#define _DSGUI_PATHCOMBOBOX_H

#include "DSGuiGlobal.h"
#include <QComboBox>
#include <QFileDialog>

namespace DSGUI
{
	/**  类名：DSPathComboBox
	 *   说明  路径选择控件
	**/
	class DS_GUI_EXPORT DSPathComboBox : public QComboBox
	{
		Q_OBJECT

	public:
		// 构造
		DSPathComboBox(QWidget* pParent = NULL);
		~DSPathComboBox();

		// 参看QFileDialog::setFileMode
		void SetFileMode(QFileDialog::FileMode enumMode);

		// 设置标题栏
		void SetTitle(const QString& strTitle);

		// 参看QFileDialog::setFilter
		void SetFilter(const QString& strFilter);

		// 参看QFileDialog::setDirectory
		void SetDirectory(const QString& strDirectory);

	protected:
		virtual void showPopup();
		virtual void mousePressEvent(QMouseEvent* pEvent);
		virtual void keyPressEvent(QKeyEvent* pEvent);

	private:
		QFileDialog::FileMode m_enumMode; 
		QString m_strTitle;
		QString m_strFilter;
		QString m_strDirectory;
	};
}


#endif // _DSGUI_PATHCOMBOBOX_H
