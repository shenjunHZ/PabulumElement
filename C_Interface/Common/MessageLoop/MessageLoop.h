#ifndef __COMMON_MESSAGELOOP_H__
#define __COMMON_MESSAGELOOP_H__

#include "Common/CommonGlobal.h"
#include "Common/Pattern/Singleton.h"

namespace Common
{
	class CBaseMessageLoopPrivate;
	class CTask;

	// 单线程消息循环
	class COMMON_EXPORT CBaseMessageLoop
	{
	public:
		// 塞入队列
		bool PostTask(CTask* pTask);
	public:
		// 启动消息队列(全局调用)
		bool Start();
		// 停止消息队列(全局调用)
		void Stop();

		//消息线程是否已经启动
		bool IsRunning() const;

	protected:
		CBaseMessageLoop();
		~CBaseMessageLoop();

		// 消息队列循环
		void Run();

	private:
		DS_DECLARE_PRIVATE(CBaseMessageLoop);
		CBaseMessageLoopPrivate* d_ptr;
	};

	// 界面状态更新队列
	class COMMON_EXPORT CMessageLoopForUI : public CBaseMessageLoop,
		public CSingleton<CMessageLoopForUI>
	{
		friend class CSingleton<CMessageLoopForUI>;
	};
}

#endif // __COMMON_MESSAGELOOP_H__