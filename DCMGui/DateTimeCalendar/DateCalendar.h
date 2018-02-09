// DATECALENDAR_H


/*
 *@file   DateCalendar.h
 *@brief  日期日历：展示年，月，周，日四种形式，选择日期
 * 
 *@author 28100
 *@date   
 *
 */
#ifndef __DSGUI_DATECALENDAR_H
#define __DSGUI_DATECALENDAR_H

#include "DSGuiGlobal.h"
#include <QLabel>
#include "Calendar/Calendar.h"

namespace DSGUI
{
	class DS_GUI_EXPORT DSDateCalendar : public QLabel
	{
		Q_OBJECT

	public:
		DSDateCalendar(QWidget *parent);
		~DSDateCalendar();

		void InitDate(QDateTime& dateTime);
		void ChangeDisplayType(DSCalendar::DisplayType_e eType);

	protected:
		void mousePressEvent(QMouseEvent * e);

	private slots:
		void OnDateTimeChanged();
		void OnCalendarHide();

	private:
		QString DtConvToString(QDateTime& dsTime);

	private:
		DSCalendar* m_pCalendar;
	};
}

#endif 

