#pragma once


namespace zv { class IRenderSurface; }

namespace zv
{
  class ApplicationCore
  {
  public:
    ApplicationCore() = default;
    virtual ~ApplicationCore() = default;

  public:
    virtual void create(IRenderSurface* ptr_render_surface) = 0;
    virtual void destroy() = 0;
    virtual void run() = 0;

    bool quit() const { return m_quit; }

  protected:
    bool m_quit{ false };
  };
}