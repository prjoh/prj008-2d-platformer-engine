#pragma once


#include <Core/ApplicationCore.h>
#include <Editor/Windows/GameViewWindow.h>

namespace zv { class Game; }
namespace zv { class IRenderSurface; }

namespace zv
{
  class Editor final : public ApplicationCore
  {
  public:
    Editor();
    virtual ~Editor();

  public:
    void create(IRenderSurface* ptr_render_surface) override;
    void destroy() override;
    void run() override;

  private:
    void do_main_menu();

  private:
    std::unique_ptr<Game> m_ptr_game{ nullptr };

    GameViewWindow m_game_view_window{};
  };
}
