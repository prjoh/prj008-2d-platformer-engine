#pragma once

#include <Util/PrimitiveTypes.h>

namespace zv { class EntityManager; }


namespace zv
{
  class System
  {
  public:
    explicit System(EntityManager* ptr_entity_manager) : m_ptr_entity_manager(ptr_entity_manager) {}
    virtual ~System() = default;

  public:
    virtual void post_init() = 0;
    virtual void fixed_update(f32 fixed_delta_time) = 0;
    virtual void update(f32 delta_time_s) = 0;
    virtual void late_update(f32 delta_time_s) = 0;

  protected:
    EntityManager* m_ptr_entity_manager{ nullptr };
  };
}
