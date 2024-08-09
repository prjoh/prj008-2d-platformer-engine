#pragma once

#include <Util/PrimitiveTypes.h>

namespace zv { class StreamBufferRead; }
namespace zv { class StreamBufferReadWrite; }

namespace zv
{
	typedef void ( *SerializeFunction )(StreamBufferReadWrite& out_buffer, const char* in_data, int32_t buffer_offset, u32 version);
	typedef void ( *DeserializeFunction )(const StreamBufferRead& in_buffer, char* out_data, int32_t* out_size, int32_t buffer_offset, u32 version);

  template<typename T>
  constexpr T* get_offset_ptr(const char* ptr_buffer, int32_t offset) noexcept
  {
    return reinterpret_cast<T*>( 
      reinterpret_cast<uintptr_t>( ptr_buffer ) + offset//gls::narrow<uintptr_t>(offset) 
    );
  }
}
