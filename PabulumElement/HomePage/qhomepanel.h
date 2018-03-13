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

	void SetPanelBtn(QVector<PanelBtnInfoEx_t> vecBtnInfo);

public slots:
	void OnBtnEnter(QString, bool bCombine);
	void OnBtnLeave();
	void OnBtnClicked(QString);
	void OnBtnPress(QString);

signals:
	void SignalShowFloat();

protected:

	void LaunchPlugin(PanelBtnInfo_t& btnInfo);

protected:
	QVector<PanelBtnInfoEx_t> m_vecBtnInfo;
};

#endif //QHOMEPANEL_H