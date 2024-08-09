#include <Core/Error.h>
#include <Core/Guid.h>
#include <Util/Format.h>


zv::Guid zv::Guid::s_generate()
{
  Guid guid;

#if ZV_PLATFORM_IS_OSX
  auto new_id = CFUUIDCreate(NULL);
  auto bytes = CFUUIDGetUUIDBytes(new_id);
  CFRelease(new_id);

  const std::array<u8, 16> byte_array =
  {{
    bytes.byte0,
    bytes.byte1,
    bytes.byte2,
    bytes.byte3,
    bytes.byte4,
    bytes.byte5,
    bytes.byte6,
    bytes.byte7,
    bytes.byte8,
    bytes.byte9,
    bytes.byte10,
    bytes.byte11,
    bytes.byte12,
    bytes.byte13,
    bytes.byte14,
    bytes.byte15
  }};

  for (s32 i = 0; i < 4; ++i)
  {
    guid.m_v[i] = (static_cast<uint32_t>(byte_array[i * 4]) << 24) |
                  (static_cast<uint32_t>(byte_array[i * 4 + 1]) << 16) |
                  (static_cast<uint32_t>(byte_array[i * 4 + 2]) << 8) |
                  (static_cast<uint32_t>(byte_array[i * 4 + 3]));
  }
#elif ZV_PLATFORM_IS_WIN32 || ZV_PLATFORM_IS_WIN64
// TODO
#else
#   error "No GUID support found"
#endif

  return guid;
}

std::string zv::Guid::to_string() const
{
  return zv::format("{:08x}-{:08x}-{:08x}-{:08x}", m_v[0], m_v[1], m_v[2], m_v[3]);
}
