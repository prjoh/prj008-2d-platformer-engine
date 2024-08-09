#pragma once

#include <stdint.h>


namespace zv { class StreamBufferRead; }
namespace zv { class StreamBufferReadWrite; }

#define DECLARE_SERIALIZER(TYPE)\
	template<> class PrimitiveTypeSerializer<TYPE>\
	{\
	public:\
		static void serialize(zv::StreamBufferReadWrite& out_buffer, const char* in_data, int32_t buffer_offset, u32 /*version*/);\
		static void deserialize(const zv::StreamBufferRead& in_buffer, char* out_data, int32_t* out_size, int32_t buffer_offset, u32 /*version*/);\
	};\

namespace zv::internal
{
	template< typename T >
	class PrimitiveTypeSerializer {};

	// template<> class PrimitiveTypeSerializer<void>
	// {
	// 	public:
	// 	static void Serialize(zv::BufferReadWrite& outbuf, char* data, uint32_t version);
	// 	static void Deserialize(const zv::BufferRead& inbuf, char* data, uint32_t version);
	// };

	DECLARE_SERIALIZER(bool)
	DECLARE_SERIALIZER(char)
	DECLARE_SERIALIZER(int8_t)
	DECLARE_SERIALIZER(uint8_t)
	DECLARE_SERIALIZER(int16_t)
	DECLARE_SERIALIZER(uint16_t)
	DECLARE_SERIALIZER(int32_t)
	DECLARE_SERIALIZER(uint32_t)
	DECLARE_SERIALIZER(int64_t)
	DECLARE_SERIALIZER(uint64_t)
	DECLARE_SERIALIZER(float)
	DECLARE_SERIALIZER(double)
	// DECLARE_SERIALIZER(le::String);
}
