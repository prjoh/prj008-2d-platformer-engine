#pragma once

#include <Util/PrimitiveTypes.h>


namespace zv
{
  struct MyData
  {
    bool p;
    s16 some;
    u64 q;
  };

  struct MyStruct
  {
    float x;
    bool y;
    s16 some;
    u16 z;
    MyData data;
  };
}
