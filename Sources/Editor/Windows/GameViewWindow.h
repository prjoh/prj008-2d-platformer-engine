#pragma once

#include <Editor/Windows/EditorWindow.h>

#include <Math/Vector2.h>


namespace zv { class Game; }

namespace zv
{
  class GameViewWindow : public EditorWindow
  {
  public:
    s32 get_render_width() const override { return m_content_rect.width; }
    s32 get_render_height() const override { return m_content_rect.height; }

  public:
    void create(const std::string& window_title) override;
    void destroy() override;
    void update() override;
    void show() override;

  public:
    void acquire_game_instance(Game* ptr_game);

  private:
    void update_game_view();

  public:
  	// Texture ImageTexture;

    // raylib_vec2 LastMousePos = { 0 };
    // raylib_vec2 LastTarget = { 0 };
    // bool Dragging = false;

    // bool DirtyScene = false;

    // enum class ToolMode
    // {
    //   None,
    //   Move,
    // };

    // ToolMode CurrentToolMode = ToolMode::None;

  private:
    Game* m_ptr_game{ nullptr };

    // Camera2D m_camera = { 0 };
    RenderTexture m_view_texture{};
    Rectangle m_content_rect{ 0 };
  };
}
