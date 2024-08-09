#include <ECS/Entity.h>
#include <ECS/EntityManager.h>
#include <ECS/System.h>


zv::EntityManager::EntityManager()
{
  m_ptr_entity_pool = std::make_unique<entity_pool_type>();
  m_ptr_component_factory = std::make_unique<ComponentFactory>();
  m_systems.reserve(ZV_SYSTEM_SIZE);

  m_active_entities.reserve(ZV_ENTITY_SIZE);
}

auto zv::EntityManager::create_entity(const std::string& name) -> Entity*
{
  auto* ptr_entity = m_ptr_entity_pool->create();
  ptr_entity->m_ptr_component_factory = m_ptr_component_factory.get();
  ptr_entity->m_name = name; // TODO: Unique names???

  m_active_entities.emplace_back(ptr_entity);

  return ptr_entity;
}

void zv::EntityManager::destroy_entity(Entity* ptr_entity)
{
  const auto& object_id = ptr_entity->object_id();
  auto it = std::find_if(m_active_entities.begin(), m_active_entities.end(),[object_id](const auto* e) { return e->object_id() == object_id; });

  ZV_ASSERT(it != m_active_entities.end());

  m_active_entities.erase(it);

  ptr_entity->on_destroy();
  m_ptr_entity_pool->destroy(ptr_entity);
}

void zv::EntityManager::post_init()
{
  for (auto& ptr_system : m_systems)
  {
    ptr_system->post_init();
  }
}

void zv::EntityManager::fixed_update(f32 fixed_delta_time_s)
{
  for (auto& ptr_system : m_systems)
  {
    ptr_system->fixed_update(fixed_delta_time_s);
  }
}

void zv::EntityManager::update(f32 deltaTimeS)
{
  for (auto& ptr_system : m_systems)
  {
    ptr_system->update(deltaTimeS);
  }
}

void zv::EntityManager::late_update(f32 deltaTimeS)
{
  for (auto& ptr_system : m_systems)
  {
    ptr_system->late_update(deltaTimeS);
  }

  m_ptr_component_factory->reset_component_pool_flags();
}
