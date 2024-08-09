#pragma once

#include <Util/PrimitiveTypes.h>


namespace zv
{
  class DebugInfo
  {
  public:
    static constexpr s32 k_font_size = 16;
    static constexpr f32 k_update_interval_s = 0.16f;

    static s32 s_frames_per_second;
  };
}
