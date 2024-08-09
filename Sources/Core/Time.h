#pragma once

#include <raylib.h>

#include <Util/Singleton.h>
#include <Util/PrimitiveTypes.h>


namespace zv
{
  class Time final : public Singleton<Time>
  {
  public:
    Time() : base_type(this) {};

  public:
    void init(f32 fixed_time_step) { m_fixed_time_step = fixed_time_step; }

  public:
		f32 delta_time_s() const{ return GetFrameTime(); }
    s32 get_frames_per_second() const { return GetFPS(); }

    void update();
    bool fixed_time_step_tick();

  private:
    f32 m_fixed_time_step{ 1.0f };  // fixed time step per seconds
    f32 m_last_frame_time_s{ 0.0f };
  };
}
