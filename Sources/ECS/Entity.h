#pragma once

#include <string>
#include <string_view>

#include <Core/ObjectPool.h>
#include <ECS/ComponentFactory.h>

namespace zv { class EntityManager; }
namespace zv { struct ComponentArgs; }

namespace zv
{
  class Entity final : public PooledObject
  {
    friend class EntityManager;

  public:
    Entity()
    {
      m_components.reserve(ZV_ENTITY_COMPONENT_SIZE);
    }
    ~Entity() = default;

  public:
    template <typename T>
    T* add_component(const ComponentArgs* pArgs)
    {
      ZV_ASSERT(m_ptr_component_factory != nullptr);

      Component* ptr_component = m_ptr_component_factory->create_component<T>(pArgs);

      m_components.emplace_back(ptr_component);

      return static_cast<T*>(ptr_component);
    }

    template <typename T>
    void destroy_component(T* ptr_component)
    {
      ZV_ASSERT(m_ptr_component_factory != nullptr);
      
      const auto& object_id = ptr_component->object_id();
      auto it = std::find_if(m_components.begin(), m_components.end(),[object_id](const auto* c) { return c->object_id() == object_id; });

      ZV_ASSERT(it != m_components.end());

      m_components.erase(it);
      m_ptr_component_factory->destroy_component(ptr_component);
    }

    // Gets first one found
    template <typename T>
    auto get_component() -> T*
    {
      auto component_type = m_ptr_component_factory->get_pooled_component_type<T>();

      for (auto* ptr_component : m_components)
      {
        auto* ptr_pooled_component = static_cast<PooledComponent*>(ptr_component);
        if (ptr_pooled_component->get_type() == component_type)
        {
          return static_cast<T*>(ptr_component);
        }
      }

      return nullptr;
    }

    template <typename T>
    auto get_components() -> std::vector<T*>
    {
      std::vector<T*> components;
      auto component_type = m_ptr_component_factory->get_pooled_component_type<T>();

      for (auto* ptr_component : m_components)
      {
        auto* ptr_pooled_component = static_cast<PooledComponent*>(ptr_component);
        if (ptr_pooled_component->get_type() == component_type)
        {
          components.emplace_back(static_cast<T*>(ptr_component));
        }
      }

      return components;
    }

    const Guid& object_id() const { return m_guid; }
    auto name() const -> const std::string_view { return m_name; }

  private:
    void on_destroy()
    {
      ZV_ASSERT(m_ptr_component_factory != nullptr);

      for (auto& ptr_component : m_components)
      {
        m_ptr_component_factory->destroy_component(ptr_component);
      }
      m_components.clear();
    }

  private:
  /*
    struct State : public Reflected
    {
      Guid guid{};
      std::string name{};
      std::array<Component*, ZV_MAX_ENTITY_COMPONENTS> components{};
    } m_state;

    ComponentFactory* m_ptr_component_factory{ nullptr };
  */
    Guid m_guid{ Guid::s_generate() };

    std::vector<Component*> m_components;  // TODO: Implement as a map?

    ComponentFactory* m_ptr_component_factory{ nullptr };
    std::string m_name{};
  };
}
