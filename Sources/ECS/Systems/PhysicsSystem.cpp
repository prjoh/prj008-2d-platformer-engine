#include <ECS/EntityManager.h>
#include <ECS/Components/SingletonPhysicsWorld.h>
#include <ECS/Systems/PhysicsSystem.h>


void zv::PhysicsSystem::post_init()
{
  auto* ptr_contact_info = m_ptr_entity_manager->get_singleton_component<SingletonPhysicsContactInfo>();
  m_contact_listener.acquire_contact_info(ptr_contact_info);

  auto* ptr_physics_world = m_ptr_entity_manager->get_singleton_component<SingletonPhysicsWorld>();
  ptr_physics_world->m_world.SetContactListener(&m_contact_listener);
}

void zv::PhysicsSystem::fixed_update(f32 fixedDeltaTimeS)
{
  auto* ptr_contact_info = m_ptr_entity_manager->get_singleton_component<SingletonPhysicsContactInfo>();
  ptr_contact_info->reset_contact_events();

  auto* ptr_physics_world = m_ptr_entity_manager->get_singleton_component<SingletonPhysicsWorld>();
  ptr_physics_world->m_world.Step(ptr_physics_world->m_time_step, ptr_physics_world->m_velocity_iterations, ptr_physics_world->m_position_iterations);
}
