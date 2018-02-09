/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
* 2011-09
*
* DPool.h : ��ͨ����أ����ü��������
*/

#ifndef INCLUDED_LIBDSL_DPOOL_H
#define INCLUDED_LIBDSL_DPOOL_H

#include <libdsl/DMutex.h>
#include <libdsl/DRefObj.h>

#include <deque>

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

#define DSL_OBJECT_POOL_MAX_NUM		128 // �����ж������

// <1> ��ͨ����أ���Ҫ�ⲿ��ʽ�������ͻس���
template< class T >
class DPool
{
public:
	DPool( unsigned int maxnum = DSL_OBJECT_POOL_MAX_NUM ) : m_nObjectMaxCount( maxnum ) { }

	~DPool()
	{
		Decrease( 0 );
	}

	inline T * GetObject()
	{
		T* pT;
		DMutexGuard guard(&m_csLock);

		if( m_dequeObjects.size() == 0 ) {
			pT = new T();
		}
		else {
			pT = m_dequeObjects.back();
			m_dequeObjects.pop_back();
		}

		return pT;
	}

	inline void Recycle( T * pT )
	{
		// assert(pT);
		if( pT == NULL )
			return;

		DMutexGuard guard(&m_csLock);
		if( m_dequeObjects.size() >= m_nObjectMaxCount ) {
			delete pT;
		}
		else {
			m_dequeObjects.push_back(pT);
		}
	}

	inline int GetObjectNum() const { return (int)m_dequeObjects.size(); } 

	inline int Decrease( unsigned int allow_num ) 
	{
		DMutexGuard guard(&m_csLock);
		while( m_dequeObjects.size() > allow_num ) {
			delete m_dequeObjects.back();
			m_dequeObjects.pop_back();
		}
		return (int)m_dequeObjects.size();
	}

private:
	DMutex m_csLock;
	unsigned int m_nObjectMaxCount;
	std::deque< T * > m_dequeObjects;
};


// <2> ���ü�������أ�����T��Ҫ�̳�DRefPoolObj
// ���ü����صĶ���һ���ɳ���������������Ҳ���Բ�����һ��ʹ�ã�������������ʱ�˻�����ͨ��DRefObj��
// ʹ�÷��� class MyObj : public DRefPoolObj<MyObj> { ... }; 
//          DRefPool<MyObj> m_pool; DRefPointer< MyObj > pObj = m_pool.GetObject();
// ��DRefPointer����ʱ�������DRefPoolObj��release���������ջὫ���󷵻ص�pool�С�

template <class T> class DRefPool;

template< class T >
class DRefPoolObj : virtual public DRefObj
{
public:
	DRefPoolObj() { m_pPool = NULL; }

protected:
	virtual ~DRefPoolObj() {}

protected:
	inline virtual void destroy() 
	{ 
		// TODO : ��ǰpool�������ڱ�����ڶ����Ժ���Կ���pool���ͷţ����Խ���poolָ����NULL
		if( m_pPool != NULL ) {
			m_pPool->recycle( (T *)this );  // T �� DRefPool< T > �ǵ����࣬���������һ���� T
		}
		else {
			delete this;
		}
		return;
	}

private:
	friend class DRefPool< T >;
	inline void setpool( DRefPool< T > * pPool ) { m_pPool = pPool; return; } 

private:
	DRefPool< T > * m_pPool;
};

template< class T >
class DRefPool
{
public:
	DRefPool( unsigned int nObjectMaxCount = DSL_OBJECT_POOL_MAX_NUM ) : m_nObjectMaxCount( nObjectMaxCount ) { }
	~DRefPool(){ Decrease( 0 ); }

public:
	// ��DRefObj���ƣ����صĶ������ü���Ϊ0��Ӧ�ø�ֵ��һ�� DRefPointer ����
	inline DRef<T> GetObject()
	{
		T * pT = NULL;
		DMutexGuard guard(&m_csLock);
		if (m_dequeObjects.size() == 0) {
			pT = new T();
			pT->setpool( this );
		}
		else {
			pT = m_dequeObjects.back();
			m_dequeObjects.pop_back();
		}
		return DRef<T>( pT );
	}

	inline int GetObjectNum() const { return (int)m_dequeObjects.size(); } 

	inline int Decrease( unsigned int allow_num ) 
	{
		DMutexGuard guard(&m_csLock);
		while( m_dequeObjects.size() > allow_num ) {
			T * pT = m_dequeObjects.back();
			m_dequeObjects.pop_back();
			// ���ü����Ѿ�Ϊ0��setpool(NULL)��destroy�൱��delete��
			pT->setpool( NULL );
			pT->destroy();
		}
		return (int)m_dequeObjects.size();
	}

private:
	friend class DRefPoolObj< T >;
	inline void recycle( T * pT )
	{
		DMutexGuard guard(&m_csLock);
		if(m_dequeObjects.size() >= m_nObjectMaxCount) {
			// ���ü����Ѿ�Ϊ0��setpool(NULL)��destroy�൱��delete��
			pT->setpool( NULL );
			pT->destroy();
		}
		else {
			m_dequeObjects.push_back( pT );
		}
	}

private:
	DMutex m_csLock;
	unsigned int m_nObjectMaxCount;
	std::deque< T * > m_dequeObjects;  // Pool �����������ü�������0
	// TODO : ���Ӽ�¼�ѷ�������set����pool���ڶ����ͷ�ʱ���������poolָ���ÿ�
};


// <3> ��ǿ��Ӧ�ü�������أ�����T������Ҫ��DRefObj�м̳У����������Pool�����ɣ�����������ⲿ�����Ķ���

template< class T >
class DRefPoolEx
{
public:
	DRefPoolEx( unsigned int nObjectMaxCount = DSL_OBJECT_POOL_MAX_NUM ) : m_nObjectMaxCount( nObjectMaxCount ) { }
	~DRefPoolEx(){ Decrease( 0 ); }

public:
	// ��DRefObj���ƣ����صĶ������ü���Ϊ0��Ӧ�ø�ֵ��һ�� DRefPointer ����
	inline DRef<T> GetObject()
	{
		SubT * pT = NULL;
		DMutexGuard guard(&m_csLock);
		if (m_dequeObjects.size() == 0) {
			pT = new SubT();
			pT->setpool( this );
		}
		else {
			pT = m_dequeObjects.back();
			m_dequeObjects.pop_back();
		}
		return DRef<T>( (T *)pT );
	}

	inline int GetObjectNum() const { return (int)m_dequeObjects.size(); } 

	inline int Decrease( unsigned int allow_num ) 
	{
		DMutexGuard guard(&m_csLock);
		while( m_dequeObjects.size() > allow_num ) {
			SubT * pT = m_dequeObjects.back();
			m_dequeObjects.pop_back();
			// ���ü����Ѿ�Ϊ0��setpool(NULL)��destroy�൱��delete��
			pT->setpool( NULL );
			pT->destroy();
		}
		return (int)m_dequeObjects.size();
	}

private:
	class SubT : public T
	{
	public:
		inline virtual void destroy() 
		{ 
			// TODO : ��ǰpool�������ڱ�����ڶ����Ժ���Կ���pool���ͷţ����Խ���poolָ����NULL
			if( m_pPool != NULL ) {
				m_pPool->recycle( this );
			}
			else {
				delete this;
			}
			return;
		}
	private:
		friend class DRefPoolEx< T >;
		inline void setpool( DRefPoolEx< T > * pPool ) { m_pPool = pPool; return; } 

	private:
		DRefPoolEx< T > * m_pPool;
	};

private:
	friend class SubT;
	inline void recycle( SubT * pT )
	{
		DMutexGuard guard(&m_csLock);
		if(m_dequeObjects.size() >= m_nObjectMaxCount) {
			// ���ü����Ѿ�Ϊ0��setpool(NULL)��destroy�൱��delete��
			pT->setpool( NULL );
			pT->destroy();
		}
		else {
			m_dequeObjects.push_back( pT );
		}
	}

private:
	DMutex m_csLock;
	unsigned int m_nObjectMaxCount;
	std::deque< SubT * > m_dequeObjects;  // Pool �����������ü�������0
	// TODO : ���Ӽ�¼�ѷ�������set����pool���ڶ����ͷ�ʱ���������poolָ���ÿ�
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBDSL_DPOOL_H
