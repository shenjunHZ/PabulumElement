#ifndef AX_REFPTR_H_INCLUDED
#define AX_REFPTR_H_INCLUDED

//#include "platform.h"
#include <stddef.h> // NULL

template<class T, class R>
class AX_RefPtr;

template<class T,class R>
bool operator ==(  const T* t,const AX_RefPtr<T,R>& ptr);

template<class T,class R>
bool operator ==( const AX_RefPtr<T,R>& ptr, const T* t);

template<class T,class R>
bool operator ==( const AX_RefPtr<T,R>& ptr1, const AX_RefPtr<T,R>& ptr2);

template<class T,class R>
bool operator !=(  const T* t,const AX_RefPtr<T,R>& ptr);

template<class T,class R>
bool operator !=( const AX_RefPtr<T,R>& ptr, const T* t);

template<class T,class R>
bool operator !=( const AX_RefPtr<T,R>& ptr1, const AX_RefPtr<T,R>& ptr2);

// 两个参数，主要是用于T是菱形继承时，指定某个顶层的AX_IAddRefAble，但实际上，这个时候应该使用虚继承更合理

template<class T,class R=T>
class AX_RefPtr
{
	typedef AX_RefPtr<T,R> TYPE;
public:
	AX_RefPtr(T* t=NULL)
	{
		_p=t;
		if(NULL!=_p)
			_p->R::addRef();
	}
	~AX_RefPtr()
	{
		if(NULL!=_p)
		{
			_p->R::release();
			_p=NULL;
		}
	}
	AX_RefPtr(const TYPE& ptr)
	{
		_p=ptr._p;
		if(NULL!=_p)
			_p->R::addRef();
	}
public:
	AX_RefPtr& operator=(const TYPE& ptr)
	{
		if(&ptr==this)
			return *this;
		if(ptr._p==_p)
			return *this;

		if(NULL!=_p)
			_p->R::release();
		_p=ptr._p;
		if(NULL!=_p)
			_p->R::addRef();
		return *this;
	}
	AX_RefPtr& operator=(T* t)
	{
		if(_p==t)
			return *this;

		if(NULL!=_p)
			_p->R::release();
		_p=t;
		if(NULL!=_p)
			_p->R::addRef();
		return *this;
	}
public:
	T* operator->()
	{
		return _p;
	}
	const T* operator->()const
	{
		return _p;
	}
	const bool isNull() const
	{
		return NULL==_p;
	}
protected:
	T*	_p;
	friend bool operator == <> ( const T* t,const AX_RefPtr<T,R>& ptr);
	friend bool operator == <> ( const AX_RefPtr<T,R>& ptr, const T* t);
	friend bool operator == <> ( const AX_RefPtr<T,R>& ptr1, const AX_RefPtr<T,R>& ptr2);
	friend bool operator != <> ( const T* t,const AX_RefPtr<T,R>& ptr);
	friend bool operator != <> ( const AX_RefPtr<T,R>& ptr, const T* t);
	friend bool operator != <> ( const AX_RefPtr<T,R>& ptr1, const AX_RefPtr<T,R>& ptr2);
};

template<class T,class R>
bool operator ==(  const T* t,const AX_RefPtr<T,R>& ptr)
{
	return ptr._p==t;
}

template<class T,class R>
bool operator ==( const AX_RefPtr<T,R>& ptr, const T* t)
{
	return ptr._p==t;
}

template<class T,class R>
bool operator ==( const AX_RefPtr<T,R>& ptr1, const AX_RefPtr<T,R>& ptr2)
{
	return ptr1._p==ptr2._p;
}

template<class T,class R>
bool operator !=(  const T* t,const AX_RefPtr<T,R>& ptr)
{
	return ptr._p!=t;
}

template<class T,class R>
bool operator !=( const AX_RefPtr<T,R>& ptr, const T* t)
{
	return ptr._p!=t;
}

template<class T,class R>
bool operator !=( const AX_RefPtr<T,R>& ptr1, const AX_RefPtr<T,R>& ptr2)
{
	return ptr1._p!=ptr2._p;
}

#endif  // AX_REFPTR_H_INCLUDED
