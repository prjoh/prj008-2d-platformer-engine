#include <ECS/EntityManager.h>
#include <ECS/Components/SingletonPlayerCommand.h>
#include <ECS/Systems/CommandSystem.h>


namespace zv
{
  void CommandSystem::update(f32 delta_time_s)
  {
    auto* ptr_input = m_ptr_entity_manager->get_singleton_component<SingletonInput>();
    auto* ptr_player_command = m_ptr_entity_manager->get_singleton_component<SingletonPlayerCommand>();

    // TODO: Choose the one that was last pressed down!!!
    f32 horizontal_move = ptr_input->down(eKeyboardKey::Left) ? -1.0f : ptr_input->down(eKeyboardKey::Right) ? 1.0f : 0.0f;
    ptr_player_command->m_horizontal_move.set(horizontal_move);

    bool jumpDown = ptr_input->down(eKeyboardKey::Space);
    ptr_player_command->m_jump_down.set(jumpDown);

    bool jumpPressed = ptr_input->pressed(eKeyboardKey::Space);
    ptr_player_command->m_jump_pressed.set(jumpPressed);
  }
}
