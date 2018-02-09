#ifndef DH_DSS_ENVFS_TTHREAD_H_INCLUDED
#define DH_DSS_ENVFS_TTHREAD_H_INCLUDED

#if defined(_WIN32) || defined (_WIN64)
#include <process.h>
#else
#include <pthread.h>
#endif

// T通常是这个模板的子类，

template<class T>
class tthread
{
public:
	tthread()
	{
		_threadId=0;
		_canRun=true;
		_sink=NULL;
		_callback=NULL;
		_threadRunning=false;
	}
	virtual ~tthread(){}

public:
	typedef void (T::*CallBackFunc)();
    bool start(T* sink,CallBackFunc callback,int& errCode)
    {
    	errCode=0;
    	if(_threadRunning)
    	{
    		errCode=-1;
    		return false;
    	}
        _sink=sink;
        _callback=callback;
#if defined(_WIN32) || defined (_WIN64)
        _threadId=_beginthread(tthread<T>::_thread,0,this);
        if(0<_threadId)
        	_threadRunning=true;
        else
        	errCode=-2;
        return _threadRunning;
#else
        pthread_attr_t attr;
        pthread_attr_init( &attr );
        pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );
        int ret = pthread_create( &_threadId, &attr, tthread<T>::_thread, this );
        pthread_attr_destroy( &attr );
        if(0==ret)
        	_threadRunning=true;
        else
        	errCode=-3;
        return _threadRunning;
#endif
    }

    bool stop()
    {
        _canRun=false;
        while(_threadRunning)
        {
#if defined(_WIN32) || defined (_WIN64)
			::Sleep( 20 );
#else
			::usleep( 20 * 1000 );
#endif
        }
    	return true;
    }

	bool isRun()
	{
		return _threadRunning;
	}

	// 提供的CallBackFunc中应该调用这个函数来判断是否需要结束运行
	bool canRun()
	{
		return _canRun;
	}

protected:
    void _thread()
    {
        _threadRunning=true;
        if(_sink && _callback)
            (_sink->*_callback)();
        _threadRunning=false;
    }
#if defined(_WIN32) || defined (_WIN64)
    static void _thread(void *arg)
    {
        tthread<T> * pthis=(tthread<T>*)arg;
        pthis->_thread();
    }
#else
    static void * _thread(void *arg)
    {
        tthread<T> * pthis=(tthread<T>*)arg;
        pthis->_thread();
        return NULL;
    }
#endif

protected:
    bool            _threadRunning;
    T*              _sink;
    CallBackFunc    _callback;
    bool            _canRun;
    // CallBackFunc    _callBack;
#if defined(_WIN32) || defined (_WIN64)
    uintptr_t       _threadId;
#else
    pthread_t       _threadId;
#endif
};

#endif //DH_DSS_ENVFS_TTHREAD_H_INCLUDED
