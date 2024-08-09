#pragma once

#include <Util/NonCopyable.h>


namespace zv
{
  class NonMovable : public NonCopyable 
  {
  protected:
    NonMovable() = default;
    
    NonMovable(NonMovable&&) = delete;
    NonMovable& operator=(NonMovable&&) = delete;
  };
}
