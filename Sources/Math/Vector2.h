#pragma once

#include <float.h>

#include <raylib.h>
#include <box2d/b2_math.h>

#include <Math/Util.h>
#include <Util/Extension.h>
#include <Util/PrimitiveTypes.h>


using raylib_vec2 = Vector2;
using box2d_vec2 = b2Vec2;

namespace zv { class Vector2; }

namespace zv
{
	constexpr void vector_set_zero ( Vector2 &dest )noexcept;
	void vector_set_scalar ( Vector2 &dest, f32 value );

	void vector_set ( Vector2 &dest, f32 x, f32 y );

	void vector_copy ( Vector2 &dest, const Vector2 &src );

	bool vector_is_near_zero(const Vector2& src, f32 epsilon = FLT_EPSILON);
	bool vector_is_near_equal(const Vector2&, const Vector2&, f32 epsilon = FLT_EPSILON);

	void vector_add ( Vector2 &dest, const Vector2 &lhs, const Vector2 &rhs );
	void vector_subtract ( Vector2 &dest, const Vector2 &lhs, const Vector2 &rhs );
	void vector_multiply ( Vector2 &dest, const Vector2 &lhs, const Vector2 &rhs );
	void vector_divide ( Vector2 &dest, const Vector2 &lhs, const Vector2 &rhs );

	void vector_add_scalar ( Vector2 &dest, const Vector2 &src, f32 scalar );
	void vector_subtract_scalar ( Vector2 &dest, const Vector2 &src, f32 scalar );
	void vector_multiply_scalar ( Vector2 &dest, const Vector2 &src, f32 scalar );
	void vector_divide_scalar ( Vector2 &dest, const Vector2 &src, f32 scalar );

	bool vector_try_normalize ( Vector2 &dest, const Vector2 &src );
	void vector_normalize ( Vector2 &dest, const Vector2 &src );

	f32 vector_length ( const Vector2 &src );
	f32 vector_length_sqr ( const Vector2 &src );

	f32 vector_dist ( const Vector2 &lhs, const Vector2 &rhs );
	f32 vector_dist_sqr ( const Vector2 &lhs, const Vector2 &rhs );

	f32 vector_dot_product ( const Vector2 &lhs, const Vector2 &rhs );
	f32 vector_cross_product ( const Vector2 &lhs, const Vector2 &rhs );

	void vector_lerp ( Vector2 &dest, const Vector2 &lhs, const Vector2 &rhs, f32 rate );

  class Vector2 final
  {
  public:
		static const Vector2 One;
		static const Vector2 Zero;

  public:
    Vector2() = default;
    Vector2(const Vector2& src);
    Vector2(f32 set_x, f32 set_y);

    Vector2(const raylib_vec2& src);
    Vector2(const box2d_vec2& src);
  
  public:
		bool operator==(const Vector2 &rhs) const;
		bool operator!=(const Vector2 &rhs) const;

		// assignment operators
		Vector2& operator=(const Vector2 &rhs);
		Vector2& operator+=(const Vector2 &rhs);
		Vector2& operator-=(const Vector2 &rhs);
		Vector2& operator*=(const Vector2 &rhs);
		Vector2& operator/=(const Vector2 &rhs);
		Vector2& operator*=(f32 scalar);
		Vector2& operator/=(f32 scalar);

		// unary operators
		Vector2 operator-() const;
		
		// binary operators
		Vector2 operator+(const Vector2 &rhs) const;
		Vector2 operator-(const Vector2 &rhs) const;
		Vector2 operator*(const Vector2 &rhs) const;
		Vector2 operator/(const Vector2 &rhs) const;
		Vector2 operator*(f32 scalar) const;
		Vector2 operator/(f32 scalar) const;

		constexpr Vector2& set_zero (void) noexcept;
		constexpr Vector2& set_one (void) noexcept;
		Vector2& set ( f32 set_x, f32 set_y );

  public:
    f32 x{};
    f32 y{};
  };

  Vector2 operator*( f32 scalar, const Vector2 &rhs );
}

//----------------------------------------------
// Vector2 functions
//----------------------------------------------
inline constexpr void zv::vector_set_zero(Vector2& dest) noexcept
{
  dest.x = 0.0f;
  dest.y = 0.0f;
}

inline void zv::vector_set_scalar( Vector2 &dest, f32 value )
{
  dest.x = value;
  dest.y = value;
}

inline void zv::vector_set ( Vector2 &dest, f32 x, f32 y )
{
  dest.x = x;
  dest.y = y;
}

inline void zv::vector_copy ( Vector2 &dest, const Vector2 &src )
{
  dest.x = src.x;
  dest.y = src.y;
}

inline bool zv::vector_is_near_zero(const Vector2& src, f32 epsilon)
{
  return zv::is_near_zero(src.x, epsilon) && zv::is_near_zero(src.y, epsilon);
}

inline bool zv::vector_is_near_equal(const Vector2& lhs, const Vector2& rhs, f32 epsilon)
{
	zv::remove_cvref_t<decltype(lhs)> delta;
	vector_subtract(delta, lhs, rhs);
  return zv::is_near_zero(delta.x, epsilon) && zv::is_near_zero(delta.y, epsilon);
}

inline void zv::vector_add ( Vector2 &dest, const Vector2 &lhs, const Vector2 &rhs )
{
  dest.x = lhs.x + rhs.x;
  dest.y = lhs.y + rhs.y;
}

inline void zv::vector_subtract ( Vector2 &dest, const Vector2 &lhs, const Vector2 &rhs )
{
  dest.x = lhs.x - rhs.x;
  dest.y = lhs.y - rhs.y;
}

inline void zv::vector_multiply ( Vector2 &dest, const Vector2 &lhs, const Vector2 &rhs )
{
  dest.x = lhs.x * rhs.x;
  dest.y = lhs.y * rhs.y;
}

inline void zv::vector_divide ( Vector2 &dest, const Vector2 &lhs, const Vector2 &rhs )
{
  dest.x = lhs.x / rhs.x;
  dest.y = lhs.y / rhs.y;
}

inline void zv::vector_add_scalar ( Vector2 &dest, const Vector2 &src, f32 scalar )
{
  dest.x = src.x + scalar;
  dest.y = src.y + scalar;
}

inline void zv::vector_subtract_scalar ( Vector2 &dest, const Vector2 &src, f32 scalar )
{
  dest.x = src.x - scalar;
  dest.y = src.y - scalar;
}

inline void zv::vector_multiply_scalar ( Vector2 &dest, const Vector2 &src, f32 scalar )
{
  dest.x = src.x * scalar;
  dest.y = src.y * scalar;
}

inline void zv::vector_divide_scalar ( Vector2 &dest, const Vector2 &src, f32 scalar )
{
  dest.x = src.x / scalar;
  dest.y = src.y / scalar;
}

inline bool zv::vector_try_normalize ( Vector2 &dest, const Vector2 &src )
{
	Vector2 temp;
  vector_normalize(temp, src);

	if (zv::float_is_nan(temp.x) || zv::float_is_nan(temp.y)) return false;

	dest = temp;
	return true;
}

inline void zv::vector_normalize ( Vector2 &dest, const Vector2 &src )
{
	f32 temp = ZV_POW2(src.x) + ZV_POW2(src.y);
	if(temp == 0.0f)
	{
		dest.x = src.x;
		dest.y = src.y;
	}
	else
	{
		temp = 1.0f / sqrtf(temp);
		dest.x = src.x * temp;
		dest.y = src.y * temp;
	}
}

inline f32 zv::vector_length ( const Vector2 &src )
{
	return sqrtf(vector_length_sqr(src));
}

inline f32 zv::vector_length_sqr ( const Vector2 &src )
{
	return (src.x * src.x + src.y * src.y);
}

inline f32 zv::vector_dist ( const Vector2 &lhs, const Vector2 &rhs )
{
	return sqrt(vector_dist_sqr(lhs, rhs));
}

inline f32 zv::vector_dist_sqr ( const Vector2 &lhs, const Vector2 &rhs )
{
	Vector2 temp;
	vector_subtract(temp, lhs, rhs);
	return vector_length_sqr(temp);
}

inline f32 zv::vector_dot_product ( const Vector2 &lhs, const Vector2 &rhs )
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

inline f32 zv::vector_cross_product ( const Vector2 &lhs, const Vector2 &rhs )
{
	return lhs.y * rhs.x - lhs.x * rhs.y;
}

inline void zv::vector_lerp ( Vector2 &dest, const Vector2 &lhs, const Vector2 &rhs, f32 rate )
{
  // TODO
  f32 temp = 1.0f - rate;
	dest.x = (lhs.x * temp) + (rhs.x * rate);
	dest.y = (lhs.y * temp) + (rhs.y * rate);
  // dest.x = zv::lerp(lhs.x, rhs.x, rate);
  // dest.y = zv::lerp(lhs.y, rhs.y, rate);
}

//----------------------------------------------
//  Vector2
//----------------------------------------------
inline zv::Vector2::Vector2(const Vector2& src)
{
  vector_copy(*this, src);
}

inline zv::Vector2::Vector2(f32 set_x, f32 set_y)
{
  vector_set(*this, set_x, set_y);
}

inline zv::Vector2::Vector2(const raylib_vec2& src)
{
  vector_set(*this, src.x, src.y);
}

inline zv::Vector2::Vector2(const box2d_vec2& src)
{
  vector_set(*this, src.x, src.y);
}

inline zv::Vector2& zv::Vector2::operator= ( const Vector2 &rhs )
{
	vector_copy ( ( *this ), rhs );

	return *this;
}

inline bool zv::Vector2::operator==( const Vector2 &rhs ) const
{
	return vector_is_near_equal( (*this), rhs );
} 

inline bool zv::Vector2::operator!=( const Vector2 &rhs ) const
{
	return !vector_is_near_equal( ( *this ), rhs );
}

inline zv::Vector2& zv::Vector2::operator += ( const Vector2 &rhs )
{ 
	vector_add ( ( *this ), ( *this ), rhs );

	return *this;
}

inline zv::Vector2& zv::Vector2::operator -= ( const Vector2 &rhs )
{
	vector_subtract ( ( *this ), ( *this ), rhs );

	return *this;
}

inline zv::Vector2& zv::Vector2::operator *= (const Vector2 &rhs)
{
	vector_multiply((*this), (*this), rhs);

	return *this;
}

inline zv::Vector2& zv::Vector2::operator /= (const Vector2 &rhs)
{
	vector_divide((*this), (*this), rhs);

	return *this;
}

inline zv::Vector2& zv::Vector2::operator *= ( f32 scalar ) 
{
	vector_multiply_scalar ( ( *this ), ( *this ), scalar );

	return *this;
}

inline zv::Vector2& zv::Vector2::operator /= ( f32 scalar ) 
{
	vector_divide_scalar ( ( *this ), ( *this ), scalar );

	return *this;
}

inline zv::Vector2 zv::Vector2::operator - () const
{
	return Vector2( -this->x, -this->y );
}

inline zv::Vector2 zv::Vector2::operator + ( const Vector2 &rhs ) const
{
	Vector2 temp;

	vector_add ( temp, ( *this ), rhs );

	return temp;
}

inline zv::Vector2 zv::Vector2::operator - ( const Vector2 &rhs ) const 
{
	Vector2 temp;

	vector_subtract ( temp, ( *this ), rhs );

	return temp;
}

inline zv::Vector2 zv::Vector2::operator * (const Vector2 &rhs) const
{
	Vector2 temp;

	vector_multiply(temp, (*this), rhs);

	return temp;
}

inline zv::Vector2 zv::Vector2::operator / (const Vector2 &rhs) const
{
	Vector2 temp;

	vector_divide(temp, (*this), rhs);

	return temp;
}

inline zv::Vector2 zv::Vector2::operator * ( f32 scalar ) const
{
	Vector2 temp;

	vector_multiply_scalar ( temp, ( *this ), scalar);

	return temp;
}

inline zv::Vector2 zv::Vector2::operator / ( f32 scalar ) const 
{
	Vector2 temp;

	vector_divide_scalar ( temp, ( *this ), scalar );

	return temp;
}

inline constexpr zv::Vector2& zv::Vector2::set_zero ( void )noexcept
{
	vector_set_zero( ( *this ) );
	return *this;
}

inline constexpr zv::Vector2& zv::Vector2::set_one ( void )noexcept
{
	vector_set_scalar( ( *this ), 1.0f );
	return *this;
}

inline zv::Vector2& zv::Vector2::set( f32 set_x, f32 set_y )
{
	vector_set( ( *this ), set_x, set_y );
	return *this;
} 

inline zv::Vector2 zv::operator* ( f32 scalar, const Vector2 &rhs ) 
{
	Vector2 temp;

	vector_multiply_scalar ( temp, rhs, scalar );

	return temp;
}
