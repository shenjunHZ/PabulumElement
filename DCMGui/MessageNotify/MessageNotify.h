#ifndef __DSGUI_MESSAGENOTIFY_H__
#define __DSGUI_MESSAGENOTIFY_H__

#include "DSGuiGlobal.h"
#include "Pattern/Singleton.h"
#include <QtNetwork/QLocalSocket>

namespace DSGUI
{
    class DSMessageNotifyPrivate;

    /** 类名：DSMessageNotify
     *  说明：右下角提示框
     *  此接口需在QCoreApplication::exec()返回之前使用
     **/
    class DS_GUI_EXPORT DSMessageNotify : public QObject,
        public DSSingleton<DSMessageNotify>
    {
        Q_OBJECT
        friend class DSSingleton<DSMessageNotify>;

    public:
        ~DSMessageNotify();

    public:
        // 提示框标题。需在提示框启动之前设置，只需设置一次即可。
        void SetMessageNotifyTitle(const QString& strTitle);
        // 传入参数，参数1为翻译资源列表，参数2为皮肤
        void SetParam(const QStringList& strListTranslations, const QStringList& strListSkins,const QString& strLang);
		// 启动消息提示框进程，上层调用
		void StartMessageProcess();

    public:
        // 添加文字提示信息
        void AddTextNotification(const QString& strNotifyInfo);
        // 添加图片提示信息
        void AddPictureNotification(const QString& strNotifyInfo, const QString& strFile);
		// 添加录像提示信息
		void AddRecordNotification(const QString& strNotifyInfo, const QString& strFile);
		// 显示进度条
		void ShowModalProgressBar(bool bShow);
    private:
        DSMessageNotify();

    private:
        QScopedPointer<DSMessageNotifyPrivate> d_ptr;

    private:
        Q_DECLARE_PRIVATE(DSMessageNotify)
        Q_DISABLE_COPY(DSMessageNotify)
        Q_PRIVATE_SLOT(d_func(), void OnAPPAboutToQuit())
        Q_PRIVATE_SLOT(d_func(), void OnAPPAboutToQuit())
        Q_PRIVATE_SLOT(d_func(), void OnLocalSocketError(QLocalSocket::LocalSocketError))
        
    };
}

#endif
