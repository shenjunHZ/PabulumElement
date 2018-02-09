#ifndef __DSGUI_WAITDIALOG_H__
#define __DSGUI_WAITDIALOG_H__

#include "DSGuiGlobal.h"
#include <QDialog>

class Ui_CWaitDialogUI;
namespace DSGUI
{
    class DSWaitDialogPrivate;

	/** 类名：DSWaitDialog
	 *  说明  等待框
	 **/
	class DS_GUI_EXPORT DSWaitDialog : public QDialog
	{
		Q_OBJECT
	public:
        // 构造与析构
		DSWaitDialog(QWidget* pParent = NULL);
		~DSWaitDialog();

	signals:
        // 取消等待操作
		void SignalCancelWait();

    public Q_SLOTS:// 槽函数
        // 取消等待操作，会触发SignalCancelWait
		void OnCancelWait();
        // 立即停止等待，正常结束
		void OnStopWaitImmediately();

	protected:
		virtual void paintEvent(QPaintEvent *e);

    private:
        QScopedPointer<DSWaitDialogPrivate> d_ptr;

    private:
        Q_DECLARE_PRIVATE(DSWaitDialog)
        Q_DISABLE_COPY(DSWaitDialog)
        Q_PRIVATE_SLOT(d_func(), void OnTimeout())

    private:
        QScopedPointer<Ui_CWaitDialogUI> m_ptWaitDialogUI;

	};
}

#endif // __DSGUI_WAITDIALOG_H__
