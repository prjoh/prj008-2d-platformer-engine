#pragma once

#include <array>
#include <string>

#include <Util/Platform.h>
#include <Util/PrimitiveTypes.h>

#if ZV_PLATFORM_IS_OSX
  #include <CoreFoundation/CFUUID.h>
#elif ZV_PLATFORM_IS_WIN32 || ZV_PLATFORM_IS_WIN64
  // TODO
#endif 

namespace zv
{
  class Guid
  {
		friend struct std::hash<Guid>;
	public:
		constexpr Guid() : Guid(0, 0, 0, 0) {};
		constexpr Guid(u32 v0, u32 v1, u32 v2, u32 v3) : m_v{ v0, v1, v2, v3 } {};

		static Guid s_generate();

		std::string to_string() const;

		constexpr bool is_empty() const { return *this == Guid{}; }

		constexpr u32 get0() const { return m_v[0]; }
		constexpr u32 get1() const { return m_v[1]; }
		constexpr u32 get2() const { return m_v[2]; }
		constexpr u32 get3() const { return m_v[3]; }

		constexpr bool operator<(Guid o) const { return guid_compare(m_v, o.m_v) < 0; }
		constexpr bool operator<=(Guid o) const { return guid_compare(m_v, o.m_v) <= 0; }
		constexpr bool operator>(Guid o) const { return guid_compare(m_v, o.m_v) > 0; }
		constexpr bool operator>=(Guid o) const { return guid_compare(m_v, o.m_v) >= 0; }
		constexpr bool operator==(Guid o) const { return guid_compare(m_v, o.m_v) == 0; }
		constexpr bool operator!=(Guid o) const { return guid_compare(m_v, o.m_v) != 0; }

	private:
		constexpr s32 guid_compare(const std::array<u32, 4>& a, const std::array<u32, 4>& b) const
		{
			for (s32 i = 0; i < 4; ++i)
			{
				if (a[i] == b[i]) continue;
				if (a[i] > b[i]) return 1;
				if (a[i] < b[i]) return -1;
			}
			return 0;
		}

		std::array<u32, 4> m_v;
  };
}

template<>
struct std::hash< zv::Guid >
{
	[[nodiscard]] size_t operator()(zv::Guid guid) const noexcept
	{
		size_t seed = 0;
		for (auto v : guid.m_v)
		{
			seed ^= std::hash<u32>{}(v)+0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};
