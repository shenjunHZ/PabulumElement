#ifndef __DSPLUGINAPI_ICLIENTUIPLUGINAPI_H__
#define __DSPLUGINAPI_ICLIENTUIPLUGINAPI_H__

#include "IPluginAPI.h"
#include <QIcon>

namespace DSPluginAPI
{
    // ����Ȩ�ޱ�ʶ
    typedef std::string PluginRight;
    const PluginRight rightDefault = "Default Right"; // Ĭ��Ȩ��

    class IAbstractUI;
    class IAbstractResourceManager;

    /** @class IClientUIPluginAPI
     *  @brief �ͻ��˽������ӿ�
     *
     *  ְ��
     *  
     */
    class IClientUIPluginAPI : public IPluginAPI
    {
    public:
        // ���Ȩ��Ψһ��ʶ����DSPluginAPI::rightDefault��ʾ������Ȩ�޲�������
        // ������Ҫ����Ȩ�ޣ����޸�Ϊ��ӦȨ��ֵ
        virtual DSPluginAPI::PluginRight GetPluginRightID() const { return DSPluginAPI::rightDefault; }

    public:
        // �󶨲����Դ���ɰ󶨶��[�̰߳�ȫͬ���ӿ�]
        virtual bool Bind(IAbstractResourceManager* pManager) = 0;
        // �������Դ�����ͷŸɾ�[�̰߳�ȫͬ���ӿ�]
        virtual bool Release(IAbstractResourceManager* pManager) = 0;

    public:
        // �߼���[�̰߳�ȫͬ���ӿ�]
        virtual bool InitLogical() = 0;
        // [�̰߳�ȫͬ���ӿ�]
        virtual void UninitLogical() = 0;

    public:
        // UI��[�̰߳�ȫͬ���ӿ�]
        virtual void InitUI() = 0;
        // ���ڴ˴�����IAbstractUI[�̰߳�ȫͬ���ӿ�]
        virtual void UninitUI() = 0;

    public:
        // ��ȡ����Ľ��棬����������ݵ�Ψһ�ӿڣ�Ϊ�ղ������ʧ��
        // IAbstractUI�����ڿ���UninitUI�ӿڴ���������
        virtual IAbstractUI* GetAbstractUI() const = 0;
    };

    class IAbstractWidget;

    /** @class IAbstractUI
     *  @brief ����Ľ���
     *
     *  ְ��
     *  
     */
    class IAbstractUI
    {
    public:
        virtual ~IAbstractUI() {}

    public:
        // ��������Ĵ��ڣ��������ֻ��ʾ�˴�����Ϣ��Ϊ�ղ������ʧ��
        virtual IAbstractWidget* CreateAbstractWidget() const = 0;

        // ͨ������ID��ȡ����Ĵ���
        virtual IAbstractWidget* GetAbstractWidget(const std::string& strWidgetID) const = 0; 
    };

    /** @class IAbstractWidget
     *  @brief ����Ĵ���
     *  
     */
    class IAbstractWidget
    {
    public:
        virtual ~IAbstractWidget() {}

    public:
        // ��ȡ�������ͱ��
        virtual std::string GetWidgetID() const = 0;

        // ��ȡ��ʾ���ڣ������ͷ�
        virtual QWidget* GetWidget() const = 0;

    public:
        // ��ȡ�������
        virtual QString GetPanelName() const = 0;
        // ��ȡ���ͼ��
        virtual QIcon GetPanelIcon() const = 0;
        // ��ȡ�����ϸ����
        virtual QString GetPanelDetails() const = 0;

    public:
        // ��ȡtabҳ����
        virtual QString GetTabName() const = 0;
        // ��ȡtabҳͼ��
        virtual QIcon GetTabIcon() const = 0;

    public:
        // ��ȡ�˵�����
        virtual QString GetMenuName() const = 0;
        // ��ȡ�˵�ͼ��
        virtual QIcon GetMenuIcon() const = 0;

    public:
        // ��ȡֵ
        virtual QVariant GetValue(int iType) const = 0;

    public:
        // close = 1 tab�л� = 2
        virtual bool OnMsg(int iType, const QVariant& vtParam1, const QVariant& vtParam2) = 0;
    };
}

// Q_DECLARE_INTERFACE(ClassName, Identifier)
// IdentifierΨһ������1.0Ϊ����汾����
Q_DECLARE_INTERFACE(DSPluginAPI::IClientUIPluginAPI, "com.DSPluginAPI.IClientUIPluginAPI(1.0)");

#endif // __DSPLUGINAPI_ICLIENTUIPLUGINAPI_H__
