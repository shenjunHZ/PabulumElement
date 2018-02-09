#ifndef __DSPLUGINAPI_ICLIENTUIPLUGINAPI_H__
#define __DSPLUGINAPI_ICLIENTUIPLUGINAPI_H__

#include "IPluginAPI.h"
#include <QIcon>

namespace DSPluginAPI
{
    // 定义权限标识
    typedef std::string PluginRight;
    const PluginRight rightDefault = "Default Right"; // 默认权限

    class IAbstractUI;
    class IAbstractResourceManager;

    /** @class IClientUIPluginAPI
     *  @brief 客户端界面插件接口
     *
     *  职责：
     *  
     */
    class IClientUIPluginAPI : public IPluginAPI
    {
    public:
        // 插件权限唯一标识符，DSPluginAPI::rightDefault表示这个插件权限不做控制
        // 如有需要控制权限，可修改为对应权限值
        virtual DSPluginAPI::PluginRight GetPluginRightID() const { return DSPluginAPI::rightDefault; }

    public:
        // 绑定插件资源，可绑定多个[线程安全同步接口]
        virtual bool Bind(IAbstractResourceManager* pManager) = 0;
        // 解绑插件资源，需释放干净[线程安全同步接口]
        virtual bool Release(IAbstractResourceManager* pManager) = 0;

    public:
        // 逻辑层[线程安全同步接口]
        virtual bool InitLogical() = 0;
        // [线程安全同步接口]
        virtual void UninitLogical() = 0;

    public:
        // UI层[线程安全同步接口]
        virtual void InitUI() = 0;
        // 可在此处销毁IAbstractUI[线程安全同步接口]
        virtual void UninitUI() = 0;

    public:
        // 获取抽象的界面，插件返回数据的唯一接口，为空插件加载失败
        // IAbstractUI生命期可在UninitUI接口触发后销毁
        virtual IAbstractUI* GetAbstractUI() const = 0;
    };

    class IAbstractWidget;

    /** @class IAbstractUI
     *  @brief 抽象的界面
     *
     *  职责：
     *  
     */
    class IAbstractUI
    {
    public:
        virtual ~IAbstractUI() {}

    public:
        // 创建抽象的窗口，控制面板只显示此窗口信息，为空插件加载失败
        virtual IAbstractWidget* CreateAbstractWidget() const = 0;

        // 通过窗口ID获取抽象的窗口
        virtual IAbstractWidget* GetAbstractWidget(const std::string& strWidgetID) const = 0; 
    };

    /** @class IAbstractWidget
     *  @brief 抽象的窗口
     *  
     */
    class IAbstractWidget
    {
    public:
        virtual ~IAbstractWidget() {}

    public:
        // 获取窗口类型标记
        virtual std::string GetWidgetID() const = 0;

        // 获取显示窗口，可以释放
        virtual QWidget* GetWidget() const = 0;

    public:
        // 获取面板名称
        virtual QString GetPanelName() const = 0;
        // 获取面板图标
        virtual QIcon GetPanelIcon() const = 0;
        // 获取面板详细描述
        virtual QString GetPanelDetails() const = 0;

    public:
        // 获取tab页名称
        virtual QString GetTabName() const = 0;
        // 获取tab页图标
        virtual QIcon GetTabIcon() const = 0;

    public:
        // 获取菜单名称
        virtual QString GetMenuName() const = 0;
        // 获取菜单图标
        virtual QIcon GetMenuIcon() const = 0;

    public:
        // 获取值
        virtual QVariant GetValue(int iType) const = 0;

    public:
        // close = 1 tab切换 = 2
        virtual bool OnMsg(int iType, const QVariant& vtParam1, const QVariant& vtParam2) = 0;
    };
}

// Q_DECLARE_INTERFACE(ClassName, Identifier)
// Identifier唯一，定义1.0为插件版本控制
Q_DECLARE_INTERFACE(DSPluginAPI::IClientUIPluginAPI, "com.DSPluginAPI.IClientUIPluginAPI(1.0)");

#endif // __DSPLUGINAPI_ICLIENTUIPLUGINAPI_H__
