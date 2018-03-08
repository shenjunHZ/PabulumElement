#ifndef QHOMEBASIC_H
#define QHOMEBASIC_H

#include "HomePage/qhomepanel.h"
#include "ViewDefine.h"

class QHomeBasic : public QHomePanel
{
    Q_OBJECT

public:
    QHomeBasic(QWidget *parent = 0);
    ~QHomeBasic();

public:
    //bool ShowRealMonitorView(QVariant Param);
    //bool ShowPlayBackView(QVariant Param);
    //bool ShowLocalConfig();
    //bool ShowModel(QVariant Param);
    void AddButtons();
    int	ClickBtn(QString strWidgetID);
    QList<DSGUI::TabPanel_t> GetPanelBtnList();

protected:
    //void resizeEvent(QResizeEvent *);
};

#endif // QHOMEBASIC_H
