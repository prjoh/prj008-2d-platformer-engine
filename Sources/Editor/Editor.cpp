#include <Core/RenderCore.h>
#include <Editor/Editor.h>
#include <Game/Game.h>

#include <imgui.h>
#include <rlImGui.h>


zv::Editor::Editor()
{
}

zv::Editor::~Editor()
{
}

void zv::Editor::create(IRenderSurface* ptr_render_surface)
{
  m_game_view_window.create("Game View");

  m_ptr_game = std::make_unique<Game>();
  IRenderSurface* game_view_render_surface = &m_game_view_window;
  m_ptr_game->create(game_view_render_surface);

  m_game_view_window.acquire_game_instance(m_ptr_game.get());
}

void zv::Editor::destroy()
{
  m_game_view_window.destroy();

  m_ptr_game->destroy();
}

void zv::Editor::run()
{
  m_game_view_window.update();
  // ImageViewer.Update();
  // SceneView.Update();

  BeginDrawing();
  ClearBackground(DARKGRAY);

  // Begin ImGui Content
  rlImGuiBegin();
  
  do_main_menu();

  if (m_game_view_window.Open)
  {
    m_game_view_window.show();
  }

  // if (ImGuiDemoOpen)
  // 	ImGui::ShowDemoWindow(&ImGuiDemoOpen);

  // if (ImageViewer.Open)
  // 	ImageViewer.Show();

  // if (SceneView.Open)
  // 	SceneView.Show();

  // end ImGui Content
  rlImGuiEnd();



  // // start ImGui Conent
  // rlImGuiBegin();

  // // create an ImGui window that covers the entire viewport, so that we can have a menu bar at the top of the applications
  // ImGui::SetNextWindowPos(ImVec2(0, 0));                                                  // always at the window origin
  // ImGui::SetNextWindowSize(ImVec2(float(GetScreenWidth()), float(GetScreenHeight())));    // always at the window size

  // ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoBringToFrontOnFocus |                 // we just want to use this window as a host for the menubar and docking
  //     ImGuiWindowFlags_NoNavFocus |                                                      // so turn off everything that would make it act like a window
  //     ImGuiWindowFlags_NoDocking |
  //     ImGuiWindowFlags_NoTitleBar |
  //     ImGuiWindowFlags_NoResize |
  //     ImGuiWindowFlags_NoMove |
  //     ImGuiWindowFlags_NoCollapse |
  //     ImGuiWindowFlags_MenuBar |
  //     ImGuiWindowFlags_NoBackground;                                                      // we want our game content to show through this window, so turn off the background.

  // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));                          // we don't want any padding for windows docked to this window frame

  // bool show = (ImGui::Begin("Main", NULL, windowFlags));                                   // show the "window"
  // ImGui::PopStyleVar();                                                                    // restore the style so inner windows have fames

  // // create a docking space inside our inner window that lets prevents anything from docking in the central node (so we can see our game content)
  // ImGui::DockSpace(ImGui::GetID("Dockspace"), ImVec2(0.0f, 0.0f),  ImGuiDockNodeFlags_PassthruCentralNode);
  // if (show)
  // {
  //     // Do a menu bar with an exit menu
  //     if (ImGui::BeginMenuBar())
  //     {
  //         if (ImGui::BeginMenu("File"))
  //         {
  //             if (ImGui::MenuItem("Exit"))
  //             {
  //               // TODO
  //             }

  //             ImGui::EndMenu();
  //         }
  //         ImGui::EndMenuBar();
  //     }
  // }
  // ImGui::End();

  // // show any other windows that we want to be dockable
  // ImGui::ShowDemoWindow(NULL);

  // // end ImGui Content
  // rlImGuiEnd();

  EndDrawing();
}

void zv::Editor::do_main_menu()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Exit"))
      {
        m_quit = true;
      }

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Window"))
    {
      ImGui::MenuItem("Game View", nullptr, &m_game_view_window.Open);
      // ImGui::MenuItem("ImGui Demo", nullptr, &ImGuiDemoOpen);
      // ImGui::MenuItem("Image Viewer", nullptr, &ImageViewer.Open);

      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}
