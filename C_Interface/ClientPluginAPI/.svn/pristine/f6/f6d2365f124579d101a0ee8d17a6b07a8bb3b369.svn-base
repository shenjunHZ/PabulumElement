#ifndef __DSPLUGINAPI_IOBSERVER_H__
#define __DSPLUGINAPI_IOBSERVER_H__

#ifndef NDEBUG
#include <assert.h>
#endif

namespace DSPluginAPI
{
#ifdef _DEBUG
    class IObserver
    {
    public:
        IObserver()
            : m_iCount(0)
        {}

        virtual ~IObserver()
        {
            assert(m_iCount == 0);
        }

        void IncreaseCount()
        {
            ++m_iCount;
        }

        void DecreaseCount()
        {
            --m_iCount;
        }

    private:
        int m_iCount;
    };
#else 
    class IObserver
    {
    };
#endif
}

#endif
