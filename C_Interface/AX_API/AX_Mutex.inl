
/*
* Copyright (c) 
* All rights reserved.
*
* �ļ����ƣ�AX_Mutex.inl
* �ļ���ʶ��
* ժ����Ҫ��AX������ .inl�ļ�
*

* ��ǰ�汾��1.0
* ԭ���ߡ���
* ������ڣ�
* �޶���¼������
*/

inline int 
AX_Mutex::remove (void)
{
	int result = 0;

#ifdef AX_HAS_PROCESS_MUTEX
	if (this->process_lock_)
	{
		//process mutex, to be implemented
	}
	else
	{
#endif
		if (this->removed_ == 0)
		{
			this->removed_ = 1;
			result = AX_OS::thread_mutex_destroy (&this->lock_);
		}
#ifdef AX_HAS_PROCESS_MUTEX
	}
#endif

	return result;
}

inline int 
AX_Mutex::acquire (void)
{
#ifdef AX_HAS_PROCESS_MUTEX
	if (this->process_lock_)
		return -1;
#endif
	return AX_OS::thread_mutex_lock (&this->lock_);
}

#if 0
#ifndef MAC
inline int 
AX_Mutex::acquire (timeval &tv)
{
#ifdef AX_HAS_PROCESS_MUTEX
	if (this->process_lock_)
		return -1;
#endif
	return AX_OS::thread_mutex_lock (&this->lock_, tv);
}

inline int 
AX_Mutex::acquire (timeval *tv)
{
#ifdef AX_HAS_PROCESS_MUTEX
	if (this->process_lock_)
		return -1;
#endif
	return AX_OS::thread_mutex_lock (&this->lock_, tv);
}
#endif // MAC
#endif // if 0

inline int 
AX_Mutex::tryacquire (void)
{
#ifdef AX_HAS_PROCESS_MUTEX
	if (this->process_lock_)
		return -1;
#endif
	return AX_OS::thread_mutex_trylock (&this->lock_);
}

inline int 
AX_Mutex::release (void)
{
#ifdef AX_HAS_PROCESS_MUTEX
	if (this->process_lock_)
		return -1;
#endif
	return AX_OS::thread_mutex_unlock (&this->lock_);
}

#if 0

inline int 
AX_Mutex::acquire_read (void)
{
#ifdef AX_HAS_PROCESS_MUTEX
	if (this->process_lock_)
		return -1;
#endif
	return AX_OS::thread_mutex_lock (&this->lock_);
}

inline int 
AX_Mutex::acquire_write (void)
{
#ifdef AX_HAS_PROCESS_MUTEX
	if (this->process_lock_)
		return -1;
#endif
	return AX_OS::thread_mutex_lock (&this->lock_);
}

inline int 
AX_Mutex::tryacquire_read (void)
{
#ifdef AX_HAS_PROCESS_MUTEX
	if (this->process_lock_)
		return -1;
#endif
	return AX_OS::thread_mutex_trylock (&this->lock_);
}

inline int 
AX_Mutex::tryacquire_write (void)
{
#ifdef AX_HAS_PROCESS_MUTEX
	if (this->process_lock_)
		return -1;
#endif
	return AX_OS::thread_mutex_trylock (&this->lock_);
}

#endif // 0
