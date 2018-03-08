#ifndef QSINGLEMAINDLG_H
#define QSINGLEMAINDLG_H

#include "HomePage/qdlgskin.h"
#include "HomePage/qdsstoolbar.h"

#include <QTimer>

typedef enum{
	RESOLUTION_MAXIMIZE,
	RESOLUTION_960_680,
	RESOLUTION_1024_768,
	RESOLUTION_1280_800,
	RESOLUTION_1280_1024,
	RESOLUTION_1440_900,
	RESOLUTION_1680_1050,
}Resolution_e;

class QSingleMainDlg : public QDlgSkin
{
	Q_OBJECT

public:
	explicit QSingleMainDlg(QWidget *parent,bool bMain);
	virtual ~QSingleMainDlg();

	int  AddItem(QPanelButton *btnItem, QWidget *SubWidget, int nPos, QIcon menuIcon = QIcon(), QString menuName = "", QString strWidgetID = "");
	int  RemoveItem(QPanelButton *btnItem, bool bDeleteBtn, bool bAnimation);
	void SetHomePage(QWidget *pHomePage);
	QDSSToolBar* GetToolBar();
	//QHomeLoginInfo* GetLoginInfo();
	bool close();
	bool IsWidgetInToolBar(QString strWidgetID);
	//void InitLoginInfo(const QString &strUserNa, const QString &strServerIP);
	//QString GetUserName() const;
	//QString GetServerIP() const;
	//void	UpdateScreenResolution(int nSizeItem);

	void _SwitchMaximized();
	void _SwitchNormal();
	//Resolution_e GetResolutionType(){return m_EnumResolution;};

	
protected:
	void resizeEvent(QResizeEvent *);
	//bool eventFilter(QObject *obj, QEvent *event);

#ifdef WIN32
	//bool winEvent( MSG * message, long * result );
#endif
private:
	//工具条
	QDSSToolBar *m_toolBar;

	QWidget*		m_pBg;
	bool m_bQuit;
	QWidget*        m_pMainPage; // 主页不加在toolbar,临时存储主页
	const bool		m_bMainDlg; 

protected:
	void closeEvent( QCloseEvent * event ) ;

private slots:
	void OnCloseWindow();
	//void OnShowUserInfo();
	//void OnHideUserInfo();
	//void OnLeaveUserInfo();
	//void OnTimeout();
	//void OnChangeResolution(int);
signals:
	void sgnCloseWindow(QSingleMainDlg*);
	void sgnExchangePwdFinish();
	void sgnHomePageShow(bool bPopup);

private:
	//QTimer*      m_timer;
	//Resolution_e m_EnumResolution;
};


#endif // QSINGLEMAINDLG_H

