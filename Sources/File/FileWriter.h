#pragma once

#include <raylib.h>

#include <Core/Log.h>
#include <Util/PrimitiveTypes.h>


namespace zv
{
  class FileWriter
  {
  public:
    static bool write(const char* file_path, char* data, s32 data_size)
    {
      if(!SaveFileData(file_path, data, data_size))
      {
        ZV_LOG_ERROR("[FileWriter::write] Unable to write file:\n{}", file_path);
        return false;
      }
      return false;
    }
  };
}
