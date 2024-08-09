#pragma once

#include <array>
#include <string_view>


namespace zv::internal
{
  // Figure out if a type is a pointer
  template <typename TYPE> struct is_pointer
  {
    enum { val = 0 };
  };
  template <typename TYPE> struct is_pointer<TYPE*>
  {
    enum { val = 1 };
  };

  constexpr size_t k_name_array_size = 256;
  using NameArray = std::array<char, k_name_array_size>;

  constexpr NameArray create_name_array(std::string_view data)
  {
    auto next_char = [](std::string_view data, size_t& idx)
    {
      return data[idx++];
    };

    auto name_array = NameArray{};
    size_t array_ndx = 0, string_ndx = 0;
    while (string_ndx < data.size()) { name_array[array_ndx++] = next_char(data, string_ndx); }

    return name_array;
  }
}
