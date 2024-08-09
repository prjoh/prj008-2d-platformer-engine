#pragma once

#include <map>

#include <Config.h>
#include <ECS/Component.h>
#include <ECS/ComponentTypes.h>
#include <Util/PhysicsContactListener.h>


namespace zv
{
  class SingletonPhysicsContactInfo final : public SingletonComponent
  {
    friend class Game;
    friend class PhysicsSystem;
    friend class ActorControllerSystem;

  public:
    struct Args : public ComponentArgs
    {
    };

  private:
    struct PhysicsContactMap
    {
    public:
      auto get(const zv::Guid& key) -> std::optional<const PhysicsContact*>
      {
        for (s32 i = 0; i < m_size; ++i)
        {
          if (m_colliders[i] == key)
          {
            return &m_events[i];
          }
        }
        return std::nullopt;
      }

      bool add(const zv::Guid& key, const PhysicsContact& event)
      {
        if (m_size >= ZV_CONTACT_EVENTS_SIZE)
        {
          return false;
        }

        m_colliders[m_size] = key;
        m_events[m_size] = event;
        m_size++;
        return true;
      }

      void reset()
      {
        m_size = 0;
      }

    private:
      std::array<zv::Guid, ZV_CONTACT_EVENTS_SIZE> m_colliders{};
      std::array<PhysicsContact, ZV_CONTACT_EVENTS_SIZE> m_events{};
      u32 m_size{ 0 };
    };

  public:
    SingletonPhysicsContactInfo() { m_type = eSingletonComponentType::SingletonPhysicsContactInfo; }
    ~SingletonPhysicsContactInfo() = default;

  public:
    void record_contact_event(const zv::Guid& colliderId, PhysicsContact::eType contactType, zv::ColliderComponent* pCollidesWith)
    {
      PhysicsContact contact{};
      contact.ptr_collider = pCollidesWith;
      contact.type = contactType;
      m_contacts.add(colliderId, contact);
    }

    void reset_contact_events()
    {
      m_contacts.reset();
    }

  private:
    // TODO: Call location unclear!!!
    void create(const ComponentArgs* ptr_args) override;

  private:
    PhysicsContactMap m_contacts{};
  };
}

inline void zv::SingletonPhysicsContactInfo::create(const ComponentArgs* ptr_args)
{
  // TODO: Add to base class???
  ZV_ASSERT_MSG(ptr_args != nullptr, "Expected SingletonPhysicsContactInfo::Args was null.");

  const auto args = *reinterpret_cast<const Args*>(ptr_args);
}
