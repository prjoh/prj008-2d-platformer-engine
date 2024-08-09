#include <rlImGui.h>
#include <imgui.h>

#include <Editor/EditorMainWindow.h>


void zv::EditorMainWindow::create(const std::string& window_title)
{
  MainWindow::ConfigFlags flags{};
  flags.set(MainWindow::eConfig::MSAA4XHint);
  flags.set(MainWindow::eConfig::WindowHighDPI);
  // flags.set(MainWindow::eConfig::VSyncHint);
  flags.set(MainWindow::eConfig::WindowResizable);

  SetConfigFlags(flags.get());
  InitWindow(0, 0, window_title.c_str());
  SetExitKey(0);

  auto current_monitor = GetCurrentMonitor();
  auto monitor_width = GetMonitorWidth(current_monitor);
  auto monitor_height = GetMonitorHeight(current_monitor);
  s32 window_width = monitor_width * 0.8f;
  s32 window_height = monitor_height * 0.8f;

  SetWindowSize(window_width, window_height);
  SetWindowPosition(monitor_width / 2 - window_width / 2, monitor_height / 2 - window_height / 2);
  MaximizeWindow();

  rlImGuiSetup(true);

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
}

void zv::EditorMainWindow::destroy()
{
  rlImGuiShutdown();

  base_type::destroy();
}
