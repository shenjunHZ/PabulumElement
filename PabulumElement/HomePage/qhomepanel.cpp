#include "HomePage/qhomepanel.h"
#include "AppCommon/ClientApp.h"
#include "MessageNotify/MessageNotify.h"

#include "libdsl/dslbase.h"

Q_DECLARE_METATYPE(QVector<std::string>);

QHomePanel::QHomePanel(QWidget *parent)
    : DSGUI::DSTabPanel(parent)
{
    SetGridSize(QSize(PANNELITEM_WIDTH, PANNELITEM_HEIGHT));
    SetMargins(PANNELBORDER_LEFT, PANNELBORDER_TOP, PANNELBORDER_RIGHT, PANNELBORDER_BOTTOM);
    SetHSpacing(PANNELITEM_HSPACEING);
    SetVSpacing(PANNELITEM_VSPACEING);

    SetDragDropModes(DSTabPanel::InternalMove | DSTabPanel::DragDrop);

    connect(this, SIGNAL(SignalHoverEnter(QString, bool)), this, SLOT(OnBtnEnter(QString, bool)));
    connect(this, SIGNAL(SignalHoverLeave()),              this, SLOT(OnBtnLeave()));
    connect(this, SIGNAL(SignalClickedTab(QString)),       this, SLOT(OnBtnClicked(QString)));
    connect(this, SIGNAL(SignalPressTab(QString)),         this, SLOT(OnBtnPress(QString)));
    connect(this, SIGNAL(SignalTabPanelGroup()),           this, SIGNAL(SignalShowFloat()));
}

QHomePanel::~QHomePanel()
{
    for each (PanelBtnInfoEx_t btnInfo in m_vecBtnInfo)
    {
        PanelBtnInfoList& lsPanelBtnInfo = btnInfo.lsPanelBtnInfo;
        for each (PanelBtnInfo_t info in lsPanelBtnInfo)
        {
            if (nullptr != info.pIcon)
            {
                SAFE_DELETE(info.pIcon);
            }
        }
    }
}

void QHomePanel::SetPanelBtn(QVector<PanelBtnInfoEx_t> vecBtnInfo)
{
    m_vecBtnInfo = vecBtnInfo;
}

QLabel* QHomePanel::CreateLabel(QWidget*parent, const QRect& lblRec, const QString& lblText, const QColor& txtColor ,  const QColor& bgColor )
{
    QLabel * lbl = new QLabel(parent);
    lbl->setGeometry(lblRec);
    lbl->setText(lblText);

    QPalette pal;
    if(txtColor.isValid())
    {
        pal.setColor(QPalette::WindowText, txtColor);
    }
    if(bgColor.isValid())
    {
        pal.setColor(QPalette::Background, bgColor);
        lbl->setAutoFillBackground(true);
    }
    lbl->setPalette(pal);
    return lbl;
}

void QHomePanel::SetTitle(QString strTitle)
{
    QLabel *lblTitle = CreateLabel(this, QRect(0,0,150,24),strTitle,QColor::fromRgba(0xff5d6778));
    lblTitle->setAlignment(Qt::AlignCenter);
    lblTitle->setObjectName("HomeMouduleTitle");
}

void QHomePanel::OnBtnEnter(QString strPluginID, bool bCombine)
{

}

void QHomePanel::OnBtnLeave()
{

}

void QHomePanel::OnBtnClicked(QString strPluginID)
{
    bool bFind = false;
    for (QVector<PanelBtnInfoEx_t>::iterator it = m_vecBtnInfo.begin(); it != m_vecBtnInfo.end(); it++)
    {
        PanelBtnInfoList& lsPanelBtnInfo = it->lsPanelBtnInfo;
        for (PanelBtnInfoList::iterator iter = lsPanelBtnInfo.begin(); iter != lsPanelBtnInfo.end(); iter++)
        {
            PanelBtnInfo_t& struPanelBtnInfo = *iter;
            if (strPluginID == struPanelBtnInfo.strPluginID)
            {
                LaunchPlugin(struPanelBtnInfo);
                bFind = true;
                break;
            }
        }

        if (bFind)
        {
            break;
        }
    }
}

void QHomePanel::OnBtnPress(QString)
{
    //emit SignalHideFloat();
}

void QHomePanel::LaunchPlugin(PanelBtnInfo_t& btnInfo)
{
    int nTryRet = -1;
    QPanelButton *pAddBtn = nullptr;
    QIcon menuIcon;
    QString menuName = "";

    if ((nTryRet = theApp.m_pContainManager->TrytoAddItem(QString::fromStdString(btnInfo.vecWidgetID))) == 0)
    {
        QString strTabName = QString("%1").arg(btnInfo.strPluginID);
        pAddBtn = new QPanelButton(this, strTabName);
//      QIcon icon = pAbWidget->GetTabIcon();
//      pAddWidget = pAbWidget->GetWidget();
//      menuIcon = pAbWidget->GetMenuIcon();
//      menuName = pAbWidget->GetMenuName();
//      strWidgetID = QString::fromStdString(pAbWidget->GetWidgetID());
        if (theApp.m_pContainManager->AddItem(theApp.m_pMainDlg, pAddBtn, btnInfo.pWidget, 0, *(btnInfo.pIcon), 
            strTabName, QString::fromStdString(btnInfo.vecWidgetID)) < 0)
        {
            Q_DELETE(pAddBtn);
        }
    }
    else if (nTryRet == 1)
    {
        if ("" != btnInfo.vecWidgetID)
        {
            theApp.m_pContainManager->PopupSpecialWidget(QString::fromStdString(btnInfo.vecWidgetID));
        }
    }
}

