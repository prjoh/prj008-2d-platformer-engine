#pragma once

#include <memory>
#include <vector>

#include <Config.h>
#include <Core/ObjectPool.h>
#include <ECS/Entity.h>
#include <ECS/ComponentFactory.h>
#include <ECS/ComponentTupleContainer.h>

namespace zv { class System; }
namespace zv { struct ComponentArgs; }

namespace zv
{
  class EntityManager final
  {
  private:
    using entity_pool_type = ObjectPool<Entity, ZV_ENTITY_SIZE>;

  public:
    EntityManager();
    ~EntityManager() = default;

  public:
    auto create_entity(const std::string& name) -> Entity*;
    void destroy_entity(Entity* ptr_entity);

    template <typename T>
    T* get_singleton_component()
    {
      return m_ptr_component_factory->get_singleton_component<T>();
    }

    template <typename T>
    void register_system()
    {
      m_systems.emplace_back(std::make_unique<T>(this));
    }

    template<typename... Args>
    void update_component_tuple(ComponentTupleContainer<Args...>& container) {
      if (!any_component_outdated<Args...>())
      {
        return;
      }

      container.clear();

      for (const auto& ptr_entity : m_active_entities) {
        std::tuple<Args*...> components(ptr_entity->get_component<Args>()...);

        // Check if all components are valid
        if (all_components_valid(components)) {
          // If all components are valid, add them to the container
          container.add_component_tuple(std::get<Args*>(components)...);
        }
      }
    }

    void post_init();
    void fixed_update(f32 fixed_delta_time_s);
    void update(f32 delta_time_s);
    void late_update(f32 delta_time_s);

  private:
    // Helper function to check if all components in a tuple are valid
    template<typename... Args>
    bool all_components_valid(const std::tuple<Args*...>& components) {
        return ((std::get<Args*>(components) != nullptr) && ...);
    }

    // Helper function to check if all components in a tuple are valid
    template<typename... Args>
    bool any_component_outdated()
    {
      return (m_ptr_component_factory->is_component_type_updated<Args>() || ...);
    }

  private:
    std::unique_ptr<entity_pool_type> m_ptr_entity_pool{ nullptr };
    std::unique_ptr<ComponentFactory> m_ptr_component_factory{ nullptr };
    std::vector<std::unique_ptr<System>> m_systems{};

    std::vector<Entity*> m_active_entities;
  };
}
