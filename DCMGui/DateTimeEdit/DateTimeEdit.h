#ifndef DSDATETIMEEDIT_H
#define DSDATETIMEEDIT_H

#include "DSGuiGlobal.h"
#include <QDateTimeEdit>
#include <qtoolbutton.h>

namespace DSGUI
{
	class DSCalendar;

	class DS_GUI_EXPORT DSDateTimeEdit : public QDateTimeEdit
	{
		Q_OBJECT

	public:
		DSDateTimeEdit(QWidget *pParent=NULL);
		~DSDateTimeEdit();

		void SetStartCalendar(bool bStartCalendar);
		int SetRecordDate(int iYear, int iMonth, int iDay, bool bHasRecrod = true);
		void ClearHasRecord();
		void SetRestrcitDateRange(int iDays);
		void SetCurTime(const QDateTime&);

	public slots:
		void OnStartDateTimeChanged(const QDate&);

	protected:
		virtual void mousePressEvent(QMouseEvent *pEvent);
		virtual bool eventFilter(QObject* pObj,QEvent *pEvent);

signals:
		void SgnYearMonthChanged(int iYear,int iMonth);
		void SgnStartDateChanged(const QDate&);

	private slots:
		void OnUpdateTime();
		void OnCalendarHide();

	private:
		void ShowCalendar();

	private:
		DSCalendar*	m_pCalendar;

		bool		m_bStartCalendar;	//是否是起始Edit
		QDate		m_StartDate;		//起始日期
		int			m_iRestrictDays;	//限制日期段

		int			m_iYear;			//当前年份
		int			m_iMonth;			//当前月份
	};
}

#endif // DSDATETIMEEDIT_H
