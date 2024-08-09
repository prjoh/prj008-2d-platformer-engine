#pragma once

#include <string>

#include <Core/Colors.h>
#include <ECS/ComponentTupleContainer.h>
#include <ECS/EntityManager.h>
#include <ECS/System.h>
#include <Math/Vector2.h>


namespace zv
{
  using raylib_color = Color;

  class RenderingSystem final : public System
  {
  private:
    using base_type = System;

  public:
    RenderingSystem(EntityManager* ptr_entity_manager) : base_type(ptr_entity_manager) {}
    ~RenderingSystem() = default;

  public:
    void post_init() override;
    void fixed_update(f32 fixed_delta_time_s) override {}
    void update(f32 delta_Time_s) override;
    void late_update(f32 delta_Time_s) override {}

  private:
    // void init_framebuffer() const { BeginDrawing(); }
    // void swap_buffers() const { EndDrawing(); }

    // void clear_buffers() const { ClearBackground(BLACK); }

#if (ZV_DEBUG_MODE_ENABLED)
    void draw_debug_primitives(const SingletonCamera& camera);
    void draw_debug_info(const SingletonCamera& camera) const;
#endif

    // Basic shapes drawing functions
    void draw_line(const Vector2& fromScreen, const Vector2& toScreen, f32 thickness, const Vector4& color) const;
    void draw_rectangle(const Vector2& position_screen, const Vector2& size, f32 rotation, const Vector4& color, const Vector2& pivot = { 0.5f, 0.5f }) const;
    void draw_rectangle_lines(const Vector2& position_screen, const Vector2& size, f32 thickness, const Vector4& color, const Vector2& pivot = { 0.5f, 0.5f }) const;
    void draw_circle(const Vector2& position_screen, f32 radius, const Vector4& color) const;
    void draw_line_strip(std::vector<raylib_vec2>& vertices, const Vector4& color);

/*
RLAPI void DrawPixel(int posX, int posY, Color color);                                                   // Draw a pixel
RLAPI void DrawLineStrip(Vector2 *points, int pointCount, Color color);                                  // Draw lines sequence (using gl lines)
RLAPI void DrawCircle(int centerX, int centerY, float radius, Color color);                              // Draw a color-filled circle
RLAPI void DrawCircleLines(int centerX, int centerY, float radius, Color color);                         // Draw circle outline
RLAPI void DrawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color);             // Draw ellipse
RLAPI void DrawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color);        // Draw ellipse outline
RLAPI void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color);              // Draw rectangle with rounded edges
RLAPI void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, float lineThick, Color color); // Draw rectangle with rounded edges outline
RLAPI void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                                // Draw a color-filled triangle (vertex in counter-clockwise order!)
RLAPI void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                           // Draw triangle outline (vertex in counter-clockwise order!)
RLAPI void DrawTriangleFan(Vector2 *points, int pointCount, Color color);                                // Draw a triangle fan defined by points (first vertex is the center)
RLAPI void DrawTriangleStrip(Vector2 *points, int pointCount, Color color);                              // Draw a triangle strip defined by points
RLAPI void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color);               // Draw a regular polygon (Vector version)
RLAPI void DrawPolyLinesEx(Vector2 center, int sides, float radius, float rotation, float lineThick, Color color); // Draw a polygon outline of n sides with extended parameters
*/

    // Text drawing functions
    void draw_text_centered(const std::string& text, s32 pos_x_screen, s32 pos_y_screen, s32 font_size, const Vector4& color) const;

/*
RLAPI void DrawText(const char *text, int posX, int posY, int fontSize, Color color);       // Draw text (using default font)
RLAPI void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text using font and additional parameters
RLAPI void DrawTextPro(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint); // Draw text using Font and pro parameters (rotation)
RLAPI void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint); // Draw one character (codepoint)
RLAPI void DrawTextCodepoints(Font font, const int *codepoints, int codepointCount, Vector2 position, float fontSize, float spacing, Color tint); // Draw multiple character (codepoint)
*/

  private:
#if (ZV_DEBUG_MODE_ENABLED)
    ComponentTupleContainer<ColliderComponent> m_collider_components;
#endif
  };
}
