#pragma once

#include "HomePage/qdlgskin.h"
#include "HomePage/qhomebasic.h"
#include "HomePage/ViewDefine.h"

using namespace mainApp;

namespace mainApp
{
    class MaterialRepositoryWidget;
    class MaterialAnalyzeWidget;
}

class HomePage : public QDlgSkin
{
    Q_OBJECT

public:
public:
    explicit HomePage(QWidget *parent = 0);
    ~HomePage();

    void InitModule(mainApp::MaterialRepositoryWidget* pMaterialRepositoryWidget, mainApp::MaterialAnalyzeWidget* pMaterialAnalyzeWidge);

    QHomeBasic *m_mdBasic;

protected:
    //virtual bool event(QEvent *event);
    virtual void mousePressEvent(QMouseEvent * event);

private slots:
    //void OnBtnEnter(QString, bool);
    //void OnBtnLeave();
    //void OnBtnClicked(QString);

private:

private:
    QVector<PanelBtnInfoEx_t> m_vecBtnInfo;
};
