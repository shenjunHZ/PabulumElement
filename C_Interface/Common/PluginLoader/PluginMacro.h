#ifndef __COMMON_PLUGINMACRO_H__
#define __COMMON_PLUGINMACRO_H__

#include "Common/CommonGlobal.h"
#include <list>

#ifdef WIN32
#define PLUGIN_EXPORT __declspec(dllexport)
#else
#define PLUGIN_EXPORT
#endif

#if (defined IOS) || (defined ANDROID)
#define DS_EXPORT_PLUGIN1(IMPLEMENTATION) 
#else
COMMON_EXPORT void qRegisterStaticPluginInstanceFunction(DSPluginAPI::IPluginAPI* pPlugin);

#define DS_EXPORT_PLUGIN1(IMPLEMENTATION) \
extern "C" PLUGIN_EXPORT DSPluginAPI::IPluginAPI* DS_Plugin_GetInstance() \
{ \
    static DSPluginAPI::IPluginAPI* s_instance; \
    if (NULL == s_instance) \
    { \
        s_instance = new IMPLEMENTATION; \
    } \
    qRegisterStaticPluginInstanceFunction(s_instance);        \
    return s_instance; \
} 
#endif

#endif