#pragma once

#include <string>

#include <Math/Vector2.h>


namespace zv
{
  raylib_vec2 get_text_size(const std::string& text, s32 font_size)
  {
    // TODO
    if (GetFontDefault().texture.id == 0)
    {
      return { 0.0f, 0.0f };
    }

    int default_font_size = 10;   // Default Font chars height in pixel
    if (font_size < default_font_size) font_size = default_font_size;
    int spacing = font_size/default_font_size;

    return MeasureTextEx(GetFontDefault(), text.c_str(), font_size, spacing);
  }
}
