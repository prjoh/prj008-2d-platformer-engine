#include <Core/IRenderSurface.h>
#include <Core/Time.h>
#include <ECS/Components/ColliderComponent.h>
#include <ECS/Entity.h>
#include <ECS/EntityManager.h>
#include <ECS/Systems/ActorControllerSystem.h>
#include <ECS/Systems/CommandSystem.h>
#include <ECS/Systems/PhysicsSystem.h>
#include <ECS/Systems/RenderingSystem.h>
#include <Game/Game.h>

#if (ZV_DEBUG_MODE_ENABLED)
#include <Core/DebugInfo.h>
#endif


zv::Game::Game()
{
  m_ptr_entity_manager = std::make_unique<EntityManager>();
}

zv::Game::~Game()
{
}

void zv::Game::create(IRenderSurface* ptr_render_surface)
{
  Time::get().init(ZV_FIXED_TIME_STEP);

  init(ptr_render_surface);
  post_init();
}

void zv::Game::destroy()
{
  cleanup();
}

void zv::Game::run()
{
  zv::Time::get().update();

  while (zv::Time::get().fixed_time_step_tick())
  {
    fixed_update(ZV_FIXED_TIME_STEP);
  }

  const auto& delta_time_s = zv::Time::get().delta_time_s();

#if (ZV_DEBUG_MODE_ENABLED)
  m_debug_info_update_time_s += delta_time_s;
  if (m_debug_info_update_time_s >= DebugInfo::k_update_interval_s)
  {
    m_debug_info_update_time_s -= DebugInfo::k_update_interval_s;
    DebugInfo::s_frames_per_second = zv::Time::get().get_frames_per_second();
  }
#endif

  update(delta_time_s);
  late_update(delta_time_s);
}

void zv::Game::init(IRenderSurface* ptr_render_surface)
{
  // CREATE SINGLETON ENTITIES

  // SingletonRenderContext::Args render_context_args{};
  // render_context_args.ptr_render_core = ptr_render_core;
  // auto* ptr_render_context = m_ptr_entity_manager->get_singleton_component<SingletonRenderContext>();
  // ptr_render_context->create(&render_context_args);

  constexpr f32 initial_world_height = 24.0f;

  SingletonCamera::Args camera_args{};
  camera_args.ptr_render_surface = ptr_render_surface;
  camera_args.initial_world_height = initial_world_height; // TODO
  // camera_args.render_size_x = ptr_render_core->render_size_x();
  // camera_args.render_size_y = ptr_render_core->render_size_y();
  // camera_args.pixel_per_unit = ptr_render_core->render_size_y() / initial_world_height;
  auto* ptr_camera = m_ptr_entity_manager->get_singleton_component<SingletonCamera>();
  ptr_camera->create(&camera_args);

  SingletonPhysicsWorld::Args physics_world_args{};
  physics_world_args.gravity = {0.0f, -9.81f};
  physics_world_args.timeStep = ZV_FIXED_TIME_STEP;
  physics_world_args.velocityIterations = ZV_VELOCITY_ITERATIONS;
  physics_world_args.positionIterations = ZV_POSITION_ITERATIONS;
  auto* ptr_physics_world = m_ptr_entity_manager->get_singleton_component<SingletonPhysicsWorld>();
  ptr_physics_world->create(&physics_world_args);

  // CREATE ENTITIES

  auto* pPlayerEntity = m_ptr_entity_manager->create_entity("Player");
  // const auto& guid = pPlayerEntity->object_id();
  // auto guid_str = guid.to_string();
  ColliderComponent::BoxTypeState collider_args{};
  collider_args.ptr_world = &ptr_physics_world->m_world;
  collider_args.body_type = ColliderComponent::eBodyType::b2_dynamicBody;
  collider_args.collider_type = ColliderComponent::eColliderType::Box;
  collider_args.density = 1.0f;
  collider_args.friction = 0.2f;
  collider_args.restitution = 0.0f;
  collider_args.linear_damping = 0.0f;
  collider_args.angular_damping = 0.01f;
  collider_args.width = 1.2f;
  collider_args.height = 2.0f;
  collider_args.category = (u16)eColliderCategory::Player;
  auto* pPlayerCollider = pPlayerEntity->add_component<ColliderComponent>(&collider_args);
  // pPlayerEntity->destroy_component(pCollider);
  // m_ptr_entity_manager->destroy_entity(pPlayerEntity);
  PlayerControllerComponent::Args player_controller_args{};
  player_controller_args.speed = 60.0f;
  player_controller_args.max_run_velocity = 7.0f;
  player_controller_args.distance_to_jump_peak = {3.5f, 4.5f};
  pPlayerEntity->add_component<PlayerControllerComponent>(&player_controller_args);

  auto* ptr_ground_entity = m_ptr_entity_manager->create_entity("Ground");
  ColliderComponent::BoxTypeState collider_args2{};
  collider_args2.ptr_world = &ptr_physics_world->m_world;
  collider_args2.body_type = ColliderComponent::eBodyType::b2_staticBody;
  collider_args2.collider_type = ColliderComponent::eColliderType::Box;
  collider_args2.density = 1.0f;
  collider_args2.friction = 0.2f;
  collider_args2.restitution = 0.0f;
  collider_args2.linear_damping = 0.0f;
  collider_args2.angular_damping = 0.01f;
  collider_args2.width = 64.0f;
  collider_args2.height = 0.25f;
  collider_args2.category = (u16)eColliderCategory::Ground;
  auto* ptr_ground_collider = ptr_ground_entity->add_component<ColliderComponent>(&collider_args2);

  ptr_ground_collider->m_ptr_body->SetTransform(
    {0.0f, -10.0f},
    0.0f
  );

  m_ptr_entity_manager->register_system<CommandSystem>();
  m_ptr_entity_manager->register_system<ActorControllerSystem>();
  m_ptr_entity_manager->register_system<PhysicsSystem>();
  m_ptr_entity_manager->register_system<RenderingSystem>();
}

void zv::Game::post_init()
{
  m_ptr_entity_manager->post_init();
}

void zv::Game::cleanup()
{
}

void zv::Game::fixed_update(f32 fixed_delta_time_s)
{
  m_ptr_entity_manager->fixed_update(fixed_delta_time_s);
}

void zv::Game::update(f32 delta_time_s)
{
  m_ptr_entity_manager->update(delta_time_s);
}

void zv::Game::late_update(f32 delta_time_s)
{
  m_ptr_entity_manager->late_update(delta_time_s);
}
