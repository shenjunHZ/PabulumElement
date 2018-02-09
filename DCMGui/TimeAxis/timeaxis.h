#ifndef _DSGUI_TIMEAXIS_H
#define _DSGUI_TIMEAXIS_H

#include "DSGuiGlobal.h"
#include "Interval.h"
#include <QWidget>
#include <QMap>

class QResizeEvent;
class QWheelEvent;
class QPaintEvent;
class QMouseEvent;
class QTimerEvent;

namespace DSGUI
{
	class DSTimeAxisPrivate;
	class DS_GUI_EXPORT DSTimeAxis : public QWidget
	{
		Q_OBJECT
		Q_PROPERTY(QColor baseColor READ GetBaseColor WRITE SetBaseColor)
		Q_PROPERTY(QColor timeFontColor READ GetTimeFontColor WRITE SetTimeFontColor)
		Q_PROPERTY(QColor timeGraduColor READ GetTimeGraduColor WRITE SetTimeGraduColor)
		Q_PROPERTY(QColor timeGraduReflectionColor READ GetTimeGraduReflectionColor WRITE SetTimeGraduReflectionColor)
		Q_PROPERTY(QColor timeRegionColor READ GetTimeRegionColor WRITE SetTimeRegionColor)
		Q_PROPERTY(QColor selectRegionColor READ GetSelectRegionColor WRITE SetSelectRegionColor)
		Q_PROPERTY(QColor lockRegionColor READ GetLockRegionColor WRITE SetLockRegionColor)
		Q_PROPERTY(QColor playRegionColor READ GetPlayRegionColor WRITE SetPlayRegionColor)
		Q_PROPERTY(QColor selectBorderColor READ GetSelectBorderColor WRITE SetSelectBorderColor)
		Q_PROPERTY(QColor lockBorderColor READ GetLockBorderColor WRITE SetLockBorderColor)
		Q_PROPERTY(int timeRegionHeight READ GetTimeRegionHeight WRITE SetTimeRegionHeight)
		Q_PROPERTY(int graduLabelHeight READ GetGraduLabelHeight WRITE SetGraduLabelHeight)
		Q_PROPERTY(int playRegionHeight READ GetPlayRegionHeight WRITE SetPlayRegionHeight)
		Q_PROPERTY(int utilRegionHeight READ GetUtilRegionHeight WRITE SetUtilRegionHeight)
		Q_PROPERTY(QPixmap selectOnCursor READ GetSelectOnCursor WRITE SetSelectOnCursor)
		Q_PROPERTY(QPixmap selectPressedCursor READ GetSelectPressedCursor WRITE SetSelectPressedCursor)
		Q_PROPERTY(QPixmap lockOnCursor READ GetLockOnCursor WRITE SetLockOnCursor)
		Q_PROPERTY(QPixmap lockPressedCursor READ GetLockPressedCursor WRITE SetLockPressedCursor)

	public:
		typedef enum{
			NORMAL = 0,    
			LOCK,			
			CUT				
		}ModeType_e;

	public:
		DSTimeAxis(QWidget *parent);
		~DSTimeAxis();

		void Init(qint64 start,qint64 end, bool bDynamic = false);
		inline ModeType_e CurrentMode() const;
		void InsertTimeList(int level, const IntervalList& invs);
		void ClearTimeList(int level = -1);
		void InsertTimeInterval(int level, const Interval& inv);
		void InsertLevelColor(int level, QColor color);
		void InsertLevelColor(int level, QVector<QColor> colorVec);
		void ClearColor(int level = -1);
		bool EnterOperMode(ModeType_e);
		void ExitOperMode();
		void AdjustCurrentOperInterval(const Interval& inv);
		void ClearCurrentOperInterval();
		void InsertLockInterval(const Interval& inv);
		void ClearLockInterval(const Interval& inv);
		void ClearAllLockInterval();
		void ShowPlayIndicator(bool bShow);
		inline bool IsPlayIndicatorVisible()const;
		void UpdatePlayIndicator(qint64 time);
		qint64 GetPlayIndicatorTime() const;
		void Scale(bool bLarge);
		void IsScaleEnabled(bool& bUp,bool &bDown);
		qint64 PosToTime(double pos);
		double TimeToPos(qint64 time);
		bool TimeContained(qint64 time);
		void SetFormat(int interval /*= 3600*/, int split/* = 2*/,const QString&);

	public:
		virtual QSize sizeHint() const;
		virtual QSize minimumSizeHint() const;
		virtual int heightForWidth(int) const;

	public:
		void SelectSwitch(bool bSwitch,qint64 tmStart, qint64 tmEnd); 
		void SelectChange(qint64);

	private:
		void _d_scale(double pos, int steps);
		void _d_resize(int width);

	protected:
		virtual void paintEvent(QPaintEvent *e);
		virtual void wheelEvent(QWheelEvent *e);
		virtual void resizeEvent(QResizeEvent *e);
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseMoveEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);
		virtual void mouseDoubleClickEvent(QMouseEvent *e);
		virtual void enterEvent(QEvent* e);
		virtual void leaveEvent(QEvent* e);
		virtual void timerEvent(QTimerEvent *e);

signals:
		void sgnTimeDbClicked(qint64 time);
		void sgnPlayIndicatorValueChanged(qint64 time);
		void sgnSelectSwitch(bool bOpen, bool bCommit, 
			qint64 startTime, qint64 currentTime,
			const Interval& inv);
		void sgnSelectChanged(qint64);
		void sgnLockInterval(const Interval&);
		void sgnCutInterval(const Interval&);

	private:
		bool                        m_bShowPlayIndicator;
		qint64                      m_tmPlayIndicator;
		QMap<int,IntervalList>		m_timeIntervalMap;
		QMap<int,QVector<QColor>>	m_colorIndex;
		IntervalList				m_lockBlocks;
		IntervalList				m_mergedlockBlocks;
		Interval                    m_invOper;
		ModeType_e					m_eMode;

	private:
		void SetBaseColor(const QColor& color);
		QColor GetBaseColor() const;
		void SetTimeFontColor(const QColor& color);
		QColor GetTimeFontColor() const;
		void SetTimeGraduColor(const QColor& color);
		QColor GetTimeGraduColor() const;
		void SetTimeGraduReflectionColor(const QColor& color);
		QColor GetTimeGraduReflectionColor() const;
		void SetTimeRegionColor(const QColor& color);
		QColor GetTimeRegionColor() const;
		void SetPlayIndicatorColor(const QColor& color);
		QColor GetPlayIndicatorColor() const;
		void SetSelectRegionColor(const QColor& color);
		QColor GetSelectRegionColor() const;
		void SetLockRegionColor(const QColor& color);
		QColor GetLockRegionColor() const;
		void SetPlayRegionColor(const QColor& color);
		QColor GetPlayRegionColor() const;
		void SetSelectBorderColor(const QColor& color);
		QColor GetSelectBorderColor() const;
		void SetLockBorderColor(const QColor& color);
		QColor GetLockBorderColor() const;
		void SetTimeRegionHeight(int h);
		int GetTimeRegionHeight() const;
		void SetGraduLabelHeight(int h);
		int GetGraduLabelHeight() const;
		void SetPlayRegionHeight(int h);
		int GetPlayRegionHeight() const;
		void SetUtilRegionHeight(int h);
		int GetUtilRegionHeight() const;
		void SetSelectOnCursor(const QPixmap& pixmap);
		QPixmap GetSelectOnCursor() const;
		void SetSelectPressedCursor(const QPixmap& pixmap);
		QPixmap GetSelectPressedCursor() const;
		void SetLockOnCursor(const QPixmap& pixmap);
		QPixmap GetLockOnCursor() const;
		void SetLockPressedCursor(const QPixmap& pixmap);
		QPixmap GetLockPressedCursor() const;

	private:
		QScopedPointer<DSTimeAxisPrivate> d_ptr;
		Q_DECLARE_PRIVATE(DSTimeAxis)
		Q_DISABLE_COPY(DSTimeAxis)
	};

	inline bool DSTimeAxis::IsPlayIndicatorVisible() const
	{
		return m_bShowPlayIndicator;
	}

	inline DSTimeAxis::ModeType_e DSTimeAxis::CurrentMode() const
	{
		return m_eMode;
	}

}
#endif // 
