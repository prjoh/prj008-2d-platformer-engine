#pragma once

#include <raylib.h>

#include <Util/PrimitiveTypes.h>

namespace zv
{
  char* mem_alloc(u32 size)
  {
    return (char*)MemAlloc(size);
  }

  void mem_free(char* ptr)
  {
    MemFree((void*)ptr);
  }
}