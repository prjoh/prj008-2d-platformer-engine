#pragma once

#include <string>

#include <Core/IRenderSurface.h>


namespace zv
{
  class EditorWindow : public IRenderSurface
  {
  public:
    EditorWindow() = default;
    virtual ~EditorWindow() = default;

  public:
    virtual void create(const std::string& window_title) = 0;
    virtual void destroy() = 0;
    virtual void update() = 0;
    virtual void show() = 0;

  public:
    bool Open{ false };

  protected:
    bool m_focused{ false };
    std::string m_title{};
  };
}
