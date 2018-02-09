#ifndef __COMMON_PLUGINLOADER_H__
#define __COMMON_PLUGINLOADER_H__

#include "Common/CommonGlobal.h"
#include <string>
#include <list>

namespace DSPluginAPI
{
	struct IPluginAPI;
}

namespace Common
{
    class CPluginLoaderPrivate;
	class COMMON_EXPORT CPluginLoader
	{
	public:
		explicit CPluginLoader(const std::string& strFileName);
		~CPluginLoader();

    public:
        // 获取当前加载的库，插件加载对象需调用Unload()释放
		DSPluginAPI::IPluginAPI* GetInstance();
        // 获取全局加载的库
        static std::list<DSPluginAPI::IPluginAPI*> GetGlobalInstances();
	public:
		bool Load();
		bool Unload();
		bool IsLoaded() const;

    private:
        DS_DECLARE_PRIVATE(CPluginLoader);
        CPluginLoaderPrivate* d_ptr;
        DS_DISABLE_COPY(CPluginLoader);
	};
}

#endif // __COMMON_PLUGINLOADER_H__
