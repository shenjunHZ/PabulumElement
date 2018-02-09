#ifndef __COMMON_NONCOPYABLE_H__
#define __COMMON_NONCOPYABLE_H__

namespace Common
{
	class CNoncopyable
	{
	protected:
		CNoncopyable() {}
		~CNoncopyable() {}

	private: 
		CNoncopyable( const CNoncopyable& );
		CNoncopyable& operator=( const CNoncopyable& );
	};

}

#endif // __COMMON_NONCOPYABLE_H__
