#include <ECS/EntityManager.h>
#include <ECS/Components/SingletonPlayerCommand.h>
#include <ECS/Components/SingletonPhysicsContactInfo.h>
#include <ECS/Systems/ActorControllerSystem.h>


void zv::ActorControllerSystem::post_init()
{
  m_ptr_entity_manager->update_component_tuple(m_components);
}

void zv::ActorControllerSystem::update(f32 deltaTimeS)
{
  m_ptr_entity_manager->update_component_tuple(m_components);
  
  auto* ptr_player_command = m_ptr_entity_manager->get_singleton_component<SingletonPlayerCommand>();

  for (auto& tuple : m_components)
  {
    auto* ptr_player_controller = tuple.get<PlayerControllerComponent>();

    if (ptr_player_controller->m_isGrounded && ptr_player_command->m_jump_pressed.get())
    {
      ptr_player_controller->m_cmdJumpPressed = true;
    }
  }
}

void zv::ActorControllerSystem::fixed_update(f32 fixedDeltaTimeS)
{
  auto* ptr_contact_info = m_ptr_entity_manager->get_singleton_component<SingletonPhysicsContactInfo>();
  auto* ptr_player_command = m_ptr_entity_manager->get_singleton_component<SingletonPlayerCommand>();

  auto* ptr_physics_world = m_ptr_entity_manager->get_singleton_component<SingletonPhysicsWorld>();

  for (auto& tuple : m_components)
  {
    auto* ptr_collider = tuple.get<ColliderComponent>();
    auto* ptr_player_controller = tuple.get<PlayerControllerComponent>();

    /////////////////////////////
    // Update grounded state
    ///////////////////////////// 

    const auto& contact_info = ptr_contact_info->m_contacts.get(ptr_collider->m_guid);
    if (contact_info.has_value())
    {
      ZV_ASSERT(ptr_collider->is_category(eColliderCategory::Player));

      const auto& type = contact_info.value()->type;
      const auto* ptr_other = contact_info.value()->ptr_collider;

      const auto& is_ground = ptr_other->is_category(eColliderCategory::Ground);

      if (is_ground)
      {
        ptr_player_controller->m_isGrounded = type == PhysicsContact::eType::Begin;
      }
    }

    /////////////////////////////
    // Update horizontal velocity
    /////////////////////////////

    const auto& horizontal_move = ptr_player_command->m_horizontal_move.get();
    const auto& horizontal_speed = ptr_player_controller->m_speed;
    const auto& maxHorizontal_velocity = ptr_player_controller->m_max_run_velocity;

    const auto& ground_fricition = 35.0f; // TODO: Parameterize

    box2d_vec2 linear_velocity = ptr_collider->m_ptr_body->GetLinearVelocity();

    if (zv::is_near_zero(horizontal_move))
    {
      const auto& dt_friction = fixedDeltaTimeS * ground_fricition;
      if (dt_friction < zv::abs(linear_velocity.x))
      {
        linear_velocity.x -= dt_friction * zv::sign(linear_velocity.x);
      }
      else
      {
        linear_velocity.x = 0.0f;
      }
    }
    else
    {
      linear_velocity.x += fixedDeltaTimeS * horizontal_move * horizontal_speed;
    }
    linear_velocity.x = zv::clamp(linear_velocity.x, -maxHorizontal_velocity, maxHorizontal_velocity);

    /////////////////////////////
    // Update vertical velocity
    /////////////////////////////

    // Grounded state
    if (ptr_player_controller->m_isGrounded)
    {
      // Check for jump
      if (ptr_player_controller->m_cmdJumpPressed)
      {
        // Consume jump pressed event
        ptr_player_controller->m_cmdJumpPressed = false;
        // m_inputJumpPressed = false;
        // m_isJumping = true;

        // m_isGrounded = false;
        ptr_player_controller->m_isGrounded = false;

        // m_horizontalJump = !MathExtension.Approximately(m_inputHorizontal, 0.0f, 0.01f);

        const auto& distance_to_jump_peak = ptr_player_controller->m_distance_to_jump_peak;

        // TODO: Calculate during Awake
        auto initial_jump_velocity = (2.0f * distance_to_jump_peak.y * maxHorizontal_velocity) / distance_to_jump_peak.x;
        ptr_physics_world->m_world.SetGravity({0.0f, (-2.0f * distance_to_jump_peak.y * (maxHorizontal_velocity * maxHorizontal_velocity)) / (distance_to_jump_peak.x * distance_to_jump_peak.x)});
        linear_velocity.y = initial_jump_velocity + ptr_physics_world->m_world.GetGravity().y * fixedDeltaTimeS;
      }
      else
      {
        linear_velocity.y = 0.0f;
      }
    }
    // Jumping state
    else
    {

    }

    ptr_collider->m_ptr_body->SetLinearVelocity(linear_velocity);
  }
}
