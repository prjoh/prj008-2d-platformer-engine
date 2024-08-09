#include <Core/Time.h>


void zv::Time::update()
{
  m_last_frame_time_s += delta_time_s();
}

bool zv::Time::fixed_time_step_tick()
{
  if (m_last_frame_time_s < m_fixed_time_step)
    return false;

  m_last_frame_time_s -= m_fixed_time_step;
  return true;
}
