#pragma once

#include <box2d/b2_world_callbacks.h>

namespace zv { class ColliderComponent; }
namespace zv { class SingletonPhysicsContactInfo; }


namespace zv
{
  struct PhysicsContact
  {
    enum class eType
    {
      Begin,
      End,
    } type;
    zv::ColliderComponent* ptr_collider;
  };

  class PhysicsContactListener : public b2ContactListener
  {
  public:
    void acquire_contact_info(SingletonPhysicsContactInfo* ptr_contact_info)
    {
      m_ptr_contact_info = ptr_contact_info;
    }

  private:
    void BeginContact (b2Contact* ptr_contact) override;
    void EndContact (b2Contact* ptr_contact) override;
    // void PreSolve (b2Contact* ptr_contact, const b2Manifold* ptr_old_manifold) override;
    // void PostSolve (b2Contact* ptr_contact, const b2ContactImpulse* ptr_impulse) override;

  private:
    SingletonPhysicsContactInfo* m_ptr_contact_info{ nullptr };
  };
}
