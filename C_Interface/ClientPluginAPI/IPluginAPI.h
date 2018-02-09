#ifndef __DSPLUGINAPI_IPLUGINAPI_H__
#define __DSPLUGINAPI_IPLUGINAPI_H__

#include <string>

namespace DSPluginAPI
{
    struct IPluginAPI
    {
    public:
        virtual ~IPluginAPI() {}

    public:
        // ���Ψһ��ʶ��
        virtual std::string GetPluginID() const = 0;
    };
}

#endif // __DSPLUGINAPI_IPLUGINAPI_H__
