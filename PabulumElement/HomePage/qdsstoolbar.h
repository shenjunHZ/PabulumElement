#ifndef QDSSTOOLBAR_H
#define QDSSTOOLBAR_H

#include "HomePage/qdlgskin.h"
#include "Menu/Menu.h"
#include "QPanelButton.h"

#include <QObject>
#include <list>

using std::list;
using namespace mainApp;
class QSingleMainDlg;

typedef struct stItemInfo
{
	QPanelButton *pBtn;
	QPushButton *pBtnClose;
	//QLabel *pLblLine;
	QWidget *pWidget;
	int nBeginX;
	QIcon menuIcon;
	QString menuName;
	QString strWidgetID;
	int iItemWidth;  //¼ÇÂ¼¿í¶È
}ToolBarItemInfo;

typedef struct DragShareData
{
	QWidget *DragSubWidget;
	char nDropTarget;
	char nDragDropRet;
	QIcon menuIcon;
	QString menuName;
	QString strWidgetID;
}BtnDragShareData;

class QDSSToolBar : public QDlgSkin
{
	Q_OBJECT
	Q_PROPERTY(bool ItemCloseable READ ItemCloseable)
public:
	explicit QDSSToolBar(QDlgSkin *parent = 0, bool bMainDlg =false);
	virtual~QDSSToolBar();

	int  AddItem(QPanelButton *btnItem, QWidget *SubWidget, int nPos, QIcon menuIcon = QIcon(), QString menuName = "", QString strWidgetID = "");
	int  RemoveItem(QPanelButton *btnItem, bool bDeleteBtn = true, bool bAnimation = true);
	void RemoveSelectItem();
	int  PopupSpecialWidget(const QString &strWidgetID);
	bool GetSpecialWidget(const QWidget *pWidget);
	int  PopupSpecialWidget(const QWidget *pWidget);
	//void MenuClicked(QAction* pAction);
	list<ToolBarItemInfo> m_lstWidget;
	void HideBtnAddPage();
	//QString GetIExploreBin();

protected:
	void resizeEvent(QResizeEvent *);
	//void paintEvent(QPaintEvent *);
	//void dragEnterEvent(QDragEnterEvent *);
	//void dragLeaveEvent(QDragLeaveEvent *);
	//void dropEvent(QDropEvent *event);
	//void dragMoveEvent(QDragMoveEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *);
	//bool eventFilter(QObject *obj, QEvent *event);

private:
	QLabel*		m_logo;

	QPanelButton *m_SelectButton;
	//QPushButton *m_btnDrop;
	QPushButton *m_btnMini;
	QPushButton *m_btnMax;
	QPushButton *m_btnClose;
	QPushButton *m_btnExchange;
	//QPushButton *m_btnBack2Home;

	//QWidget		*m_innerWgt;
	//QPushButton *m_btnPCStatus;
	//QPushButton *m_btnConfig;
	//QPushButton *m_btnUserInfo;

	QPushButton* m_pbtnAddPage;

	int m_nGlobalX;
	//DSGUI::DSMenu* m_menuDrop;
	const bool  m_bMainDlg;

	//void StartDrag(const list<ToolBarItemInfo>::iterator &);
	void SwitchButton(list<ToolBarItemInfo>::iterator &, int);
	//void RemoveActionFromMenu(QPanelButton *pBtnTarget);
	list<ToolBarItemInfo>::iterator GetWidgetByButton(QWidget*&, QPanelButton *target = NULL);
	void PopupToolBarItem(const ToolBarItemInfo& item);
	void CloseSubWidget(QPanelButton* pTargetBtn);
	bool ItemCloseable()const;

private slots:
	//void OnBtnLock();
	//void OnBtnServerIPClicked();
	void OnBtnMinimize();
	void OnBtnMax();
	void OnBtnEnter();
	void OnBtnLeave();
	void OnBtnPressed(QMouseEvent*);
	void OnBtnReleased();
	void OnCloseSubWidget();
	//void OnDropMenuClicked();
	void OnBtnMove(QMouseEvent*);
	//void OnExchangeUser();
	//void OnModifyPwd();
	//void OnBtnBack2Home();
	//void OnBtnShowLocalConfig();
	//void OnBtnShowHelp();
	//void OnBtnShowAbout();
	//void OnBtnShowConfig();
	//void OnBtnShowUserMenu();
	void OnBtnAddPage();
	//void OnOpenAlarmClicked();
	void OnBtnDbClicked();
	//void OnHomeLoginWidgetClicked(btn_type_e nType);
	//void OnAlarmReport();
	//void OnBtnPCStatusClicked();

signals:
	void sgnWantToClose();
	void sgnLockDlg(bool bLock);
	//void sgnExchangePwdFinish();
	//void sgnShowLocalConfig();
	void sgnShowUserInfo();
	void sgnLeaveUserInfo();
	void sgnHomePageShow(bool bPopup);
};

#endif // QDSSTOOLBAR_H
