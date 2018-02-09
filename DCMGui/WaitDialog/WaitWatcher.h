#ifndef __DSGUI_WAITDIALOGWATCHER_H__
#define __DSGUI_WAITDIALOGWATCHER_H__

#include "WaitDialog/WaitDialog.h"
#include "Pattern/Singleton.h"
#include <QFutureWatcher>
#include <QtConcurrentRun>

namespace DSGUI
{
    /** 类名：DSWaitDialogWatcher
     *  说明：等待框封装，可异步监听执行函数
     **/
	class DS_GUI_EXPORT DSWaitDialogWatcher 
        : public DSSingleton<DSWaitDialogWatcher>
	{
		friend class DSSingleton<DSWaitDialogWatcher>;
	public:
		~DSWaitDialogWatcher();

	public:
        /* @fn    int WaitFunction(T (*pFunction)(), QWidget* pParent)
         * @brief 异步执行函数pFunction，函数返回等待框消失
         * @param <IN> T (*pFunction)() - 函数指针
         * @param <IN> QWidget* pParent - 等待框父窗口
         * @return 等待框执行结果.
         */
		template <typename T>
		int WaitFunction(T (*pFunction)(), QWidget* pParent)
		{
            // 等待框
			DSWaitDialog dlgWait(pParent);
			QFutureWatcher<T>* pFutureWatcher = new QFutureWatcher<T>;
			// QFutureWatcher启动的函数返回，等待框消失
            QObject::connect(pFutureWatcher, SIGNAL(finished()), &dlgWait, SLOT(OnStopWaitImmediately()));

            // 异步启动函数
			QFuture<T> future = QtConcurrent::run(pFunction);
			pFutureWatcher->setFuture(future);
			int iRes = dlgWait.exec();

			delete pFutureWatcher;
            return iRes;
		}

        /* @fn    int WaitFunction(Class* pClass, T (Class::*pFunction)(), QWidget* pParent)
         * @brief 异步执行函数pFunction，函数返回等待框消失
         * @param <IN> Class* pClass    - 函数类
         * @param <IN> T (*pFunction)() - 函数指针
         * @param <IN> QWidget* pParent - 等待框父窗口
         * @return 等待框执行结果.
         */
		template <typename T, typename Class>
		int WaitFunction(Class* pClass, T (Class::*pFunction)(), QWidget* pParent)
		{
            // 等待框
			DSWaitDialog dlgWait(pParent);
			QFutureWatcher<T>* pFutureWatcher = new QFutureWatcher<T>;
			// QFutureWatcher启动的函数返回，等待框消失
			QObject::connect(pFutureWatcher, SIGNAL(finished()), &dlgWait, SLOT(OnStopWaitImmediately()));

            // 异步启动函数
			QFuture<T> future = QtConcurrent::run<T>(pClass, pFunction);
			pFutureWatcher->setFuture(future);
			int iRes = dlgWait.exec();
	        
			delete pFutureWatcher;
            return iRes;
		}

        /* @fn    int WaitFunction(Class* pClass, T (Class::*pFunction)(), const char* pCancelSlot, QWidget* pParent)
         * @brief 异步执行函数pFunction，函数返回等待框消失
         * @param <IN> Class* pClass            - 函数类
         * @param <IN> T (*pFunction)()         - 函数指针
         * @param <IN> const char* pCancelSlot  - 旋转等待框取消操作关联槽函数
         * @param <IN> QWidget* pParent         - 等待框父窗口
         * @return 等待框执行结果.
         */
        template <typename T, typename Class>
        int WaitFunction(Class* pClass, T (Class::*pFunction)(), const char* pCancelSlot, QWidget* pParent)
        {
            // 等待框
            DSWaitDialog dlgWait(pParent);
            QFutureWatcher<T>* pFutureWatcher = new QFutureWatcher<T>;
            // QFutureWatcher启动的函数返回，等待框消失
            QObject::connect(pFutureWatcher, SIGNAL(finished()), &dlgWait, SLOT(OnStopWaitImmediately()));
            // 关联取消操作
            QObject::connect(&dlgWait, SIGNAL(SignalCancelWait()), pClass, pCancelSlot);

            // 异步启动函数
            QFuture<T> future = QtConcurrent::run<T>(pClass, pFunction);
            pFutureWatcher->setFuture(future);
            int iRes = dlgWait.exec();

            delete pFutureWatcher;
            return iRes;
        }

        /* @fn    int WaitFunction(Class* pClass, T (Class::*pFunction)(Param1), const Arg1& arg1, const char* pCancelSlot, QWidget* pParent)
         * @brief 异步执行函数pFunction，函数返回等待框消失
         * @param <IN> Class* pClass                     - 函数类
         * @param <IN> T (Class::*pFunction)(Param1)     - 函数指针
         * @param <IN> const Arg1& arg1                  - 函数参数
         * @param <IN> const char* pCancelSlot           - 旋转等待框取消操作关联槽函数
         * @param <IN> QWidget* pParent                  - 等待框父窗口
         * @return 等待框执行结果.
         */
        template <typename T, typename Class, typename Param1, typename Arg1>
        int WaitFunction(Class* pClass, T (Class::*pFunction)(Param1), const Arg1& arg1, const char* pCancelSlot, QWidget* pParent)
        {
            // 等待框
            DSWaitDialog dlgWait(pParent);
            QFutureWatcher<T>* pFutureWatcher = new QFutureWatcher<T>;
            // QFutureWatcher启动的函数返回，等待框消失
            QObject::connect(pFutureWatcher, SIGNAL(finished()), &dlgWait, SLOT(OnStopWaitImmediately()));
            // 关联取消操作
            QObject::connect(&dlgWait, SIGNAL(SignalCancelWait()), pClass, pCancelSlot);

            // 异步启动函数
            QFuture<T> future = QtConcurrent::run<T>(pClass, pFunction, arg1);
            pFutureWatcher->setFuture(future);
            int iRes = dlgWait.exec();

            delete pFutureWatcher;
            return iRes;
        }

	private:
		DSWaitDialogWatcher();
	};
}


#endif // __DSGUI_WAITDIALOGWATCHER_H__
