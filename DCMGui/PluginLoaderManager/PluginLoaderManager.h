#ifndef __DSGUI_PLUGINLOADERMANAGER_H__
#define __DSGUI_PLUGINLOADERMANAGER_H__

#include "DSGuiGlobal.h"
#include <QStringList>
#include <QDir>
#include <QPluginLoader>

namespace DSGUI
{
    class DS_GUI_EXPORT DSPluginLoaderManager
    {
    public:
        // 加载路径strPath下的插件库，插件库的标记为strKey
        template <typename T>
        static T Load(const QString& strKey, const QString& strPath)
        {
            if (strKey.isNull())
            {
                return NULL;
            }

            QStringList strListPlugin = QDir(strPath).entryList(QDir::Files);
            for (int i = 0, iCount = strListPlugin.count(); i < iCount; ++i) 
            {
                QString strFileName = QDir::cleanPath(strPath + QLatin1Char('/') + strListPlugin.at(i));
                QPluginLoader loader(strFileName);
                if (loader.isLoaded()) // 已经加载
                {
                    QObject* pObject = loader.instance();
                    T pFactoryInterface = qobject_cast<T>(pObject);
                    if (NULL != pFactoryInterface)
                    {
                        // 获取key值，存在加载插件
                        QStringList strListKeys = pFactoryInterface->keys();
                        if (strListKeys.contains(strKey))
                        {
                            return pFactoryInterface;
                        }
                    }
                }
                else if (loader.load()) // 加载此库
                {
                    QObject* pObject = loader.instance();
                    T pFactoryInterface = qobject_cast<T>(pObject);
                    if (NULL != pFactoryInterface)
                    {
                        // 获取key值，存在key值加载插件
                        QStringList strListKeys = pFactoryInterface->keys();
                        if (strListKeys.contains(strKey))
                        {
                            return pFactoryInterface;
                        }
                    }

                    loader.unload();
                }
            }

            return NULL;
        }
    };
}

#endif // __DSGUI_PLUGINLOADERMANAGER_H__
