#ifndef DSS_COMPONENT_AX_API_AX_STL_H_INCLUDED
#define DSS_COMPONENT_AX_API_AX_STL_H_INCLUDED

#if defined(_WIN32) || defined(WINCE) || defined (_WIN64)
#include <hash_map>
#else
#include <ext/hash_map>
#endif

#if defined(_WIN32) || defined(WINCE) || defined (_WIN64)
    template<class _Key,class _Tp>
    class ax_hash_map:public stdext::hash_map<_Key,_Tp>
    {
    };
#else
    template<class _Key,class _Tp>
    class ax_hash_map:public __gnu_cxx::hash_map<_Key,_Tp>
    {
    };
#endif



#endif//DSS_COMPONENT_AX_API_AX_STL_H_INCLUDED

