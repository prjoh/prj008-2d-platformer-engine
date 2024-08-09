#pragma once

#include <ECS/System.h>

namespace zv { class EntityManager; }


namespace zv
{
  class CommandSystem final : public System
  {
  private:
    using base_type = System;

  public:
    explicit CommandSystem(EntityManager* ptr_entity_manager) : base_type(ptr_entity_manager) {}
    ~CommandSystem() = default;

  public:
    void post_init() override {}
    void fixed_update(f32 fixed_delta_time_s) override {}
    void update(f32 delta_time_s) override;
    void late_update(f32 delta_time_s) override {}    
  };
}
