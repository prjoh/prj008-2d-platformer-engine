#pragma once

#include <memory>

#include <Util/PrimitiveTypes.h>

namespace zv { class MainWindow; }
namespace zv { class RenderCore; }
namespace zv { class ApplicationCore; }


namespace zv
{
  class Application final
  {
  public:
    Application();
    ~Application();
  
  public:
    s32 run();

  private:
    std::unique_ptr<MainWindow> m_ptr_window{ nullptr };
    // std::unique_ptr<RenderCore> m_ptr_render_core{ nullptr };
    std::unique_ptr<ApplicationCore> m_ptr_core{ nullptr };
  };
}
