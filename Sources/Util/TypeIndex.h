#pragma once

#include <typeindex>

namespace zv
{
  template <typename T>
  std::type_index get_type_index()
  {
    return std::type_index(typeid(T));
  }
}
