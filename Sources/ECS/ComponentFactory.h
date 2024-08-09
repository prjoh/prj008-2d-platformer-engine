#pragma once

#include <memory>

#include <ECS/ComponentFactoryImpl.h>


namespace zv { struct ComponentArgs; }

namespace zv
{
  class ComponentFactory
  {
  public:
    explicit ComponentFactory()
    {
      m_ptr_impl = std::make_unique<ComponentFactoryImpl>();
    }

  public:
    template <typename T>
    T* create_component(const ComponentArgs* pArgs)
    {
      return m_ptr_impl->create_component<T>(pArgs);
    }

    template <typename T>
    void destroy_component(T* pComponent)
    {
      m_ptr_impl->destroy_component<T>(pComponent);
    }

    template <typename T>
    T* get_singleton_component()
    {
      return m_ptr_impl->get_singleton_component<T>();
    }

    void reset_component_pool_flags()
    {
      return m_ptr_impl->reset_component_pool_flags();
    }

    template <typename T>
    bool is_component_type_updated() const
    {
      return m_ptr_impl->is_component_type_updated<T>();
    }

    template <typename T>
    auto get_pooled_component_type() const -> eComponentType
    {
      return m_ptr_impl->get_pooled_component_type<T>();
    }

    template <typename T>
    auto get_singleton_component_type() const -> eSingletonComponentType
    {
      return m_ptr_impl->get_singleton_component_type<T>();
    }

  private:    
    std::unique_ptr<ComponentFactoryImpl> m_ptr_impl{ nullptr };
  };
}
