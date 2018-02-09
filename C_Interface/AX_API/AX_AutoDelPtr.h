#ifndef AX_AUTODELPTR_H_INCLUDED
#define AX_AUTODELPTR_H_INCLUDED

// #include "platform.h" // define NULL
#include <stddef.h> // NULL

template<class T>
class AX_AutoDelPtr;

template<class T>
bool operator ==(  const T* t,const AX_AutoDelPtr<T>& ptr);

template<class T>
bool operator ==( const AX_AutoDelPtr<T>& ptr, const T* t);

template<class T>
bool operator !=(  const T* t,const AX_AutoDelPtr<T>& ptr);

template<class T>
bool operator !=( const AX_AutoDelPtr<T>& ptr, const T* t);

template<class T>
class AX_AutoDelPtr
{
	typedef AX_AutoDelPtr<T> TYPE;
public:
	AX_AutoDelPtr(T* t=NULL)
	{
		_p=t;
	}
	~AX_AutoDelPtr()
	{
		if(NULL!=_p)
		{
			delete _p;
			_p=NULL;
		}
	}
private:
	AX_AutoDelPtr(const TYPE& ptr);
	AX_AutoDelPtr& operator=(const TYPE& ptr);
	AX_AutoDelPtr& operator=(T* t);
public:
	T* operator->()
	{
		return _p;
	}
	const T* operator->()const
	{
		return _p;
	}
	T& operator*()
	{
		return *_p;
	}
	const T& operator*()const
	{
		return *_p;
	}
	const bool isNull() const
	{
		return NULL==_p;
	}
protected:
	T*	_p;
	// template<class C> friend bool operator ==( const C* t,const AX_AutoDelPtr<C>& ptr); // 这种写法友元范围太大
	friend bool operator == <> ( const T* t, const AX_AutoDelPtr<T>& ptr);
	friend bool operator == <> ( const AX_AutoDelPtr<T>& ptr, const T* t);
	friend bool operator != <> ( const T* t,const AX_AutoDelPtr<T>& ptr);
	friend bool operator != <> ( const AX_AutoDelPtr<T>& ptr, const T* t);
};

template<class T>
bool operator ==(  const T* t,const AX_AutoDelPtr<T>& ptr)
{
	// AX_AutoDelPtr< T * > p;
	// T ** pp = p._p; // 这个不应该允许，否则友元范围太大
	return ptr._p==t;
}
template<class T>
bool operator ==( const AX_AutoDelPtr<T>& ptr, const T* t)
{
	return ptr._p==t;
}

#if 0
// 这种情况不应该出现，否则会被删除两次
template<class T>
bool operator ==( const AX_AutoDelPtr<T>& ptr1, const AX_AutoDelPtr<T>& ptr2)
{
	return ptr1._p==ptr2._p;
}
#endif

template<class T>
bool operator !=(  const T* t,const AX_AutoDelPtr<T>& ptr)
{
	return ptr._p!=t;
}

template<class T>
bool operator !=( const AX_AutoDelPtr<T>& ptr, const T* t)
{
	return ptr._p!=t;
}

#if 0
template<class T>
bool operator !=( const AX_AutoDelPtr<T>& ptr1, const AX_AutoDelPtr<T>& ptr2)
{
	return ptr1._p!=ptr2._p;
}
#endif

#endif  //AX_AUTODELPTR_H_INCLUDED

