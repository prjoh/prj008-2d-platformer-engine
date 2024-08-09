#pragma once

#include <string>

#include <Util/Platform.h>

namespace zv
{
  class StringHash
  {
  private:
  #if defined(X86_64) || defined(AARCH64)
    static constexpr size_t k_val{ 0xcbf29ce484222325 };
    static constexpr size_t k_prime{ 0x100000001b3 };
  #else
    static constexpr size_t k_val{ 0x811c9dc5 };
    static constexpr size_t k_prime{ 0x1000193 };
  #endif

    static inline constexpr size_t hash_internal(const char* const str, const size_t value) noexcept
    {
      return (str[0] == '\0') ? value : hash_internal(&str[1], (value ^ size_t(str[0])) * k_prime);
    }

  public:
    static inline constexpr StringHash hash(const char* const str) noexcept
    {
      return StringHash(hash_internal(str, k_val));
    }

    constexpr StringHash() noexcept
      : m_hash(0)
    {
    }

    explicit constexpr StringHash(const size_t hash) noexcept
      : m_hash(hash)
    {
    }

    explicit constexpr StringHash(const char* const ptr_text) noexcept
      : m_hash(hash_internal(ptr_text, k_val))
    {
    }

    explicit StringHash(const std::string& text)
      : m_hash(hash_internal(text.c_str(), k_val))
    {
    }

    inline constexpr operator size_t() const { return m_hash; }

    inline bool operator==(const StringHash& rhs) const { return m_hash == rhs.m_hash; }
    inline bool operator!=(const StringHash& rhs) const { return m_hash != rhs.m_hash; }
    inline bool operator<(const StringHash& rhs) const { return m_hash < rhs.m_hash; }
    inline bool operator>(const StringHash& rhs) const { return m_hash > rhs.m_hash; }

    inline constexpr size_t value() const { return m_hash; }

  private:
    size_t m_hash;
  };
}

template<>
struct std::hash< zv::StringHash >
{
	[[nodiscard]] size_t operator()(const zv::StringHash& hash) const noexcept
	{
    return hash.value();
	}
};
