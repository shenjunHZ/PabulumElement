#ifndef __DSPLUGINAPI_TYPEDEF_H__
#define __DSPLUGINAPI_TYPEDEF_H__

#include <string>

namespace DSPluginAPI
{
    // ȫ�ֶ���ID
    typedef unsigned int ID;
    const ID idInValid = static_cast<unsigned int>(-1); // ��ЧID

    // ȫ�ֶ���Code
    typedef std::string Code;
    const Code codeInValid = ""; // ��Ч���

    // ȫ�ֶ������
    typedef unsigned int No;
    const No noInValid = static_cast<unsigned int>(-1); // ��Ч���

    // ��Ч��ʱ��
    const time_t tmInValid = -1;
}

#endif
