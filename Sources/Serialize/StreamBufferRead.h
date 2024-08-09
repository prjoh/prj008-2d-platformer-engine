#pragma once

#include <Serialize/StreamBuffer.h>


namespace zv
{
	class StreamBufferRead : public StreamBuffer
  {
  private:
    using base_type = StreamBuffer;

	public:
    StreamBufferRead(char* ptr_buffer, int32_t buffer_size)
      : base_type(ptr_buffer, buffer_size)
    {}
		virtual ~StreamBufferRead () = default;	

  public:
		void read_bool (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const;
		void read_char (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const;
		void read_int8_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const;
		void read_uint8_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const;
		void read_int16_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const;
		void read_uint16_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const;
		void read_int32_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const;
		void read_uint32_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const;
		void read_int64_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const;
		void read_uint64_t (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const;
		void read_float (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const;
		void read_double (char* out_data, int32_t* out_size, int32_t offset, bool reverse) const;
	};
}
