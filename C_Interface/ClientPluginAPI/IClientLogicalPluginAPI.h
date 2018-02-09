#ifndef __DSPLUGINAPI_ICLIENTLOGICALPLUGINAPI_H__
#define __DSPLUGINAPI_ICLIENTLOGICALPLUGINAPI_H__

#include "IPluginAPI.h"

namespace DSPluginAPI
{
    class IAbstractResourceManager;

    /** @class IClientLogicalPluginAPI
      * @brief 逻辑资源插件
      *
      */
    class IClientLogicalPluginAPI : public IPluginAPI
    {
    public:
        // 绑定插件资源，可绑定多个[线程安全同步接口]
        virtual bool Bind(IAbstractResourceManager* pManager) = 0;
        // 解绑插件资源，需释放干净[线程安全同步接口]
        virtual bool Release(IAbstractResourceManager* pManager) = 0;

    public:
        // 初始化逻辑[线程安全同步接口，返回数据加载完成]
        virtual bool InitLogical() = 0;
        // [线程安全同步接口]
        virtual void UninitLogical() = 0;

    public:
        // 获取逻辑资源管理类，逻辑资源数据访问的唯一接口
        virtual IAbstractResourceManager* GetResourceManager() const = 0;
    };
}

#endif // __DSPLUGINAPI_ICLIENTLOGICALPLUGINAPI_H__
