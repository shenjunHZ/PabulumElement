#ifndef __DSPLUGINAPI_ICLIENTOPERATEPLUGINAPI_H__
#define __DSPLUGINAPI_ICLIENTOPERATEPLUGINAPI_H__

#include <QFactoryInterface>
#include <QtPlugin>

namespace DSPluginAPI
{
    /** @class IClientSkinPluginAPI
      * @brief 皮肤库插件
      */
    struct IClientSkinPluginAPI : public QFactoryInterface
    {
        virtual bool LoadSkin(const QString& strKey) = 0;
    };
}

// Q_DECLARE_INTERFACE(ClassName, Identifier)
// Identifier唯一，定义1.0为插件版本控制
Q_DECLARE_INTERFACE(DSPluginAPI::IClientSkinPluginAPI, "com.DSPluginAPI.IClientSkinPluginAPI(1.0)");

#endif
