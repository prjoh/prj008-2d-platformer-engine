#pragma once

#include <Core/Window.h>


namespace zv
{
  class GameMainWindow final : public MainWindow
  {
  private:
    using base_type = MainWindow;

  public:
    void create(const std::string& window_title) override;
  };
}
