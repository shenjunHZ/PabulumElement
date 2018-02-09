/*
 *@file   Calendar.h
 *@brief  
 * 
 *@author wrb
 *@date   2015-02-04
 *
 */

#ifndef __DSGUI_CALENDAR_H
#define __DSGUI_CALENDAR_H

#include "DSGuiGlobal.h"
#include <QWidget>
#include <QtCore/QDate>

class QTableWidgetItem;
class QDate;

namespace Ui 
{
	class Calendar; 
}

namespace DSGUI
{
	class DSCalendarPrivate;
	/** @class DSCalendar
     *  @brief 日历
     */
	class DS_GUI_EXPORT DSCalendar : public QWidget
	{
		Q_OBJECT

	public:
		typedef enum{
			Day,
			Mouth,
			Year,
		}DisplayType_e;


	public:
		DSCalendar(QWidget* pParent = NULL);
		~DSCalendar();

		//设置选中的日期 时间
		int SetSelDate(int iYear, int iMonth, int iDay, int iHour = 0, int iMinute = 0, int iSecond = 0);
		int SetDateTime(QDateTime dt);
		
		//获取选中的日期 时间
		int GetSelDate(int* pYear, int* pMonth, int* pDay, int* pHour = NULL, int* pMinute = NULL, int* pSecond = NULL);
		int GetDateTime(QDateTime& dt);

		//设置给定日期是否有录像
		int	SetRecordDate(int iYear, int iMonth, int iDay, bool bHasRecrod = true);
		
		//清除所有录像
		void ClearCellWidget();

		//清除所有标记日期
		void ClearBackground();

		//限制可选的日期范围
		int SetRestrcitDateRange(int nDates);

		//设置日历的日期属性
		int SetStartCalendar(bool);

		//获取起始日期
		QDate GetDateStart();

		//获取结束日期
		QDate GetDateEnd();

		//调整展示形式
		void ChangeDisplayType(DisplayType_e eType);

		//隐藏时间编辑
		void SetTimeEditVisible(bool bVisible);

		//获取选中的日期 时间
		QDateTime GetSelectDate();

		//设置日历标题
		void SetCalendarName(QString strName);

	public slots:
		void OnStartDateTimeChanged(const QDate&);
		void OnEndDateTimeChanged(const QDate&);
		void OnCellDoubleClicked(int nRow,int nCol);

	protected:
		bool eventFilter(QObject * watched, QEvent * e);

	signals:
		void SgnDateTimeChanged();
		void SgnCalendarHide();

	private:
		QScopedPointer<DSCalendarPrivate> d_ptr;

	private:
		Q_DECLARE_PRIVATE(DSCalendar)
		Q_DISABLE_COPY(DSCalendar)
		Q_PRIVATE_SLOT(d_func(), void OnSelectionChanged())
		Q_PRIVATE_SLOT(d_func(), void OnNextMonth())
		Q_PRIVATE_SLOT(d_func(), void OnPreviewMonth())
		Q_PRIVATE_SLOT(d_func(), void OnShowYearWidget())
		Q_PRIVATE_SLOT(d_func(), void OnShowMonthWidget())
		Q_PRIVATE_SLOT(d_func(), void OnTabItemClicked(QTableWidgetItem*))
		Q_PRIVATE_SLOT(d_func(), void OnTableClick(QTableWidgetItem*))
		Q_PRIVATE_SLOT(d_func(), void OnDateTimeEditChanged(const QDateTime&))

	private:
		QScopedPointer<Ui::Calendar>	m_ptCalendarUI;
	};
}

#endif
