#ifndef __DSPLUGINAPI_IMQMANAGER_H__
#define __DSPLUGINAPI_IMQMANAGER_H__

#include "IAbstractResourceManager.h"

namespace DSPluginAPI
{
	template< class TObserver >
    class IMQManager : public IAbstractResourceManager
    {
    public:
        // 获取资源管理类ID，通过查文档标识
        virtual std::string GetResourceID() const
        {
            return "MQSDK";
        }

        // 获取资源所在的插件ID
        virtual std::string GetPluginID() const
        {
            return "MQSDK";
        }

    public:
        /** 如果要订阅多个主题，这个函数需要调用多次。
		  * @param[in] TObserver* pObserver        观察者
		  * @param[in] const std::string& strTopicURL   主题URL
		  * @return true：成功	false：失败
		  */
		virtual bool RegisterObserver(TObserver* pObserver, const std::string& strTopicURL) = 0;

		/** 取消订阅单个主题。
		* @param[in] TObserver* pObserver        观察者
		* @param[in] const std::string& strTopicType  主题
		  * @return true：成功	false：失败
		  */
		virtual bool UnRegisterObserver(TObserver* pObserver, const std::string& strTopicURL) = 0;
    };

}

#endif
