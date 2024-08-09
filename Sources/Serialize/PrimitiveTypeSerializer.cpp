#include <Serialize/StreamBufferRead.h>
#include <Serialize/StreamBufferReadWrite.h>
#include <Serialize/PrimitiveTypeSerializer.h>


#define DEFINE_SERIALIZER(TYPE)\
	void PrimitiveTypeSerializer<TYPE>::serialize(zv::StreamBufferReadWrite& out_buffer, const char* in_data, int32_t buffer_offset, u32 /*version*/)\
	{\
		out_buffer.write_##TYPE(in_data, buffer_offset, false);\
	}\
	void PrimitiveTypeSerializer<TYPE>::deserialize(const zv::StreamBufferRead& in_buffer, char* out_data, int32_t* out_size, int32_t buffer_offset, u32 /*version*/)\
	{\
		in_buffer.read_##TYPE(out_data, out_size, buffer_offset, false);\
	}\

namespace zv::internal
{
	// void PrimitiveTypeSerializer<void>::serialize(zv::BufferReadWrite& outbuf, char* data, uint32_t version)
	// {
	// }
	// void PrimitiveTypeSerializer<void>::deserialize(const zv::BufferRead& inbuf, char* data, uint32_t version)
	// {
	// }

	DEFINE_SERIALIZER(bool)
	DEFINE_SERIALIZER(char)
	DEFINE_SERIALIZER(int8_t)
	DEFINE_SERIALIZER(uint8_t)
	DEFINE_SERIALIZER(int16_t)
	DEFINE_SERIALIZER(uint16_t)
	DEFINE_SERIALIZER(int32_t)
	DEFINE_SERIALIZER(uint32_t)
	DEFINE_SERIALIZER(int64_t)
	DEFINE_SERIALIZER(uint64_t)
	DEFINE_SERIALIZER(float)
	DEFINE_SERIALIZER(double)
	// DEFINE_SERIALIZER(le::String, String)
}
