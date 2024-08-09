#include <Config.h>
#include <Core/DebugInfo.h>
#include <ECS/Systems/RenderingSystem.h>
#include <Math/Vector4.h>
#include <Util/TextUtils.h>

#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

auto vector4_to_raylib_color(const zv::Vector4& color) -> zv::raylib_color
{
  auto ftou8 = [](f32 value) -> u8 {
    // Clamp the value to the range [0.0f, 1.0f]
    value = std::max(0.0f, std::min(1.0f, value));
    
    // Map the float value to the unsigned int range [0, 255]
    return static_cast<u8>(value * 255);
  };

  return zv::raylib_color
  {
    ftou8(color.x),
    ftou8(color.y),
    ftou8(color.z),
    ftou8(color.w),
  };
}

void zv::RenderingSystem::post_init()
{
#if (ZV_DEBUG_MODE_ENABLED)
  m_ptr_entity_manager->update_component_tuple(m_collider_components);
#endif
}

void zv::RenderingSystem::update(f32 delta_time_s)
{
#if (!ZV_DEV_TOOLS_ENABLED)
  BeginDrawing();
  // init_framebuffer();
#endif

  ClearBackground(BLACK);

  auto* ptr_camera = m_ptr_entity_manager->get_singleton_component<SingletonCamera>();

#if (ZV_DEBUG_MODE_ENABLED)
  draw_debug_primitives(*ptr_camera);
  draw_debug_info(*ptr_camera);
#endif

#if (!ZV_DEV_TOOLS_ENABLED)
  EndDrawing();
  // swap_buffers();
#endif
}

#if (ZV_DEBUG_MODE_ENABLED)
void zv::RenderingSystem::draw_debug_primitives(const SingletonCamera& camera)
{
  m_ptr_entity_manager->update_component_tuple(m_collider_components);

  for (const auto& tuple : m_collider_components)
  {
    const auto* ptr_collider = tuple.get<ColliderComponent>();

    const auto& pos_physics = ptr_collider->m_ptr_body->GetTransform().p;
    const auto& rot_physics = ptr_collider->m_ptr_body->GetTransform().q;

    if (ptr_collider->m_collider_type == ColliderComponent::eColliderType::Box)
    {
      auto* ptr_poly_shape = static_cast<b2PolygonShape*>(ptr_collider->m_ptr_shape.get());

      std::vector<raylib_vec2> verts;
      verts.reserve(ptr_poly_shape->m_count + 1);

      for (s32 i = 0; i < ptr_poly_shape->m_count; ++i)
      {
        Vector2 vert {
          ptr_poly_shape->m_vertices[i].x,
          ptr_poly_shape->m_vertices[i].y
        };
        vert += pos_physics;
        vert = camera.world_to_screen_point(vert);

        raylib_vec2 v{};
        v.x = vert.x;
        v.y = vert.y;
        verts.emplace_back(v);
      }
      verts.emplace_back(verts.front());

      draw_line_strip(verts, zv::Colors::Green);
    }
  }
}

void zv::RenderingSystem::draw_debug_info(const SingletonCamera& camera) const
{
  const auto& render_size_x = camera.render_size_x();
  const auto& render_size_y = camera.render_size_y();

  draw_line({0.0f, (f32)render_size_y * 0.5f}, {(f32)render_size_x, (f32)render_size_y * 0.5f}, 1.5f, zv::Colors::Red);
  draw_line({(f32)render_size_x * 0.5f, 0.0f}, {(f32)render_size_x * 0.5f, (f32)render_size_y}, 1.5f, zv::Colors::Red);

  s32 num_lines = 0;

  const auto& fps_string = std::to_string(DebugInfo::s_frames_per_second);
  const auto& frame_time_string = std::to_string(1.0f / DebugInfo::s_frames_per_second * 1000.0f);
  const auto& frame_rate_string = "FPS: "+fps_string+" / "+frame_time_string+" ms";
  raylib_vec2 text_size = get_text_size(frame_rate_string, DebugInfo::k_font_size);
  num_lines++;

  const f32 debug_info_box_width = render_size_x * 0.2f;
  const f32 debug_info_box_height = text_size.y * 1.25f * num_lines;
  const f32 debug_info_box_x = render_size_x - debug_info_box_width * 0.5f;
  const f32 debug_info_box_y = debug_info_box_height * 0.5f;

  draw_rectangle_lines({debug_info_box_x, debug_info_box_y}, {debug_info_box_width, debug_info_box_height}, 1.5f, Colors::Purple);
  draw_text_centered(frame_rate_string, debug_info_box_x, debug_info_box_y, DebugInfo::k_font_size, Colors::Purple);
}
#endif

///////////////////////////////////
// Basic shapes drawing functions
///////////////////////////////////
void zv::RenderingSystem::draw_line(const Vector2& from_screen, const Vector2& to_screen, f32 thickness, const Vector4& color) const
{
  DrawLineEx({from_screen.x, from_screen.y}, {to_screen.x, to_screen.y}, thickness, vector4_to_raylib_color(color));
}

void zv::RenderingSystem::draw_rectangle(const Vector2& position_screen, const Vector2& size, f32 rotation, const Vector4& color, const Vector2& pivot) const
{
  Rectangle rect
  {
    position_screen.x,
    position_screen.y,
    size.x,
    size.y,
  };

  raylib_vec2 origin
  {
    size.x * pivot.x,
    size.y * pivot.y,
  };

  // TODO: Coordinate system of rotation???
  DrawRectanglePro(rect, origin, rotation, vector4_to_raylib_color(color));
}

void zv::RenderingSystem::draw_rectangle_lines(const Vector2& position_screen, const Vector2& size, f32 thickness, const Vector4& color, const Vector2& pivot) const
{
  Rectangle rect
  {
    position_screen.x - size.x * pivot.x,
    position_screen.y - size.y * pivot.y,
    size.x,
    size.y,
  };

  DrawRectangleLinesEx(rect, thickness, vector4_to_raylib_color(color));
}

void zv::RenderingSystem::draw_text_centered(const std::string& text, s32 pos_x_screen, s32 pos_y_screen, s32 font_size, const Vector4& color) const
{
  raylib_vec2 text_size = get_text_size(text, font_size);

  DrawText(text.c_str(), pos_x_screen - text_size.x / 2, pos_y_screen - text_size.y / 2, font_size, vector4_to_raylib_color(color));
}

void zv::RenderingSystem::draw_circle(const Vector2& position_screen, f32 radius, const Vector4& color) const
{
  DrawCircle(position_screen.x, position_screen.y, radius, vector4_to_raylib_color(color));
}

void zv::RenderingSystem::draw_line_strip(std::vector<raylib_vec2>& vertices, const Vector4 &color)
{
  DrawLineStrip(vertices.data(), vertices.size(), vector4_to_raylib_color(color));
}
