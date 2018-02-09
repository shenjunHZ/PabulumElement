
/*
* Copyright (c) 
* All rights reserved.
*
* �ļ����ƣ�AX_RW_Mutex.inl
* �ļ���ʶ��
* ժ����Ҫ��AX��д�� .inl�ļ�������win32&linux
*

* ��ǰ�汾��1.0
* ԭ���ߡ���
* ������ڣ�
* �޶���¼������
*/

inline int 
AX_RW_Mutex::remove (void)
{
	// AX_TRACE ("AX_RW_Mutex::remove");
	int result = 0;
	if (this->removed_ == 0)
	{
		this->removed_ = 1;
		result = AX_OS::rwlock_destroy (&this->lock_);
	}
	return result;
}

inline int 
AX_RW_Mutex::acquire_read (void)
{
	// AX_TRACE ("AX_RW_Mutex::acquire_read");
	return AX_OS::rw_rdlock (&this->lock_);
}


inline int 
AX_RW_Mutex::acquire_write (void)
{
	// AX_TRACE ("AX_RW_Mutex::acquire_write");
	return AX_OS::rw_wrlock (&this->lock_);
}


inline int 
AX_RW_Mutex::tryacquire_read (void)
{
	// AX_TRACE ("AX_RW_Mutex::tryacquire_read");
	return AX_OS::rw_tryrdlock (&this->lock_);
}


inline int 
AX_RW_Mutex::tryacquire_write (void)
{
	// AX_TRACE ("AX_RW_Mutex::tryacquire_write");
	return AX_OS::rw_trywrlock (&this->lock_);
}


inline int 
AX_RW_Mutex::acquire (void)
{
	// AX_TRACE ("AX_RW_Mutex::acquire");
	return AX_OS::rw_wrlock (&this->lock_);
}


inline int 
AX_RW_Mutex::tryacquire (void)
{
	// AX_TRACE ("AX_RW_Mutex::tryacquire");
	return this->tryacquire_write ();
}


inline int 
AX_RW_Mutex::release (void)
{
	// AX_TRACE ("AX_RW_Mutex::release");
	return AX_OS::rw_unlock (&this->lock_);
}


