#pragma once

#include <Serialize/StreamBufferRead.h>


namespace zv
{
	class StreamBufferReadWrite : public StreamBufferRead
  {
  private:
    using base_type = StreamBufferRead;

	public:
    StreamBufferReadWrite(char* ptr_buffer, int32_t buffer_size)
      : base_type(ptr_buffer, buffer_size)
    {}
		virtual ~StreamBufferReadWrite () = default;	

  public:
		void write_bool (const char* in_data, int32_t offset, bool reverse);
		void write_char (const char* in_data, int32_t offset, bool reverse);
		void write_int8_t (const char* in_data, int32_t offset, bool reverse);
		void write_uint8_t (const char* in_data, int32_t offset, bool reverse);
		void write_int16_t (const char* in_data, int32_t offset, bool reverse);
		void write_uint16_t (const char* in_data, int32_t offset, bool reverse);
		void write_int32_t (const char* in_data, int32_t offset, bool reverse);
		void write_uint32_t (const char* in_data, int32_t offset, bool reverse);
		void write_int64_t (const char* in_data, int32_t offset, bool reverse);
		void write_uint64_t (const char* in_data, int32_t offset, bool reverse);
		void write_float (const char* in_data, int32_t offset, bool reverse);
		void write_double (const char* in_data, int32_t offset, bool reverse);
	};
}
