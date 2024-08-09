#pragma once

#include <Core/Error.h>
#include <ECS/Component.h>

namespace zv
{
  class PlayerControllerComponent final : public PooledComponent
  {
    friend class Game;
    friend class ActorControllerSystem;

  public:
    struct Args : public ComponentArgs
    {
      f32 speed;
      f32 max_run_velocity;
      Vector2 distance_to_jump_peak;
    };

  public:
    PlayerControllerComponent() { m_type = eComponentType::PlayerController; }
    ~PlayerControllerComponent() = default;

  private:
    void create(const ComponentArgs* ptr_args) override;

  private:
    f32 m_speed{};
    f32 m_max_run_velocity{};
    Vector2 m_distance_to_jump_peak{};

    bool m_isGrounded{ false };

    bool m_cmdJumpPressed{ false };
  };
}

inline void zv::PlayerControllerComponent::create(const ComponentArgs* ptr_args)
{
  // TODO: Add to base class???
  ZV_ASSERT_MSG(ptr_args != nullptr, "Expected PlayerControllerComponent::Args was null.");

  auto& args = *static_cast<const Args*>(ptr_args);

  m_speed = args.speed;
  m_max_run_velocity = args.max_run_velocity;
  m_distance_to_jump_peak = args.distance_to_jump_peak;
}
