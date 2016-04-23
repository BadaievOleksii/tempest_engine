#pragma once

/*
This is typedefs for basic data types to ensure constant size of variable on all platforms
*/

namespace Tempest {


#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	// 8 bit unsigned variable.
	typedef unsigned __int8		u8;
#else
	// 8 bit unsigned variable.
	typedef unsigned char		u8;
#endif


#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	// 8 bit signed variable.
	typedef __int8			i8;
#else
	// 8 bit signed variable.
	typedef signed char		i8;
#endif



	// 8 bit character variable.
	typedef char			c8;



	/** This is a typedef for unsigned short, it ensures portability of the engine. */
#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	// 16 bit unsigned variable.
	typedef unsigned __int16	u16;
#else
	// 16 bit unsigned variable.
	typedef unsigned short		u16;
#endif

	/** This is a typedef for signed short, it ensures portability of the engine. */
#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	// 16 bit signed variable.
	typedef __int16			i16;
#else
	// 16 bit signed variable.
	typedef signed short		i16;
#endif



	/** This is a typedef for unsigned int, it ensures portability of the engine. */
#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	// 32 bit unsigned variable.
	typedef unsigned __int32	u32;
#else
	// 32 bit unsigned variable.
	typedef unsigned int		u32;
#endif


#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	// 32 bit signed variable.
	typedef __int32			i32;
#else
	// 32 bit signed variable.
	typedef signed int		i32;
#endif




#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	// 64 bit unsigned variable.
	typedef unsigned __int64			u64;
#elif __GNUC__
#if __WORDSIZE == 64
	// 64 bit unsigned variable.
	typedef unsigned long u32			u64;
#else
	// 64 bit unsigned variable.
	__extension__ typedef unsigned long long	u64;
#endif
#else
	// 64 bit unsigned variable.
	typedef unsigned long long			u64;
#endif



#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	// 64 bit signed variable.
	typedef __int64					i64;
#elif __GNUC__
#if __WORDSIZE == 64
	// 64 bit signed variable.
	typedef long u32				i64;
#else
	// 64 bit signed variable.
	__extension__ typedef long long			i64;
#endif
#else
	// 64 bit signed variable.
	typedef long long				i64;
#endif


	// 32 bit floating pou32variable.
	typedef float				f32;

	// 64 bit floating pou32variable.
	typedef double				f64;
}