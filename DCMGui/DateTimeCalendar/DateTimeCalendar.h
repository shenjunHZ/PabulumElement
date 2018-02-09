#ifndef __DSGUI_DATETIMECALENDAR_H
#define __DSGUI_DATETIMECALENDAR_H

#include "DSGuiGlobal.h"
#include <QPushButton>
#include <QDateTime>

namespace DSGUI
{
	class DSCalendarEx;

	class DS_GUI_EXPORT DSDateTimeCalendar : public QPushButton
	{
		Q_OBJECT

	public:
		DSDateTimeCalendar(QWidget *parent);
		~DSDateTimeCalendar();

		//设置结束日历的可选日期
		void SetRestrcitDateRange(int iDays);

		//设置日历日期
		void SetSelDate(const QDateTime& dtStart, const QDateTime& dtEnd = QDateTime());

		//获取日期范围
		void DateTimeRange(QDateTime& dtStart, QDateTime& dtEnd);

		//设置录像
		void SetStartRecordDate(int iYear, int iMonth, int iDay, bool bHasRecrod = true);
		void SetEndRecordDate(int iYear, int iMonth, int iDay, bool bHasRecrod = true);

		//清除录像
		void ClearRecord();

	protected:
		void mousePressEvent(QMouseEvent * e);
		bool eventFilter(QObject *, QEvent *);

	signals:
		void SgnStartYearMonthChanged(int,int);
		void SgnEndYearMonthChanged(int,int);
		void SgnDateTimeChanged(const QDateTime& start,const QDateTime& end);

	private:
		QString DtConvToString(const QDateTime& dtStart, const QDateTime& dtEnd);

	private slots:
		void OnDateTimeChanged();
		void OnStartYearMonthChanged();
		void OnEndYearMonthChanged();
		void OnCalendarHide();

	private:
		DSCalendarEx* m_pCalendar;

	};
}

#endif // DSDATETIMECALENDAR_H
