#pragma once

#include <typeindex>

#include <Config.h>
#include <Core/ObjectPool.h>
#include <ECS/Component.h>
#include <ECS/ComponentTypes.h>
#include <ECS/Components/SingletonCamera.h>
#include <ECS/Components/SingletonInput.h>
#include <ECS/Components/SingletonPhysicsContactInfo.h>
#include <ECS/Components/SingletonPhysicsWorld.h>
#include <ECS/Components/SingletonPlayerCommand.h>
#include <ECS/Components/ColliderComponent.h>
#include <ECS/Components/PlayerControllerComponent.h>
#include <Util/TypeIndex.h>


namespace zv { struct ComponentArgs; }

namespace zv
{
  class ComponentFactoryImpl final
  {
  private:
    using collider_component_pool_type = ObjectPool<ColliderComponent, ZV_COLLIDER_COMPONENT_SIZE>;
    using player_controller_component_pool_type = ObjectPool<PlayerControllerComponent, ZV_PLAYER_CONTROLLER_COMPONENT_SIZE>;

  public:
    explicit ComponentFactoryImpl()
    {
      m_ptr_component_pools[eComponentType::Collider] = std::make_unique<collider_component_pool_type>();
      m_ptr_component_pool_dirty_flags[eComponentType::Collider] = true;

      m_ptr_component_pools[eComponentType::PlayerController] = std::make_unique<player_controller_component_pool_type>();
      m_ptr_component_pool_dirty_flags[eComponentType::PlayerController] = true;

      m_singleton_components[eSingletonComponentType::SingletonCamera] = std::make_unique<SingletonCamera>();
      m_singleton_components[eSingletonComponentType::SingletonInput] = std::make_unique<SingletonInput>();
      m_singleton_components[eSingletonComponentType::SingletonPlayerCommand] = std::make_unique<SingletonPlayerCommand>();
      m_singleton_components[eSingletonComponentType::SingletonPhysicsContactInfo] = std::make_unique<SingletonPhysicsContactInfo>();
      m_singleton_components[eSingletonComponentType::SingletonPhysicsWorld] = std::make_unique<SingletonPhysicsWorld>();
    }

  public:
    template <typename T>
    T* create_component(const ComponentArgs* ptr_args)
    {
      set_component_pool_flag<T>();

      auto component_type = get_pooled_component_type<T>();
      auto* ptr_component_pool = static_cast<IObjectPool<T>*>(get_component_pool(component_type));
      Component* ptr_component = ptr_component_pool->create();
      ptr_component->create(ptr_args);
      return static_cast<T*>(ptr_component);
    }

    template <typename T>
    void destroy_component(T* ptr_component)
    {
      set_component_pool_flag<T>();

      auto* ptr_pooled_component = static_cast<PooledComponent*>(ptr_component);
      auto component_type = ptr_pooled_component->get_type();
      auto* ptr_component_pool = static_cast<IObjectPool<T>*>(get_component_pool(component_type));
      ptr_component_pool->destroy(ptr_component);
    }

    template <typename T>
    T* get_singleton_component()
    {
      auto component_type = get_singleton_component_type<T>();
      auto it = m_singleton_components.find(component_type);
      ZV_ASSERT(it != m_singleton_components.end());
      auto* ptr_singleton_component = it->second.get();
      return static_cast<T*>(ptr_singleton_component);
    }

    void reset_component_pool_flags()
    {
      for (auto& [_, flag] : m_ptr_component_pool_dirty_flags) {
        flag = false;
      }
    }

    template <typename T>
    bool is_component_type_updated() const
    {
      auto component_type = get_pooled_component_type<T>();
      auto it = m_ptr_component_pool_dirty_flags.find(component_type);
      ZV_ASSERT(it != m_ptr_component_pool_dirty_flags.end());
      return it->second;
    }

    template <typename T>
    auto get_pooled_component_type() const -> eComponentType
    {
      const auto& type_index = get_type_index<T>();
      auto it = c_component_type_lut.find(type_index);
      ZV_ASSERT(it != c_component_type_lut.end());
      return it->second;
    }

    template <typename T>
    auto get_singleton_component_type() const -> eSingletonComponentType
    {
      const auto& type_index = get_type_index<T>();
      auto it = c_singleton_component_type_lut.find(type_index);
      ZV_ASSERT(it != c_singleton_component_type_lut.end());
      return it->second;
    }

  private:
    auto get_component_pool(eComponentType component_type) -> IObjectPoolBase*
    {
      auto it = m_ptr_component_pools.find(component_type);
      ZV_ASSERT(it != m_ptr_component_pools.end());
      return it->second.get();
    }

    template <typename T>
    void set_component_pool_flag()
    {
      auto component_type = get_pooled_component_type<T>();
      auto it = m_ptr_component_pool_dirty_flags.find(component_type);
      ZV_ASSERT(it != m_ptr_component_pool_dirty_flags.end());
      it->second = true;
    }

  private:
    static const std::unordered_map<std::type_index, eComponentType> c_component_type_lut;
    static const std::unordered_map<std::type_index, eSingletonComponentType> c_singleton_component_type_lut;

  private:
    std::unordered_map<eComponentType, std::unique_ptr<IObjectPoolBase>> m_ptr_component_pools;
    std::unordered_map<eComponentType, bool> m_ptr_component_pool_dirty_flags;
    std::unordered_map<eSingletonComponentType, std::unique_ptr<Component>> m_singleton_components;
  };
}
