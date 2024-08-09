#include <Serialize/StreamBufferReadWrite.h>


void zv::StreamBufferReadWrite::write_bool (const char* in_data, int32_t offset, bool reverse)
{
  auto* ptr_bytes = get_data<char>(offset);

  ptr_bytes[0] = in_data[0];
}

void zv::StreamBufferReadWrite::write_char (const char* in_data, int32_t offset, bool reverse)
{
  auto* ptr_bytes = get_data<char>(offset);

  ptr_bytes[0] = in_data[0];
}

void zv::StreamBufferReadWrite::write_int8_t (const char* in_data, int32_t offset, bool reverse)
{
  auto* ptr_bytes = get_data<char>(offset);

  ptr_bytes[0] = in_data[0];
}

void zv::StreamBufferReadWrite::write_uint8_t (const char* in_data, int32_t offset, bool reverse)
{
  auto* ptr_bytes = get_data<char>(offset);

  ptr_bytes[0] = in_data[0];
}

void zv::StreamBufferReadWrite::write_int16_t (const char* in_data, int32_t offset, bool reverse)
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    ptr_bytes[0] = in_data[1];
    ptr_bytes[1] = in_data[0];
  }
  else
  {
    ptr_bytes[0] = in_data[0];
    ptr_bytes[1] = in_data[1];
  }
}

void zv::StreamBufferReadWrite::write_uint16_t (const char* in_data, int32_t offset, bool reverse)
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    ptr_bytes[0] = in_data[1];
    ptr_bytes[1] = in_data[0];
  }
  else
  {
    ptr_bytes[0] = in_data[0];
    ptr_bytes[1] = in_data[1];
  }
}

void zv::StreamBufferReadWrite::write_int32_t (const char* in_data, int32_t offset, bool reverse)
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    ptr_bytes[0] = in_data[3];
    ptr_bytes[1] = in_data[2];
    ptr_bytes[2] = in_data[1];
    ptr_bytes[3] = in_data[0];
  }
  else
  {
    ptr_bytes[0] = in_data[0];
    ptr_bytes[1] = in_data[1];
    ptr_bytes[2] = in_data[2];
    ptr_bytes[3] = in_data[3];
  }
}

void zv::StreamBufferReadWrite::write_uint32_t (const char* in_data, int32_t offset, bool reverse)
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    ptr_bytes[0] = in_data[3];
    ptr_bytes[1] = in_data[2];
    ptr_bytes[2] = in_data[1];
    ptr_bytes[3] = in_data[0];
  }
  else
  {
    ptr_bytes[0] = in_data[0];
    ptr_bytes[1] = in_data[1];
    ptr_bytes[2] = in_data[2];
    ptr_bytes[3] = in_data[3];
  }
}

void zv::StreamBufferReadWrite::write_int64_t (const char* in_data, int32_t offset, bool reverse)
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    for (int32_t i = 0; i < 7; ++i)
    {
      ptr_bytes[i] = in_data[7 - i];
    }
  }
  else
  {
    for (int32_t i = 0; i < 7; ++i)
    {
      ptr_bytes[i] = in_data[i];
    }
  }
}

void zv::StreamBufferReadWrite::write_uint64_t (const char* in_data, int32_t offset, bool reverse)
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    for (int32_t i = 0; i < 7; ++i)
    {
      ptr_bytes[i] = in_data[7 - i];
    }
  }
  else
  {
    for (int32_t i = 0; i < 7; ++i)
    {
      ptr_bytes[i] = in_data[i];
    }
  }
}

void zv::StreamBufferReadWrite::write_float (const char* in_data, int32_t offset, bool reverse)
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    ptr_bytes[0] = in_data[3];
    ptr_bytes[1] = in_data[2];
    ptr_bytes[2] = in_data[1];
    ptr_bytes[3] = in_data[0];
  }
  else
  {
    ptr_bytes[0] = in_data[0];
    ptr_bytes[1] = in_data[1];
    ptr_bytes[2] = in_data[2];
    ptr_bytes[3] = in_data[3];
  }
}

void zv::StreamBufferReadWrite::write_double (const char* in_data, int32_t offset, bool reverse)
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    for (int32_t i = 0; i < 7; ++i)
    {
      ptr_bytes[i] = in_data[7 - i];
    }
  }
  else
  {
    for (int32_t i = 0; i < 7; ++i)
    {
      ptr_bytes[i] = in_data[i];
    }
  }
}
