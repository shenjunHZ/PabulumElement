#ifndef __ARCH_I386_ATOMIC__
#define __ARCH_I386_ATOMIC__

typedef struct { volatile int counter; } atomic_t;

#ifndef DOAX_DEPRECATED
#if defined(_WIN32) || defined (_WIN64)
// 放在class关键字后面，以及函数或者变量定义的前面
#define DOAX_DEPRECATED	__declspec(deprecated)
#else
#define DOAX_DEPRECATED	__attribute__ ((deprecated))
#endif // #ifdef WIN32
#endif // #ifndef DOAX_DEPRECATED

#ifdef _WIN32

//#include <windows.h>
#include "winsock2i.h"

DOAX_DEPRECATED inline int atomic_read( atomic_t * v )
{
	return v->counter;
}

inline void atomic_set( atomic_t * v, int i )
{
	InterlockedExchange( (LONG *)&(v->counter), i );
	return;
}

// atomic add ( sub can convert to add negative ), return *old* value
inline int atomic_add( atomic_t * v, int i )
{
	return InterlockedExchangeAdd( (LONG *)&(v->counter), i );
}

// add one, return *new* value
inline int atomic_inc( atomic_t * v )
{
	return InterlockedIncrement( (LONG *)&(v->counter) );
}

// sub one, return *new* value
inline int atomic_dec( atomic_t * v )
{
	return InterlockedDecrement( (LONG *)&(v->counter) );
}

// set value, return *old* val
DOAX_DEPRECATED inline int atomic_xchg( atomic_t * v, int i )
{
	return InterlockedExchange( (LONG *)&(v->counter), i );
}

// compare, if equal, set value, always return *old* val
DOAX_DEPRECATED inline int atomic_xchg_cmp( atomic_t * v, int i, int cmp )
{
	return InterlockedCompareExchange( (LONG *)&(v->counter), i, cmp );
}

#elif defined( __i386__ ) || defined( __x86_64__ )

// use i386 implement,

DOAX_DEPRECATED inline int atomic_read( atomic_t * v )
{
	return v->counter;
}

inline void atomic_set( atomic_t * v, int i )
{
	v->counter = i;
	return;
}

// atomic add ( sub can convert to add negative ), return *old* value
inline int atomic_add( atomic_t * v, int i )
{
	asm volatile ("lock; xaddl %0,%1"
		: "=r" (i), "=m" (v->counter)
		: "0" (i), "m" (v->counter)
		: "memory", "cc");
	return i;
}

// add one, return *new* value
inline int atomic_inc( atomic_t * v )
{
	return atomic_add( v, 1 ) + 1;
}

// sub one, return *new* value
inline int atomic_dec( atomic_t * v )
{
	return atomic_add( v, -1 ) - 1;
}

// set value, return old val
DOAX_DEPRECATED inline int atomic_xchg( atomic_t * v, int i )
{
	int prev = i;
	asm volatile ("xchgl %0, %1"
		: "=r" (prev), "+m" (v->counter)
		: "0" (prev));
	return prev;
}

// compare, if equal, set value, always return old val
DOAX_DEPRECATED inline int atomic_xchg_cmp( atomic_t * v, int i, int cmp )
{
	int prev;
	asm volatile ("lock; cmpxchgl %1, %2"
		: "=a" (prev)
		: "r" (i), "m" (v->counter), "0"(cmp)
		: "memory", "cc");
	return prev;
}

#else
// use gcc builtin func, may not support by all, otherwise need implement
// code from ACE and apr

inline int atomic_read( atomic_t * v )
{
	return v->counter;
}

inline void atomic_set( atomic_t * v, int i )
{
	v->counter = i;
	return;
}

// atomic add ( sub can convert to add negative ), return *old* value
inline int atomic_add( atomic_t * v, int i )
{
	return __sync_add_and_fetch(&v->counter,i);
}

// add one, return *new* value
inline int atomic_inc( atomic_t * v )
{
	return atomic_add( v, 1 );
}

// sub one, return *new* value
inline int atomic_dec( atomic_t * v )
{
	return atomic_add( v, -1 );
}

// set value, return old val
inline int atomic_xchg( atomic_t * v, int i )
{
	__sync_synchronize();
	return __sync_lock_test_and_set(&v->counter, i);
}

// compare, if equal, set value, always return old val
inline int atomic_xchg_cmp( atomic_t * v, int i, int cmp )
{
	return __sync_val_compare_and_swap(&v->counter, cmp, i);
}

#endif


// disable old implementation
#if 0

typedef struct { volatile int counter; } atomic_t;

#define ATOMIC_INIT(i)  { (i) }

#define atomic_read(v) ((v)->counter)

#define atomic_set(v,i) (((v)->counter) = (i))


static __inline__ void atomic_add(int i, atomic_t *v)
{
	__sync_add_and_fetch(&v->counter,i);
}
static __inline__ void atomic_sub(int i, atomic_t *v)
{
	__sync_sub_and_fetch(&v->counter,i);
}

static __inline__ int atomic_sub_and_test(int i, atomic_t *v)
{
	return !(__sync_sub_and_fetch(&v->counter, i));	
}

static __inline__ void atomic_inc(atomic_t *v)
{
	__sync_add_and_fetch(&v->counter, 1);
}

static __inline__ void atomic_dec(atomic_t *v)
{
	__sync_sub_and_fetch(&v->counter,1);
}
static __inline__ int atomic_dec_and_test(atomic_t *v)
{
	return !(__sync_sub_and_fetch(&v->counter, 1));
}
static __inline__ int atomic_inc_and_test(atomic_t *v)
{
	return !(__sync_add_and_fetch(&v->counter,1));
}

static __inline__ int atomic_add_negative(int i, atomic_t *v)
{
	return 0>(__sync_sub_and_fetch(&v->counter,i));
}
static __inline__ int atomic_add_return(int i, atomic_t *v)
{
	return __sync_add_and_fetch(&v->counter,i);
}
static __inline__ int atomic_sub_return(int i, atomic_t *v)
{
	return __sync_sub_and_fetch(&v->counter,i);
}

#define atomic_inc_return(v)  (atomic_add_return(1,v))
#define atomic_dec_return(v)  (atomic_sub_return(1,v))


#elif 0

// #include <linux/config.h>
// #include <linux/compiler.h>
// #include <asm/processor.h>

#define CONFIG_SMP

/*
 * Atomic operations that C can't guarantee us.  Useful for
 * resource counting etc..
 */

#ifdef CONFIG_SMP
#define LOCK "lock ; "
#else
#define LOCK ""
#endif

/*
 * Make sure gcc doesn't try to be clever and move things around
 * on us. We need to use _exactly_ the address the user gave us,
 * not some alias that contains the same information.
 */
typedef struct { volatile int counter; } atomic_t;

#define ATOMIC_INIT(i)	{ (i) }

/**
 * atomic_read - read atomic variable
 * @v: pointer of type atomic_t
 * 
 * Atomically reads the value of @v.
 */ 
#define atomic_read(v)		((v)->counter)

/**
 * atomic_set - set atomic variable
 * @v: pointer of type atomic_t
 * @i: required value
 * 
 * Atomically sets the value of @v to @i.
 */ 
#define atomic_set(v,i)		(((v)->counter) = (i))

/**
 * atomic_add - add integer to atomic variable
 * @i: integer value to add
 * @v: pointer of type atomic_t
 * 
 * Atomically adds @i to @v.
 */
static __inline__ void atomic_add(int i, atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "addl %1,%0"
		:"=m" (v->counter)
		:"ir" (i), "m" (v->counter));
}

/**
 * atomic_sub - subtract the atomic variable
 * @i: integer value to subtract
 * @v: pointer of type atomic_t
 * 
 * Atomically subtracts @i from @v.
 */
static __inline__ void atomic_sub(int i, atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "subl %1,%0"
		:"=m" (v->counter)
		:"ir" (i), "m" (v->counter));
}

/**
 * atomic_sub_and_test - subtract value from variable and test result
 * @i: integer value to subtract
 * @v: pointer of type atomic_t
 * 
 * Atomically subtracts @i from @v and returns
 * true if the result is zero, or false for all
 * other cases.
 */
static __inline__ int atomic_sub_and_test(int i, atomic_t *v)
{
	unsigned char c;

	__asm__ __volatile__(
		LOCK "subl %2,%0; sete %1"
		:"=m" (v->counter), "=qm" (c)
		:"ir" (i), "m" (v->counter) : "memory");
	return c;
}

/**
 * atomic_inc - increment atomic variable
 * @v: pointer of type atomic_t
 * 
 * Atomically increments @v by 1.
 */ 
static __inline__ void atomic_inc(atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "incl %0"
		:"=m" (v->counter)
		:"m" (v->counter));
}

/**
 * atomic_dec - decrement atomic variable
 * @v: pointer of type atomic_t
 * 
 * Atomically decrements @v by 1.
 */ 
static __inline__ void atomic_dec(atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "decl %0"
		:"=m" (v->counter)
		:"m" (v->counter));
}

/**
 * atomic_dec_and_test - decrement and test
 * @v: pointer of type atomic_t
 * 
 * Atomically decrements @v by 1 and
 * returns true if the result is 0, or false for all other
 * cases.
 */ 
static __inline__ int atomic_dec_and_test(atomic_t *v)
{
	unsigned char c;

	__asm__ __volatile__(
		LOCK "decl %0; sete %1"
		:"=m" (v->counter), "=qm" (c)
		:"m" (v->counter) : "memory");
	return c != 0;
}

/**
 * atomic_inc_and_test - increment and test 
 * @v: pointer of type atomic_t
 * 
 * Atomically increments @v by 1
 * and returns true if the result is zero, or false for all
 * other cases.
 */ 
static __inline__ int atomic_inc_and_test(atomic_t *v)
{
	unsigned char c;

	__asm__ __volatile__(
		LOCK "incl %0; sete %1"
		:"=m" (v->counter), "=qm" (c)
		:"m" (v->counter) : "memory");
	return c != 0;
}

/**
 * atomic_add_negative - add and test if negative
 * @v: pointer of type atomic_t
 * @i: integer value to add
 * 
 * Atomically adds @i to @v and returns true
 * if the result is negative, or false when
 * result is greater than or equal to zero.
 */ 
static __inline__ int atomic_add_negative(int i, atomic_t *v)
{
	unsigned char c;

	__asm__ __volatile__(
		LOCK "addl %2,%0; sets %1"
		:"=m" (v->counter), "=qm" (c)
		:"ir" (i), "m" (v->counter) : "memory");
	return c;
}

/**
 * atomic_add_return - add and return
 * @v: pointer of type atomic_t
 * @i: integer value to add
 *
 * Atomically adds @i to @v and returns @i + @v
 */
static __inline__ int atomic_add_return(int i, atomic_t *v)
{
	int __i;
#ifdef CONFIG_M386
	if(unlikely(boot_cpu_data.x86==3))
		goto no_xadd;
#endif
	/* Modern 486+ processor */
	__i = i;
	__asm__ __volatile__(
		LOCK "xaddl %0, %1;"
		:"=r"(i)
		:"m"(v->counter), "0"(i));
	return i + __i;

#ifdef CONFIG_M386
no_xadd: /* Legacy 386 processor */
	local_irq_disable();
	__i = atomic_read(v);
	atomic_set(v, i + __i);
	local_irq_enable();
	return i + __i;
#endif
}

static __inline__ int atomic_sub_return(int i, atomic_t *v)
{
	return atomic_add_return(-i,v);
}

#define atomic_inc_return(v)  (atomic_add_return(1,v))
#define atomic_dec_return(v)  (atomic_sub_return(1,v))

/* These are x86-specific, used by some header files */
#define atomic_clear_mask(mask, addr) \
__asm__ __volatile__(LOCK "andl %0,%1" \
: : "r" (~(mask)),"m" (*addr) : "memory")

#define atomic_set_mask(mask, addr) \
__asm__ __volatile__(LOCK "orl %0,%1" \
: : "r" (mask),"m" (*(addr)) : "memory")

/* Atomic operations are already serializing on x86 */
#define smp_mb__before_atomic_dec()	barrier()
#define smp_mb__after_atomic_dec()	barrier()
#define smp_mb__before_atomic_inc()	barrier()
#define smp_mb__after_atomic_inc()	barrier()

#endif

#endif // __ARCH_I386_ATOMIC__
