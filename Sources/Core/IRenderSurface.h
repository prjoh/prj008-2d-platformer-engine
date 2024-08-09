#pragma once

#include <Util/PrimitiveTypes.h>

namespace zv
{
  class IRenderSurface
  {
  public:
    virtual s32 get_render_width() const = 0;
    virtual s32 get_render_height() const = 0;
  };
}
