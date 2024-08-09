#include <imgui.h>
#include <rlImGui.h>
#include <raymath.h>

#include <Game/Game.h>

#include <Editor/Windows/GameViewWindow.h>


void zv::GameViewWindow::create(const std::string& window_title)
{
  m_title = window_title;

  // m_camera.zoom = 1;
  // m_camera.target.x = 0;
  // m_camera.target.y = 0;
  // m_camera.rotation = 0;
  // m_camera.offset.x = GetScreenWidth() / 2.0f;  // TODO
  // m_camera.offset.y = GetScreenHeight() / 2.0f;  // TODO

  m_view_texture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());  // TODO

  // update_render_texture();
}

void zv::GameViewWindow::destroy()
{
  UnloadRenderTexture(m_view_texture);
}

void zv::GameViewWindow::update()
{
  if (!Open)
    return;

  if (IsWindowResized())  // TODO
  {
    UnloadRenderTexture(m_view_texture);
    m_view_texture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());  // TODO

    // m_camera.offset.x = GetScreenWidth() / 2.0f;  // TODO
    // m_camera.offset.y = GetScreenHeight() / 2.0f;  // TODO
  }

  // raylib_vec2 mousePos = GetMousePosition();  // TODO

  if (m_focused)
  {
    // if (CurrentToolMode == ToolMode::Move)
    // {
    //   // only do this tool when the mouse is in the content area of the window
    //   if (IsMouseButtonDown(0) && CheckCollisionPointRec(mousePos, m_content_rect))  // TODO
    //   {
    //     // if (!Dragging)
    //     // {
    //     //   LastMousePos = mousePos;
    //     //   LastTarget = m_camera.target;
    //     // }
    //     // Dragging = true;
    //     // raylib_vec2 mouseDelta = Vector2Subtract(LastMousePos, mousePos);  // TODO

    //     // mouseDelta.x /= m_camera.zoom;
    //     // mouseDelta.y /= m_camera.zoom;
    //     // m_camera.target = Vector2Add(LastTarget, mouseDelta);  // TODO

    //     // DirtyScene = true;

    //   }
    //   else
    //   {
    //     Dragging = false;
    //   }
    // }
  }
  else
  {
    // Dragging = false;
  }

  // if (DirtyScene)
  // {
  //   DirtyScene = false;
    update_game_view();
  // }
}

void zv::GameViewWindow::show()
{
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::SetNextWindowSizeConstraints(ImVec2(640, 320), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));

  m_focused = false;

  if (ImGui::Begin(m_title.c_str(), &Open, ImGuiWindowFlags_NoScrollbar))
  {
    // save off the screen space content rectangle
    m_content_rect = { 
      ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMin().x, 
      ImGui::GetWindowPos().y + ImGui::GetWindowContentRegionMin().y, 
      ImGui::GetContentRegionAvail().x, 
      ImGui::GetContentRegionAvail().y };

    m_focused = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows);

    ImVec2 size = ImGui::GetContentRegionAvail();

    // center the scratch pad in the view
    Rectangle view_rect = { 0 };
    view_rect.x = m_view_texture.texture.width / 2 - size.x / 2;
    view_rect.y = m_view_texture.texture.height / 2 - size.y / 2;
    view_rect.width = size.x;
    view_rect.height = -size.y;

    // if (ImGui::BeginChild("Toolbar", ImVec2(ImGui::GetContentRegionAvail().x, 25)))
    // {
    //   ImGui::SetCursorPosX(2);
    //   ImGui::SetCursorPosY(3);

    //   if (ImGui::Button("None"))
    //   {
    //     CurrentToolMode = ToolMode::None;
    //   }
    //   ImGui::SameLine();

    //   if (ImGui::Button("Move"))
    //   {
    //     CurrentToolMode = ToolMode::Move;
    //   }

    //   ImGui::SameLine();
    //   switch (CurrentToolMode)
    //   {
    //     case ToolMode::None:
    //       ImGui::TextUnformatted("No Tool");
    //       break;
    //     case ToolMode::Move:
    //       ImGui::TextUnformatted("Move Tool");
    //       break;
    //     default:
    //       break;
    //   }

    //   ImGui::SameLine();
    //   ImGui::TextUnformatted(TextFormat("camera target X%f Y%f", m_camera.target.x, m_camera.target.y));
    //   ImGui::EndChild();
    // }

    rlImGuiImageRect(&m_view_texture.texture, (s32)size.x, (s32)size.y, view_rect);	
  }
  ImGui::End();
  ImGui::PopStyleVar();
}

void zv::GameViewWindow::acquire_game_instance(Game *ptr_game)
{
  m_ptr_game = ptr_game;
}

void zv::GameViewWindow::update_game_view()
{
  BeginTextureMode(m_view_texture);

  // camera with our view offset with a world origin of 0,0
  // BeginMode2D(m_camera);

  m_ptr_game->run();

  // EndMode2D();
  
  EndTextureMode();
}
