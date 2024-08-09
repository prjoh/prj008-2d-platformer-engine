#pragma once

#include <memory>

#include <Core/ApplicationCore.h>
#include <Util/PrimitiveTypes.h>

namespace zv { class EntityManager; }
namespace zv { class IRenderSurface; }

namespace zv
{
  class Game final : public ApplicationCore
  {
  public:
    Game();
    ~Game();

  public:
    void create(IRenderSurface* ptr_render_surface) override;
    void destroy() override;
    void run() override;

  public:
    void init(IRenderSurface* ptr_render_surface);
    void post_init();

    void cleanup();

    void fixed_update(f32 fixed_delta_time_s);
    void update(f32 delta_time_s);
    void late_update(f32 delta_time_s);

  private:
    std::unique_ptr<EntityManager> m_ptr_entity_manager{ nullptr };

#if (ZV_DEBUG_MODE_ENABLED)
    f32 m_debug_info_update_time_s{ 0.0f };
#endif
  };
}
