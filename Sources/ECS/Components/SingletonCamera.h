#pragma once

#include <Core/IRenderSurface.h>
#include <ECS/Component.h>
#include <Math/Vector2.h>


namespace zv
{
  class SingletonCamera final : public SingletonComponent
  {
    friend class Game;
    friend class RenderingSystem;

  public:
    // TODO
    struct Args : public ComponentArgs
    {
      // s32 render_size_x;
      // s32 render_size_y;
      // f32 pixel_per_unit;
      IRenderSurface* ptr_render_surface;
      s32 initial_world_height; // TODO
    };

  public:
    SingletonCamera() { m_type = eSingletonComponentType::SingletonCamera; }
    ~SingletonCamera() = default;

  private:
    // TODO: Call location unclear!!!
    void create(const ComponentArgs* ptr_args) override;

  public:
    s32 render_size_x() const { return ptr_render_surface->get_render_width(); }
    s32 render_size_y() const { return ptr_render_surface->get_render_height(); }
    s32 pixel_per_unit() const { return render_size_y() / m_initial_world_height; }

    Vector2 screen_to_world_point(const Vector2& screen_pos) const;
    Vector2 world_to_screen_point(const Vector2& world_pos) const;

    f32 world_to_screen_scale(f32 val) const;
    Vector2 world_to_screen_scale(const Vector2& val) const;

  private:
    IRenderSurface* ptr_render_surface{ nullptr };
    s32 m_initial_world_height{};
    // s32 m_render_size_x{};
    // s32 m_render_size_y{};
    // f32 m_pixel_per_unit{};
  };
}

inline void zv::SingletonCamera::create(const ComponentArgs* ptr_args)
{
  // TODO: Add to base class???
  ZV_ASSERT_MSG(ptr_args != nullptr, "Expected SingletonCamera::Args was null.");

  const auto args = *reinterpret_cast<const Args*>(ptr_args);

  ptr_render_surface = args.ptr_render_surface;
  m_initial_world_height = args.initial_world_height;

  // m_render_size_x = args.render_size_x;
  // m_render_size_y = args.render_size_y;
  // m_pixel_per_unit = args.pixel_per_unit;
}

inline zv::Vector2 zv::SingletonCamera::screen_to_world_point(const Vector2& screen_pos) const
{
  // Assuming the world coordinate system is defined such that (0,0) is at the center of the world
  // Convert screen coordinate to world coordinate
  f32 world_x = screen_pos.x * (1.0f / pixel_per_unit()) - (f32)render_size_x() * 0.5f;
  f32 world_y = -screen_pos.y * (1.0f / pixel_per_unit()) + (f32)render_size_y() * 0.5f;
  return {world_x, world_y};
}

inline zv::Vector2 zv::SingletonCamera::world_to_screen_point(const Vector2& world_pos) const
{
  // Assuming the world coordinate system is defined such that (0,0) is at the center of the world
  // Convert world coordinate to screen coordinate
  f32 screen_x = (world_pos.x * pixel_per_unit() + (f32)render_size_x() * 0.5f);
  f32 screen_y = (-world_pos.y * pixel_per_unit() + (f32)render_size_y() * 0.5f);
  return {screen_x, screen_y};
}

inline f32 zv::SingletonCamera::world_to_screen_scale(f32 val) const
{
  return val * pixel_per_unit();
}

inline zv::Vector2 zv::SingletonCamera::world_to_screen_scale(const Vector2& val) const
{
  return val * pixel_per_unit();
}
