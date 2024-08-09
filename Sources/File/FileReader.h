#pragma once

#include <string>

#include <raylib.h>

#include <Core/Error.h>
#include <File/Utils.h>
#include <Util/PrimitiveTypes.h>


namespace zv
{
  class FileReader;

  class FileData
  {
    friend class FileReader;

  private:
    FileData() = default;

  public:
    ~FileData()
    {
      UnloadFileData(reinterpret_cast<unsigned char*>(m_ptr));
    }

  public:
    char* m_ptr{ nullptr };
    s32 m_size{ 0 };
  };

  class FileReader
  {
  public:
    static FileData read(const char* file_path)
    { 
      ZV_ASSERT_MSG(FileUtils::file_exists(file_path), "[FileReader::read] No file found:\n{}", file_path);

      FileData data{};
      data.m_ptr = reinterpret_cast<char*>(LoadFileData(file_path, &data.m_size));
      return data;
    }
  };
}
