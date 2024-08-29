#pragma once

#if ( defined( __CUDACC__ ) || defined( __HIPCC__ ) )
#define __KERNELCC__
#endif

#if !defined( __KERNELCC__ )
#include <algorithm>
#include <cfloat>
#include <cstring>
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <type_traits>
#define __host__
#define __device__
#endif

#ifdef __CUDACC__
// Switch to sync counterparts as CUDA recently deprecated the non-sync ones
#define __shfl( x, y ) __shfl_sync( __activemask(), ( x ), ( y ) )
#define __shfl_up( x, y ) __shfl_up_sync( __activemask(), ( x ), ( y ) )
#define __shfl_down( x, y ) __shfl_down_sync( __activemask(), ( x ), ( y ) )
#define __shfl_xor( x, y ) __shfl_xor_sync( __activemask(), ( x ), ( y ) )
#define __ballot( x ) __ballot_sync( __activemask(), ( x ) )
#define __any( x ) __any_sync( __activemask(), ( x ) )
#define __all( x ) __all_sync( __activemask(), ( x ) )
#endif

#if !defined( __KERNELCC__ )
#if defined( _MSC_VER )
#define HIPRT_ASSERT( cond ) \
	if ( !( cond ) )         \
	{                        \
		__debugbreak();      \
	}
#elif defined( __GNUC__ )
#include <signal.h>
#define HIPRT_ASSERT( cond ) \
	if ( !( cond ) )         \
	{                        \
		raise( SIGTRAP );    \
	}
#else
#define HIPRT_ASSERT( cond )
#endif
#else
#define HIPRT_ASSERT( cond )
#endif

#define HIPRT_STATIC_ASSERT( cond ) static_assert( ( cond ), "" )

#ifdef __KERNELCC__
#define HIPRT_INLINE __forceinline__
#else
#define HIPRT_INLINE inline
#endif

#define HIPRT_HOST __host__
#define HIPRT_DEVICE __device__
#define HIPRT_HOST_DEVICE __host__ __device__

// TODO: cleanup after baking is removed
#if defined( HIPRT_LOAD_FROM_STRING ) || defined( HIPRT_BITCODE_LINKING )
#define GET_ARGS( X ) ( hip::X##Args )
#define GET_INC( X ) ( hip::X##Includes )
#else
#define GET_ARGS( X ) static_cast<const char**>( nullptr )
#define GET_INC( X ) static_cast<const char**>( nullptr )
#endif

#if defined( HIPRT_LOAD_FROM_STRING )
#define GET_ARG_LIST( X ) sizeof( GET_ARGS( X ) ) / sizeof( void* ), GET_ARGS( X ), GET_INC( X )
#else
#define GET_ARG_LIST( X ) 0, 0, 0
#endif

typedef unsigned long long u64;
typedef unsigned int	   u32;
typedef unsigned short	   u16;
typedef unsigned char	   u8;

HIPRT_STATIC_ASSERT( sizeof( u64 ) == 8 );
HIPRT_STATIC_ASSERT( sizeof( u32 ) == 4 );
HIPRT_STATIC_ASSERT( sizeof( u16 ) == 2 );
HIPRT_STATIC_ASSERT( sizeof( u8 ) == 1 );
HIPRT_STATIC_ASSERT( alignof( u64 ) == 8 );
HIPRT_STATIC_ASSERT( alignof( u32 ) == 4 );
HIPRT_STATIC_ASSERT( alignof( u16 ) == 2 );
HIPRT_STATIC_ASSERT( alignof( u8 ) == 1 );

HIPRT_STATIC_ASSERT( sizeof( double ) == 8 );
HIPRT_STATIC_ASSERT( sizeof( float ) == 4 );
HIPRT_STATIC_ASSERT( alignof( double ) == 8 );
HIPRT_STATIC_ASSERT( alignof( float ) == 4 );

HIPRT_STATIC_ASSERT( sizeof( unsigned long long int ) == 8 );
HIPRT_STATIC_ASSERT( sizeof( long long int ) == 8 );
HIPRT_STATIC_ASSERT( sizeof( unsigned int ) == 4 );
HIPRT_STATIC_ASSERT( sizeof( int ) == 4 );
HIPRT_STATIC_ASSERT( sizeof( unsigned short int ) == 2 );
HIPRT_STATIC_ASSERT( sizeof( short int ) == 2 );
HIPRT_STATIC_ASSERT( sizeof( unsigned char ) == 1 );
HIPRT_STATIC_ASSERT( sizeof( char ) == 1 );
HIPRT_STATIC_ASSERT( alignof( unsigned long long int ) == 8 );
HIPRT_STATIC_ASSERT( alignof( long long int ) == 8 );
HIPRT_STATIC_ASSERT( alignof( unsigned int ) == 4 );
HIPRT_STATIC_ASSERT( alignof( int ) == 4 );
HIPRT_STATIC_ASSERT( alignof( unsigned short int ) == 2 );
HIPRT_STATIC_ASSERT( alignof( short int ) == 2 );
HIPRT_STATIC_ASSERT( alignof( unsigned char ) == 1 );
HIPRT_STATIC_ASSERT( alignof( char ) == 1 );

namespace hiprt
{
constexpr float Pi	   = 3.14159265358979323846f;
constexpr float TwoPi  = 2.0f * Pi;
constexpr float FltMin = 1.175494351e-38f;
constexpr float FltMax = 3.402823466e+38f;
constexpr int	IntMin = -2147483647 - 1;
constexpr int	IntMax = 2147483647;

constexpr u32 InvalidValue				= ~0u;
constexpr u32 FullRayMask				= ~0u;
constexpr u32 MaxBatchBuildMaxPrimCount = 512u;

#if __gfx900__ || __gfx902__ || __gfx904__ || __gfx906__ || __gfx908__ || __gfx909__ || __gfx90a__ || __gfx90c__
constexpr int WarpSize = 64;
#else
constexpr int WarpSize = 32;
#endif

template <typename T, typename U>
constexpr HIPRT_HOST_DEVICE T RoundUp( T value, U factor )
{
	return ( value + factor - 1 ) / factor * factor;
}

template <typename T, typename U>
constexpr HIPRT_HOST_DEVICE T DivideRoundUp( T value, U factor )
{
	return ( value + factor - 1 ) / factor;
}

template <typename T>
constexpr HIPRT_HOST_DEVICE T Log2( T n )
{
	return n <= 1 ? 0 : 1 + Log2( ( n + 1 ) / 2 );
}

template <class T, class U>
struct is_same
{
	enum
	{
		value = 0
	};
};

template <class T>
struct is_same<T, T>
{
	enum
	{
		value = 1
	};
};

template <class T>
struct remove_reference
{
	using type = T;
};

template <class T>
struct remove_reference<T&>
{
	using type = T;
};

template <class T>
struct remove_reference<T&&>
{
	using type = T;
};

template <class Ty, Ty Val>
struct integral_constant
{
	static constexpr Ty value = Val;
	using value_type		  = Ty;
	using type				  = integral_constant;

	HIPRT_DEVICE constexpr							operator value_type() const noexcept { return value; }
	[[nodiscard]] HIPRT_DEVICE constexpr value_type operator()() const noexcept { return value; }
};

template <bool _Val>
using bool_constant = integral_constant<bool, _Val>;

using true_type	 = bool_constant<true>;
using false_type = bool_constant<false>;

template <class T>
struct is_lvalue_reference : false_type
{
};

template <class T>
struct is_lvalue_reference<T&> : true_type
{
};

template <class T>
HIPRT_DEVICE constexpr typename remove_reference<T>::type&& move( T&& t ) noexcept
{
	return static_cast<typename remove_reference<T>::type&&>( t );
}

template <class T>
HIPRT_DEVICE constexpr T&& forward( typename remove_reference<T>::type& t ) noexcept
{
	return static_cast<T&&>( t );
}

template <class T>
HIPRT_DEVICE constexpr T&& forward( typename remove_reference<T>::type&& t ) noexcept
{
	HIPRT_STATIC_ASSERT( !is_lvalue_reference<T>::value );
	return static_cast<T&&>( t );
}

template <class T>
struct alignment_of : integral_constant<size_t, alignof( T )>
{
};

template <bool B, class T, class F>
struct conditional
{
	using type = T;
};

template <class T, class F>
struct conditional<false, T, F>
{
	using type = F;
};

template <size_t Size, u32 Align>
struct aligned_storage
{
	struct type
	{
		alignas( Align ) unsigned char data[Size];
	};
};

#if !defined( __KERNELCC__ )
template <typename T>
struct Traits
{
	static const std::string TYPE_NAME;
};

#define DECLARE_TYPE_TRAITS( name ) \
	template <>                     \
	const std::string Traits<name>::TYPE_NAME = #name;
#endif
} // namespace hiprt

template <typename T, size_t Size, u32 Align>
class hiprtPimpl
{
	typename hiprt::aligned_storage<Size, Align>::type data;

  public:
	template <size_t T_size>
	HIPRT_DEVICE static constexpr void PimplSizeCheck()
	{
		HIPRT_STATIC_ASSERT( T_size == Size );
	};

	HIPRT_DEVICE static constexpr void PimplPtrCheck()
	{
		PimplSizeCheck<sizeof( T )>();
		HIPRT_STATIC_ASSERT( alignof( T ) >= hiprt::alignment_of<T>::value );
	}

	template <typename... Args>
	HIPRT_DEVICE hiprtPimpl( Args&&... args )
	{
		PimplPtrCheck();
		new ( &data ) T( hiprt::forward<Args>( args )... );
	}

	HIPRT_DEVICE hiprtPimpl( hiprtPimpl const& o )
	{
		PimplPtrCheck();
		new ( &data ) T( *o );
	}

	HIPRT_DEVICE hiprtPimpl( hiprtPimpl& o )
	{
		PimplPtrCheck();
		new ( &data ) T( *o );
	}

	HIPRT_DEVICE hiprtPimpl( hiprtPimpl&& o )
	{
		PimplPtrCheck();
		new ( &data ) T( hiprt::move( *o ) );
	}

	HIPRT_DEVICE ~hiprtPimpl() {}

	HIPRT_DEVICE hiprtPimpl& operator=( hiprtPimpl const& o )
	{
		PimplPtrCheck();
		**this = *o;
		return *this;
	}

	HIPRT_DEVICE hiprtPimpl& operator=( hiprtPimpl&& o )
	{
		PimplPtrCheck();
		**this = hiprt::move( *o );
		return *this;
	}

	HIPRT_DEVICE T& operator*()
	{
		PimplPtrCheck();
		return *reinterpret_cast<T*>( &data );
	}

	HIPRT_DEVICE T const& operator*() const
	{
		PimplPtrCheck();
		return *reinterpret_cast<T const*>( &data );
	}

	HIPRT_DEVICE T* operator->()
	{
		PimplPtrCheck();
		return &**this;
	}

	HIPRT_DEVICE T const* operator->() const
	{
		PimplPtrCheck();
		return &**this;
	}
};

enum TraversalObjSize
{
	SIZE_GEOM_TRAVERSAL_CUSTOM_STACK   = 128,
	SIZE_SCENE_TRAVERSAL_CUSTOM_STACK  = 192,
	SIZE_GEOM_TRAVERSAL_PRIVATE_STACK  = 416,
	SIZE_SCENE_TRAVERSAL_PRIVATE_STACK = 480,
};

enum TraversalObjAlignment
{
	ALIGNMENT_GEOM_TRAVERSAL_CUSTOM_STACK	= 32,
	ALIGNMENT_SCENE_TRAVERSAL_CUSTOM_STACK	= 32,
	ALIGNMENT_GEOM_TRAVERSAL_PRIVATE_STACK	= 32,
	ALIGNMENT_SCENE_TRAVERSAL_PRIVATE_STACK = 32
};
