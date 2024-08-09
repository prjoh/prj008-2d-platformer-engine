#pragma once


#include <Core/Guid.h>
#include <Core/ObjectPool.h>

#include <Util/PrimitiveTypes.h>

namespace zv { class ComponentFactoryImpl; }
namespace zv { enum class eComponentType : s32; }
namespace zv { enum class eSingletonComponentType : s32; }

/*
namespace _zv
{
  struct ZObject
  {
  protected:
    ZObject() = default;
  };

  struct ComponentState : public ZObject
  {
    
  protected:
    ComponentState() = default;
  };

  struct ComponentContext
  {
  protected:
    ComponentContext() = default;
  };


  class Component
  {
    friend class ComponentFactoryImpl;

  public:
    Component() = default;
    virtual ~Component() = default;

  public:
    const zv::Guid& object_id() const { return m_guid; }

  protected:
    virtual void create(const ComponentState* ptr_state) = 0;

  protected:
    zv::Guid m_guid{ zv::Guid::s_generate() };
  };


  class SingletonComponent : public Component
  {
  public:
    auto get_type() -> zv::eSingletonComponentType { return m_type; }

  protected:
    zv::eSingletonComponentType m_type;
  };


  class PooledComponent : public zv::PooledObject, public Component
  {
  public:
    auto get_type() -> zv::eComponentType { return m_type; }

  protected:
    zv::eComponentType m_type;
  };


  class ColliderComponent final : public PooledComponent
  {
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

  public:
    ColliderComponent() { m_type = zv::eComponentType::Collider; }
    ~ColliderComponent() = default;
  
  public:
    bool is_category(zv::eColliderCategory category) const;

  private:
    void create(const ComponentState* ptr_state) override
    {
      ZV_ASSERT_MSG(ptr_state != nullptr, "Expected ColliderComponent::State was null.");

      m_state = *(const State*)ptr_state;

      
    }

  private:
    struct Context : public ComponentContext
    {
      b2World* ptr_world{ nullptr };

      std::unique_ptr<b2Shape> m_ptr_shape{ nullptr };

      b2Body* m_ptr_body{ nullptr };
		  b2Fixture* m_ptr_fixture{ nullptr };
    } m_context;

    struct State : public ComponentState
    {
      eBodyType body_type;
      eColliderType collider_type;
      f32 density;
      f32 friction;
      f32 restitution;
      f32 linear_damping = 0.0f;
      f32 angular_damping = 0.01f;
      // Type parameters
      struct BoxTypeParams
      {
        f32 width  = 1.0f;
        f32 height = 1.0f;
      } box_params;
      // Collision filtering
      u16 category = 0x01;
      u16 mask = 0xff;
      // User Data // TODO: Move this to its own component (FilterBits)
      // u8 tag;
      // u8 layer;
    } m_state;
  };
}
*/

namespace zv
{
  struct ComponentArgs
  {
  protected:
    ComponentArgs() = default;
  };

  class Component
  {
    friend class ComponentFactoryImpl;

  public:
    Component() = default;
    virtual ~Component() = default;

  public:
    const Guid& object_id() const { return m_guid; }

  protected:
    virtual void create(const ComponentArgs* ptr_args) = 0;

  protected:
    Guid m_guid{ Guid::s_generate() };
  };

  class SingletonComponent : public Component
  {
  public:
    auto get_type() -> eSingletonComponentType { return m_type; }

  protected:
    eSingletonComponentType m_type;
  };

  class PooledComponent : public PooledObject, public Component
  {
  public:
    auto get_type() -> eComponentType { return m_type; }

  protected:
    eComponentType m_type;
  };
}
