
/*
* Copyright (c) 
* All rights reserved.
*
* �ļ����ƣ�AX_Mutex.h
* �ļ���ʶ��
* ժ����Ҫ��AX������ .h�ļ�
*

* ��ǰ�汾��1.0
* ԭ���ߡ���
* ������ڣ�
* �޶���¼������
*/

#ifndef AX_MUTEX_INCLUDE
#define AX_MUTEX_INCLUDE

#include "AX_API/AX_OS.h"

//#define AX_HAS_PROCESS_MUTEX

class DOAX_DEPRECATED AX_Mutex
{
public:
	/// Initialize the mutex.
	AX_Mutex (int type = AX_USYNC_THREAD);

	/// Implicitly destroy the mutex.
	~AX_Mutex (void);

	/// Explicitly destroy the mutex.
	/**
	* @note Only one thread should call this method since it doesn't
	*        protect against race conditions.
	*/
	int remove (void);

	/// Acquire lock ownership (wait on queue if necessary).
	int acquire (void);

#if 0
	// win32ƽ̨��֧�֣������ã���Ӧ��ʹ�ã�����ע�͵�
	/// Block the thread until the mutex is acquired or @a tv times out,
	/// in which case -1 is returned and @c errno == @c ETIME.
	/**
	* @note @a tv is assumed  to be in "absolute" rather than
	* "     relative" time.  The value of @a tv is updated upon return
	*       to show the actual(absolute) acquisition time.
	*/
#ifndef MAC
	int acquire (timeval &tv);
#endif

	/// Block the thread until the mutex is acquired or @a *tv times
	/// out, in which case -1 is returned and @c errno == @c ETIME.
	/**
	* If @a tv == 0 then call @c acquire() directly.  Otherwise, block
	* the thread until the mutex is acquired or @a tv times out, in
	* which case -1 is returned and @c errno == @c ETIME.
	*
	* @note @a *tv is assumed to be in "absolute" rather than
	*       "relative" time.  The value of @a *tv is updated upon
	*       return to show the actual (absolute) acquisition time.
	*/
#ifndef MAC
	int acquire (timeval *tv);
#endif

#endif // if 0

	/// Conditionally acquire lock (i.e., don't wait on queue).
	/**
	* @return -1 on failure.  If we "failed" because someone
	*         else already had the lock, @c errno is set to @c EBUSY.
	*/
	int tryacquire (void);

	/// Release lock and unblock a thread at head of queue.
	int release (void);


	/// ���½ӿڽ�Ϊ�����Կ���
//	int acquire_read (void);
//	int acquire_write (void);
//	int tryacquire_read (void);
//	int tryacquire_write (void);
//	int tryacquire_write_upgrade (void);

protected:
	/// This lock resides in shared memory.
//	AX_Mutex_t *process_lock_;

	/// Mutex type supported by the OS.
	AX_Mutex_t lock_;

	/// Keeps track of whether @c remove has been called yet to avoid
	/// multiple @c remove calls, e.g., explicitly and implicitly in the
	/// destructor.  This flag isn't protected by a lock, so make sure
	/// that you don't have multiple threads simultaneously calling
	/// @c remove on the same object, which is a bad idea anyway.
	int removed_;

private:
	// Prevent assignment and initialization.
	void operator= (const AX_Mutex &);
	AX_Mutex (const AX_Mutex &);

};

#include "AX_Mutex.inl"

#endif

