#include <Game/GameMainWindow.h>


void zv::GameMainWindow::create(const std::string& window_title)
{
  MainWindow::ConfigFlags flags{};
  flags.set(MainWindow::eConfig::MSAA4XHint);
  flags.set(MainWindow::eConfig::WindowHighDPI);
  // flags.set(MainWindow::eConfig::VSyncHint);
  // flags.set(MainWindow::eConfig::FullscreenMode);
  flags.set(MainWindow::eConfig::WindowResizable);

  SetConfigFlags(flags.get());
  InitWindow(0, 0, window_title.c_str());
  // SetExitKey(0);
  SetExitKey(KEY_ESCAPE);  // TODO

  auto current_monitor = GetCurrentMonitor();
  auto monitor_width = GetMonitorWidth(current_monitor);
  auto monitor_height = GetMonitorHeight(current_monitor);

  SetWindowSize(monitor_width / 1.5f, monitor_height / 1.5f);
  // ToggleFullscreen();
}
