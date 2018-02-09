/* Copyright (c) 2011, �㽭�󻪼����ɷ����޹�˾, All rights reserved.
 * 2011-09
 *
 * DRefObj.h : ���ü�������
 */

#ifndef INCLUDED_LIBSDL_DREFOBJ_H
#define INCLUDED_LIBSDL_DREFOBJ_H

#include <libdsl/DAtomic.h>

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

/* DRefObj�����ü���������࣬��ʼ���� m_dwRefCount ����ֵΪ 0 ����������
 * ����̳�ʱ��Ӧ��ʹ����̳У��ر��ǽӿ��࣬�������Դ������μ̳�
 * ���ഴ��ʱ����ʹ��new�����븳ֵ�����ü���ָ��DRef������ : DRef<DRefObjXXX> refXXX = new DRefObjXXX;
 * ����Ҫ����ֻ��Ҫ����DRef�������߸���ֵ����������ʽdelete�����Ҫ�л���֪ͨ����ʹ�����ͷţ�
 */

class DStr;
template< class T > class DRef;

class LIBDSL_API DRefObj
{
public:
	// �����ԣ��������ü�����ֵ���������Բο�ʹ�ã�����ҵ���߼���Ӧ��ʹ���������
	inline int GetRefCount() const { return m_ref.Read(); }
	// �����ԣ��ṩ���ü�������Ļ�����Ϣ��*����*��strβ������Ҫ�����Ժ�ϵͳ��άʹ��
	virtual void GetObjInfo( DStr * /* out_info */ ) const {}

protected:
	DRefObj() {}
	/* �����ڼ���ԭDRefInterface���� */ DSL_DEPRECATED DRefObj( DRefObj * /* obj */ ) {}
	virtual ~DRefObj() {}   // ע�⣺�������������ҲӦ����protected��������
	virtual void destroy(); // ���ü�����Ϊ0ʱ���ã�ȱʡʵ���ǣ�{ delete this; return; }��һ�㲻��Ҫ���أ���ǰֻ����pool

private:
	// �ⲿ��Ӧ��ֱ�ӵ���������������Ӧ��ͨ��DRef�����ʣ�����Ҳ��Ӧ�õ���
	template< class T > friend class DRef;
	inline int addref() { return m_ref.Inc(); }
	inline int release() { int r = m_ref.Dec(); if( r == 0 ) destroy(); return r; }

private:
	DAtomic m_ref;
};

// ָ�� DRefObj ����������ü���ָ�룬�Զ����Ӻͼ������ü���
template< class T >
class DRef
{
public:
	~DRef() { if( m_pObj ) { m_pObj->release(); m_pObj = NULL; } }

	DRef( T * p = NULL ) : m_pObj( p ) { if( m_pObj ) m_pObj->addref(); }
	inline DRef< T > & operator = ( T * p )
	{
		if( m_pObj == p )
			return *this;

		if( m_pObj ) m_pObj->release();
		m_pObj = p;
		if( m_pObj ) m_pObj->addref();
		return *this;
	}

	DRef( const DRef< T > & rp ) : m_pObj( rp.m_pObj ) { if( m_pObj ) m_pObj->addref(); }
	inline DRef< T > & operator = ( const DRef< T > & rp )
	{
		// if( this == &rp )
		if( m_pObj == rp.m_pObj )
			return *this;

		if( m_pObj != NULL ) m_pObj->release();
		m_pObj = rp.m_pObj;
		if( m_pObj ) m_pObj->addref();
		return *this;
	}

	// ������ָͨ�븳ֵ����������ָ�루T2 Ӧ���� T �����ࣩ��������ʱ�����Զ�ת�����ͣ�
	// ���� T2 * rp2; DRef<T> rp1 = rp2; ���� func( rp2 ); ��ԭ�ͣ�void func( const DRef<T> & rp );��
	template< class T2 >
	DRef( T2 * rp ) : m_pObj( rp ) { if( m_pObj ) m_pObj->addref(); }
	template< class T2 >
	inline DRef< T > & operator = ( T2 * rp )
	{
		T * tmp = rp; // ���T2����T�����࣬�����ʧ��
		if( m_pObj == tmp )
			return *this;

		if( m_pObj ) m_pObj->release();
		m_pObj = tmp;
		if( m_pObj ) m_pObj->addref();
		return *this;
	}

	// ��������ָ�븳ֵ����������ָ�루T2 Ӧ���� T �����ࣩ��������ʱ�����Զ�ת�����ͣ�
	// ���� DRef<T2> rp2; DRef<T> rp1 = rp2; ���� func( rp2 ); ��ԭ�ͣ�void func( const DRef<T> & rp );��
	template< class T2 >
	DRef( const DRef< T2 > & rp ) : m_pObj( rp.GetPointer() ) { if( m_pObj ) m_pObj->addref(); }
	template< class T2 >
	inline DRef< T > & operator = ( const DRef< T2 > & rp )
	{
		T * tmp = rp.GetPointer(); // ���T2����T�����࣬�����ʧ��
		if( m_pObj == tmp )
			return *this;

		if( m_pObj ) m_pObj->release();
		m_pObj = tmp;
		if( m_pObj ) m_pObj->addref();
		return *this;
	}

	// ��ʽ��ǿ������ת�����������������ָ��ָ���������ʱ����ת���������������ָ�룬Ҫ��ʽ���ô˺���
	// ���� T2��T�����࣬DRef<T2> t2; DRef<T> t1 = t2; DRef<T2> t22 = t1.Cast<T2>();
	template< class T2 >
	inline DRef<T2> Cast() { return DRef<T2>( static_cast<T2 *>( m_pObj ) ); }

	inline T * operator -> () const { return m_pObj; }
	// inline operator T * () const { return m_pObj; }

	inline T * GetPointer() const { return m_pObj; }

	inline bool operator == ( const DRef< T > & rp ) const { return m_pObj == rp.m_pObj; }
	inline bool operator == ( const T * p ) const { return m_pObj == p; }
	inline bool operator == ( int p ) const { return m_pObj == (T *)(intptr_t)p; }  // for NULL
	inline bool operator == ( long p ) const { return m_pObj == (T *)(intptr_t)p; }  // for NULL
	inline bool operator != ( const DRef< T > & rp ) const { return m_pObj != rp.m_pObj; }
	inline bool operator != ( const T * p ) const { return m_pObj != p; }
	inline bool operator != ( int p ) const { return m_pObj != (T *)(intptr_t)p; }  // for NULL
	inline bool operator != ( long p ) const { return m_pObj != (T *)(intptr_t)p; }  // for NULL
	inline operator bool () const { return m_pObj != NULL; }
	inline bool operator ! () const { return m_pObj == NULL; }
	inline bool operator < ( const DRef< T > & rp ) const { return m_pObj < rp.m_pObj; }

protected:
	T * m_pObj;
};	

// ��1.0��1.1��ֲ˵����
// ��1��ԭ���̳�DRefObj�ģ�һ�������Ӧ����Ϊ��̳У����磺class XXXX : virtual public DRefObj
// ��2��ԭ�����ü���ָ��DRefPointer����Ҫ��ΪDRef
//      ��������һ�����壺 #define DRefPointer DRef 
// ��3��ԭ���̳�DRefInterface�ģ���Ҫ��Ϊ��̳� DRefObj��
//      ���ԭ��ͬʱ�̳�DRefInterface��DRefObj����Ҫ��Ϊֻ��̳�һ��DRefObj
// ��4��ԭ��ʹ��DRefInterfacePointer�ģ���Ҫ��ΪDRef
//      ��������һ�����壺 #define DRefInterfacePointer DRef 

// NOTE : ͨ����̳�DRefObj�ķ�ʽ���������μ̳е����⣬��Ҫ�������ĸ�����
// ��˲�����Ҫ�������ü�������DRefObj�������ü����ӿڣ�DRefInterface����
// ͳһʹ��DRefObj��DRef���ɣ�����Ҫʹ����̳�

#if 0

template< class T > class DSL_DEPRECATED DRefInterfacePointer;

class DSL_DEPRECATED DRefInterface
{
public:
	// ��Ӧ��ʹ������������ж����ü����������ǲ��ɿ���
	// DSL_DEPRECATED inline int GetRefCount() const { return m_obj->GetRefCount(); }
	DSL_DEPRECATED inline const DRefObj * GetRefObj() const { return m_obj; } // Ҳ��ֻ���������� m_obj->GetRefCount();

protected:
	DSL_DEPRECATED DRefInterface( DRefObj * obj ) : m_obj( obj ) {}
	virtual ~DRefInterface() {}   // ע�⣺�������������ҲӦ����protected��������

private:
	// �ⲿ��Ӧ��ֱ�ӵ���������������Ӧ��ͨ��DRefInterfacePointer�����ʣ�����Ҳ��Ӧ�õ���
	template< class T > friend class DRefInterfacePointer;
	inline int addref2() { return m_obj->addref(); }   // ���ܸ�DRefObj��������̳�ʱ���ͻ
	inline int release2() { return m_obj->release(); }

private:
	DRefObj * m_obj;  // һ�㶼��ָ���Լ����Ҳ�ΪNULL�����ﲻ��ʹ��DRefInterfacePointer������ỷ�����ã��ͷŲ���
};

template< class T >
class DSL_DEPRECATED DRefInterfacePointer
{
public:
	DSL_DEPRECATED DRefInterfacePointer( T * p = NULL ) : m_pObj( p ) { if( m_pObj ) m_pObj->addref2(); }
	DSL_DEPRECATED DRefInterfacePointer( const DRefInterfacePointer< T > & rp ) : m_pObj( rp.m_pObj ) { if( m_pObj ) m_pObj->addref2(); }
	~DRefInterfacePointer() { if( m_pObj ) { m_pObj->release2(); m_pObj = NULL; } }

	inline DRefInterfacePointer< T > & operator = ( const DRefInterfacePointer< T > & rp )
	{
		// if( this == &rp )
		if( m_pObj == rp.m_pObj )
			return *this;

		if( m_pObj != NULL ) m_pObj->release2();
		m_pObj = rp.m_pObj;
		if( m_pObj ) m_pObj->addref2();
		return *this;
	}
	inline DRefInterfacePointer< T > & operator = ( T * p )
	{
		if( m_pObj == p )
			return *this;

		if( m_pObj ) m_pObj->release2();
		m_pObj = p;
		if( m_pObj ) m_pObj->addref2();
		return *this;
	}

	inline T * operator -> () { return m_pObj; }
	inline const T * operator -> () const { return m_pObj; }
	// inline operator T * () const { return m_pObj; }

	inline const T * GetPointer() const { return m_pObj; }
	inline T * GetPointer() { return m_pObj; }

	inline bool operator == ( const DRefInterfacePointer< T > & rp ) const { return m_pObj == rp.m_pObj; }
	inline bool operator == ( const T * p ) const { return m_pObj == p; }
	inline bool operator == ( int p ) const { return m_pObj == (T *)(intptr_t)p; } // for NULL
	inline bool operator != ( const DRefInterfacePointer< T > & rp ) const { return m_pObj != rp.m_pObj; }
	inline bool operator != ( const T * p ) const { return m_pObj != p; }
	inline bool operator != ( int p ) const { return m_pObj != (T *)(intptr_t)p; } // for NULL
	inline operator bool () const { return m_pObj != NULL; }
	inline bool operator ! () const { return m_pObj == NULL; }
	inline bool operator < ( const DRefInterfacePointer< T > & rp ) const { return m_pObj < rp.m_pObj; }

protected:
	T * m_pObj;
};

#endif // #if 0

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBSDL_DREFOBJ_H

