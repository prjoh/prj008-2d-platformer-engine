#pragma once

#include <box2d/b2_world.h>

#include <ECS/Component.h>
#include <Math/Vector2.h>


namespace zv
{
  class SingletonPhysicsWorld final : public SingletonComponent
  {
    friend class Game;
    friend class PhysicsSystem;
    
    friend class ActorControllerSystem;

  public:
    struct Args : public ComponentArgs
    {
      Vector2 gravity;
      f32 timeStep;
      s32 velocityIterations;
      s32 positionIterations;
    };

  public:
    SingletonPhysicsWorld() { m_type = eSingletonComponentType::SingletonPhysicsWorld; }
    ~SingletonPhysicsWorld() = default;

  private:
    // TODO: Call location unclear!!!
    void create(const ComponentArgs* ptr_args) override;

  private:
    f32 m_time_step{};
		s32 m_velocity_iterations{};
		s32 m_position_iterations{};
		b2World m_world{ {0.0f, 0.0f} };
  };
}

inline void zv::SingletonPhysicsWorld::create(const ComponentArgs* ptr_args)
{
  // TODO: Add to base class???
  ZV_ASSERT_MSG(ptr_args != nullptr, "Expected SingletonPhysicsWorld::Args was null.");

  const auto args = *reinterpret_cast<const Args*>(ptr_args);

  m_time_step = args.timeStep;
  m_velocity_iterations = args.velocityIterations;
  m_position_iterations = args.positionIterations;
  m_world.SetGravity({ args.gravity.x, args.gravity.y });
}
