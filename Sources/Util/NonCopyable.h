#pragma once


namespace zv
{
  class NonCopyable
  {
  protected:
	  NonCopyable() = default;
    
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
  };
}
