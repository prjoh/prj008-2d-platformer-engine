#pragma once

#include <ECS/System.h>

namespace zv { class EntityManager; }


namespace zv
{
  class ActorControllerSystem final : public System
  {
  private:
    using base_type = System;

  public:
    explicit ActorControllerSystem(EntityManager* ptr_entity_manager) : base_type(ptr_entity_manager) {}
    ~ActorControllerSystem() = default;

  public:
    void post_init() override;
    void fixed_update(f32 fixed_delta_time_s) override;
    void update(f32 delta_time_s) override;
    void late_update(f32 delta_time_s) override {}
  
  private:
    ComponentTupleContainer<PlayerControllerComponent, ColliderComponent> m_components;
  };
}
