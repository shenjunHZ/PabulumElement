#ifndef __COMMON_TASK_H__
#define __COMMON_TASK_H__

#include "Common/CommonGlobal.h"
#include <boost/function.hpp>

namespace Common
{
	class CFunctionTaskPrivate;

    class COMMON_EXPORT CTask
    {
    public:
        CTask() {}
        virtual ~CTask() {}

	public:
        virtual void Exec() = 0;
    };

    class COMMON_EXPORT CFunctionTask : public CTask
    {
    public:
        CFunctionTask(boost::function<void()> funtion);

        virtual ~CFunctionTask();

    public:
		virtual void Exec();

	private:
		DS_DECLARE_PRIVATE(CFunctionTask);
		CFunctionTaskPrivate* d_ptr;
    };
}

#endif // __COMMON_TASK_H__
