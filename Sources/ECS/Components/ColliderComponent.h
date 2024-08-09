#pragma once

#include <box2d/box2d.h>

#include <Config.h>
#include <Core/Error.h>
#include <ECS/Component.h>
#include <ECS/ComponentTypes.h>

namespace zv { class RenderingSystem; }
namespace zv { class Game; }

namespace zv
{
  class ColliderComponent final : public PooledComponent
  {
    friend class Game;
    friend class ActorControllerSystem;
    friend class RenderingSystem;

  public:
    using eBodyType = b2BodyType;

    enum class eColliderType : u8
    {
      Unknown = 1 << 0,
      Box     = 1 << 1,
      // Circle  = 1 << 2,
      // Polygon = 1 << 3,
      // Edge    = 1 << 4,
      // Chain   = 1 << 5,
    };

    struct Args : public ComponentArgs
    {
      b2World* ptr_world;
      eBodyType body_type;
      eColliderType collider_type;
      f32 density;
      f32 friction;
      f32 restitution;
      f32 linear_damping = 0.0f;
      f32 angular_damping = 0.01f;
      // Collision filtering
      u16 category = 0x01;
      u16 mask = 0xff;
      // User Data // TODO: Move this to its own component (FilterBits)
      // u8 tag;
      // u8 layer;
    };

    struct BoxTypeState : public Args
    {
      f32 width  = 1.0f;
      f32 height = 1.0f;
    };

  public:
    ColliderComponent() { m_type = eComponentType::Collider; }
    ~ColliderComponent() = default;
  
  public:
    bool is_category(eColliderCategory category) const;

  private:
    void create(const ComponentArgs* ptr_args) override;

  private:
    eColliderType m_collider_type{ eColliderType::Unknown };

    std::unique_ptr<b2Shape> m_ptr_shape{ nullptr };

		// b2World* m_ptr_world{ nullptr };

		b2Body* m_ptr_body{ nullptr };
		b2Fixture* m_ptr_fixture{ nullptr };
  };
}

inline void zv::ColliderComponent::create(const ComponentArgs* ptr_args)
{
  // TODO: Add to base class???
  ZV_ASSERT_MSG(ptr_args != nullptr, "Expected ColliderComponent::Args was null.");

  auto& args = *static_cast<const Args*>(ptr_args);

  m_collider_type = args.collider_type;

  // m_ptr_world = args.ptr_world;

  // TODO: Give option to pass in a bodyPtr? For connected fixtures!
  b2BodyDef body_def;
  body_def.type = args.body_type;
  body_def.position = { 0.0f, 0.0f };
  body_def.angle = 0.0f;
  /*
  Damping is used to reduce the world velocity of bodies. 
  Damping is different than friction because friction only occurs with contact. 
  Damping is not a replacement for friction and the two effects should be used together.
  Damping parameters should be between 0 and infinity, with 0 meaning no damping, and infinity meaning full damping. 
  Normally you will use a damping value between 0 and 0.1. I generally do not use linear damping because it makes bodies look like they are floating.
  Damping is approximated for stability and performance. At small damping values the damping effect is mostly independent of the time step. 
  At larger damping values, the damping effect will vary with the time step. This is not an issue if you use a fixed time step (recommended).
  */
  body_def.linearDamping = args.linear_damping;
  body_def.angularDamping = args.angular_damping;
  // TODO!!!
  // /*
  // You can use the gravity scale to adjust the gravity on a single body. 
  // Be careful though, increased gravity can decrease stability.
  // */
  // bodyDef.gravityScale = 0.0f;
  // /*
  // What does sleep mean? Well it is expensive to simulate bodies, so the less we have to simulate the better. 
  // When a body comes to rest we would like to stop simulating it.
  // When Box2D determines that a body (or group of bodies) has come to rest, the body enters a sleep state which has very little CPU overhead. 
  // If a body is awake and collides with a sleeping body, then the sleeping body wakes up. 
  // Bodies will also wake up if a joint or contact attached to them is destroyed. You can also wake a body manually.
  // The body definition lets you specify whether a body can sleep and whether a body is created sleeping.
  // */
  // bodyDef.allowSleep = true;
  // bodyDef.awake = true;
  // /*
  // You may want a rigid body, such as a character, to have a fixed rotation. 
  // Such a body should not rotate, even under load. You can use the fixed rotation setting to achieve this.
  // The fixed rotation flag causes the rotational inertia and its inverse to be set to zero.
  // */
  // bodyDef.fixedRotation = true;
  // /*
  // Perform CCD with both static and dynamic bodies at the cost of performance.
  // */
  // bodyDef.bullet = true;
  // /*
  // You can create a body in an inactive state and later re-activate it.
  // */
  // bodyDef.enabled = true;
  body_def.userData.pointer = (uintptr_t)this;

  m_ptr_body = args.ptr_world->CreateBody(&body_def);

  // m_userData.tag = args.tag;
  // m_userData.layer = args.layer;

  b2FixtureDef fixture_def;
  /*
  The fixture density is used to compute the mass properties of the parent body.
  The density can be zero or positive.
  You should generally use similar densities for all your fixtures. This will improve stacking stability.
  */
  fixture_def.density = args.density;    // (kg/m^2)
  fixture_def.friction = args.friction;  // [0.0, 1.0]
  /*
  Restitution is used to make objects bounce. The restitution value is usually set to be between 0 and 1.
  Consider dropping a ball on a table. A value of zero means the ball won't bounce.
  This is called an inelastic collision. A value of one means the ball's velocity will be exactly reflected.
  This is called a perfectly elastic collision. Restitution is combined using the following formula.
  */
  fixture_def.restitution = args.restitution;  // [0.0, 1.0]
  // fixtureDef.restitutionThreshold // TODO
  // fixtureDef.isSensor // TODO
  fixture_def.filter.categoryBits = args.category;
  fixture_def.filter.maskBits = args.mask;
  fixture_def.filter.groupIndex = 0;  // TODO

  switch (m_collider_type)
  {
    case eColliderType::Box:
    {
      auto& box_type_args = *static_cast<const BoxTypeState*>(ptr_args);

      m_ptr_shape = std::make_unique<b2PolygonShape>();

      auto* ptr_poly_shape = static_cast<b2PolygonShape*>(m_ptr_shape.get());
      ptr_poly_shape->SetAsBox(box_type_args.width * 0.5f, box_type_args.height * 0.5f);

      fixture_def.shape = ptr_poly_shape;

      m_ptr_fixture = m_ptr_body->CreateFixture(&fixture_def);

      break;
    }
    default:
    {
      ZV_ASSERT_UNREACHABLE();
    }
  }
}

inline bool zv::ColliderComponent::is_category(eColliderCategory category) const
{
  return m_ptr_fixture->GetFilterData().categoryBits == (u16)category;
}
