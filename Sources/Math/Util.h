#pragma once

#include <algorithm>
#include <cmath>
#include <float.h>

#include <Util/PrimitiveTypes.h>


#define ZV_PI         ( 3.141592654f )
#define ZV_PI2        ( PI * 2.0f )
#define ZV_DEG( v )   ( ( v ) * 0.017453292f)
#define ZV_RAD( v )   ( ( v ) * 57.29577950f)
#define ZV_POW2( v )  ( ( v ) * ( v ) )

namespace zv
{
	[[nodiscard]] constexpr auto to_radian(f32 degree)noexcept { return ZV_RAD(degree); }
	[[nodiscard]] constexpr auto to_degree(f32 radian)noexcept { return ZV_DEG(radian); }

  [[nodiscard]] f32	abs ( f32 f )noexcept;
	[[nodiscard]] f64	abs ( f64 f )noexcept;

  [[nodiscard]] f32	clamp ( f32 v, f32 min, f32 max ) noexcept;
  template <typename T> 
  [[nodiscard]] s32	sign ( T v ) noexcept;

	[[nodiscard]] bool float_is_nan ( f32 value ) noexcept;

	[[nodiscard]] bool is_near_equal ( f32 a, f32 b, f32 e=FLT_EPSILON )noexcept;
	[[nodiscard]] bool is_near_equal( f64 a, f64 b, f64 e=DBL_EPSILON )noexcept;
	[[nodiscard]] bool is_near_zero ( f32 value, f32 e=FLT_EPSILON )noexcept;
	[[nodiscard]] bool is_near_zero ( f64 value, f64 e=DBL_EPSILON )noexcept;

	[[nodiscard]] constexpr f32 lerp ( f32 a, f32 b, f32 rate )noexcept;
}

inline f32 zv::abs ( f32 f )noexcept
{
	return fabsf( f );
}

inline f64 zv::abs ( f64 f )noexcept
{
	return fabs( f );
}

inline f32 zv::clamp ( f32 v, f32 min, f32 max )noexcept
{
	return std::clamp(v, min, max);
}

template <typename T> 
inline s32 zv::sign(T v) noexcept
{
  return (T(0) < v) - (v < T(0));
}

inline bool zv::float_is_nan ( f32 value ) noexcept
{
	return std::isnan( value );
}

inline bool zv::is_near_equal ( f32 a, f32 b, f32 e )noexcept
{
	return zv::abs( a - b ) < e;
}

inline bool zv::is_near_equal( f64 a, f64 b, f64 e )noexcept
{
	return zv::abs( a - b ) < e;
}

inline bool zv::is_near_zero ( f32 value, f32 e )noexcept
{
	return zv::abs( value ) < e;
}

inline bool zv::is_near_zero( f64 value, f64 e )noexcept
{
	return zv::abs( value ) < e;
}

constexpr f32 zv::lerp ( f32 a, f32 b, f32 rate )noexcept
{
	return ( ( b - a ) * rate ) + a;
}
