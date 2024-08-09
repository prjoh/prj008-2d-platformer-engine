#pragma once

#include <raylib.h>

#include <Util/PrimitiveTypes.h>


using raylib_vec4 = Vector4;

namespace zv
{
  class Vector4 final
  {
  public:
		static const Vector4 One;
		static const Vector4 Zero;

  public:
    Vector4() = default;
    Vector4(f32 _x, f32 _y, f32 _z, f32 _w = 1.0f) : x(_x), y(_y), z(_z), w(_w) {};
    Vector4(const raylib_vec4& vec4) : Vector4(vec4.x, vec4.y, vec4.z, vec4.w) {};
  
  public:
    f32 x{};  // Vector x component
    f32 y{};  // Vector y component
    f32 z{};  // Vector y component
    f32 w{};  // Vector y component
  };
}
