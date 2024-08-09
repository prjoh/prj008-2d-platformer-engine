#include <Serialize/StreamBufferRead.h>


void zv::StreamBufferRead::read_bool (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const
{
  auto* ptr_bytes = get_data<char>(offset);

  if (ptr_bytes[0]) out_data[0] = true;
  else out_data[0] = false;

  *out_size = 1;
}

void zv::StreamBufferRead::read_char (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const
{
  auto* ptr_bytes = get_data<char>(offset);

  out_data[0] = ptr_bytes[0];

  *out_size = 1;
}

void zv::StreamBufferRead::read_int8_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const
{
  auto* ptr_bytes = get_data<int8_t>(offset);

  out_data[0] = ptr_bytes[0];

  *out_size = 1;
}

void zv::StreamBufferRead::read_uint8_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const
{
  auto* ptr_bytes = get_data<uint8_t>(offset);

  out_data[0] = ptr_bytes[0];
  
  *out_size = 1;
}

void zv::StreamBufferRead::read_int16_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    out_data[0]	 = ptr_bytes[1];
    out_data[1]	 = ptr_bytes[0];
  } 
  else
  {
    out_data[0]	 = ptr_bytes[0];
    out_data[1]	 = ptr_bytes[1];
  }

  *out_size = 2;
}

void zv::StreamBufferRead::read_uint16_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    out_data[0]	 = ptr_bytes[1];
    out_data[1]	 = ptr_bytes[0];
  } 
  else
  {
    out_data[0]	 = ptr_bytes[0];
    out_data[1]	 = ptr_bytes[1];
  }

  *out_size = 2;
}

void zv::StreamBufferRead::read_int32_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    out_data[0]	 = ptr_bytes[3];
    out_data[1]	 = ptr_bytes[2];
    out_data[2]	 = ptr_bytes[1];
    out_data[3]	 = ptr_bytes[0];
  } 
  else
  {
    out_data[0]	 = ptr_bytes[0];
    out_data[1]	 = ptr_bytes[1];
    out_data[2]	 = ptr_bytes[2];
    out_data[3]	 = ptr_bytes[3];
  }

  *out_size = 4;
}

void zv::StreamBufferRead::read_uint32_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    out_data[0]	 = ptr_bytes[3];
    out_data[1]	 = ptr_bytes[2];
    out_data[2]	 = ptr_bytes[1];
    out_data[3]	 = ptr_bytes[0];
  } 
  else
  {
    out_data[0]	 = ptr_bytes[0];
    out_data[1]	 = ptr_bytes[1];
    out_data[2]	 = ptr_bytes[2];
    out_data[3]	 = ptr_bytes[3];
  }

  *out_size = 4;
}

void zv::StreamBufferRead::read_int64_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    for (int32_t i = 0; i < 7; ++i)
    {
      out_data[i] = ptr_bytes[7 - i];
    }
  }
  else
  {
    for (int32_t i = 0; i < 7; ++i)
    {
      out_data[i] = ptr_bytes[i];
    }
  }

  *out_size = 8;
}

void zv::StreamBufferRead::read_uint64_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    for (int32_t i = 0; i < 7; ++i)
    {
      out_data[i] = ptr_bytes[7 - i];
    }
  }
  else
  {
    for (int32_t i = 0; i < 7; ++i)
    {
      out_data[i] = ptr_bytes[i];
    }
  }

  *out_size = 8;
}

void zv::StreamBufferRead::read_float (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    out_data[0]	 = ptr_bytes[3];
    out_data[1]	 = ptr_bytes[2];
    out_data[2]	 = ptr_bytes[1];
    out_data[3]	 = ptr_bytes[0];
  } 
  else
  {
    out_data[0]	 = ptr_bytes[0];
    out_data[1]	 = ptr_bytes[1];
    out_data[2]	 = ptr_bytes[2];
    out_data[3]	 = ptr_bytes[3];
  }

  *out_size = 4;
}

void zv::StreamBufferRead::read_double (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const
{
  auto* ptr_bytes = get_data<char>(offset);

  if (reverse)
  {
    for (int32_t i = 0; i < 7; ++i)
    {
      out_data[i] = ptr_bytes[7 - i];
    }
  }
  else
  {
    for (int32_t i = 0; i < 7; ++i)
    {
      out_data[i] = ptr_bytes[i];
    }
  }

  *out_size = 8;
}
