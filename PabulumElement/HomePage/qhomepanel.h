#ifndef QHOMEPANEL_H
#define QHOMEPANEL_H

#include "TabPanel/TabPanel.h"
#include "ViewDefine.h"

#include <QtWidgets/QLabel>

class QHomePanel : public DSGUI::DSTabPanel
{
	Q_OBJECT

public:
	QHomePanel(QWidget *parent = 0);
	~QHomePanel();

	void SetTitle(QString strTitle);
	void SetPanelBtn(QVector<PanelBtnInfoEx_t> vecBtnInfo);

public slots:
	void OnBtnEnter(QString, bool bCombine);
	void OnBtnLeave();
	void OnBtnClicked(QString);
	void OnBtnPress(QString);

signals:
	void SignalShowFloat();
	//void SignalHideFloat();

protected:

	void LaunchPlugin(PanelBtnInfo_t& btnInfo);
	QLabel* CreateLabel(QWidget*parent, const QRect&,const QString &, const QColor& txtColor=Qt::black, const QColor& bgColor="");

protected:
	//QLabel *m_lblPromptPointer;
	//QLabel *m_lblPrompt;
	QVector<PanelBtnInfoEx_t> m_vecBtnInfo;
};

#endif //QHOMEPANEL_H