#ifndef DSSTATUSLABEL_H
#define DSSTATUSLABEL_H

#include "DSGuiGlobal.h"
#include <QLabel>

namespace DSGUI
{
class DS_GUI_EXPORT DSStatusLabel : public QLabel
{
	Q_OBJECT

public:
	DSStatusLabel(QWidget *parent);
	~DSStatusLabel();

	void SetHighLevelColor(QColor);
	void SetMidLevelColor(QColor);
	void SetLowLevelColor(QColor);

	void  SetStatusPercent(int iPercent);

private:
	void paintEvent(QPaintEvent *event);

	int GetDrawSize(int iPercent);
	QColor GetStatusLevelColor(int iPercent);

	QColor HighColor;
	QColor MidColor;
	QColor LowColor;

	int m_iHighPercent;
	int m_iMidPercent;
	int m_iLowPercent;

	int m_iPercent;


	
};
}

#endif // DSSTATUSLABEL_H
