#pragma once

#include <cstdint>

#include <Core/Error.h>
#include <Reflection/TypeIdInternal.h>


namespace zv
{
  // // Each reflected type must specialise this
  // template <typename TYPE>
  // const char* get_type_name()
  // {
  //   ZV_ASSERT_MSG(false, "Type not implemented.");
  // }

  // Specialisation for primitive types
  // template <> inline const char* get_type_name<void>()     { return "void"; }  // TODO
  // template <> inline const char* get_type_name<bool>()     { return "bool"; }
  // template <> inline const char* get_type_name<char>()     { return "char"; }
  // template <> inline const char* get_type_name<float>()    { return "float"; }
  // template <> inline const char* get_type_name<double>()   { return "double"; }
  // template <> inline const char* get_type_name<uint8_t>()  { return "uint8_t"; }
  // template <> inline const char* get_type_name<uint16_t>() { return "uint16_t"; }
  // template <> inline const char* get_type_name<uint32_t>() { return "uint32_t"; }
  // template <> inline const char* get_type_name<uint64_t>() { return "uint64_t"; }
  // template <> inline const char* get_type_name<int8_t>()   { return "int8_t"; }
  // template <> inline const char* get_type_name<int16_t>()  { return "int16_t"; }
  // template <> inline const char* get_type_name<int32_t>()  { return "int32_t"; }
  // template <> inline const char* get_type_name<int64_t>()  { return "int64_t"; }

  // template <typename TYPE>
  // StringHash get_type_hash()
  // {
  //   // Calculates the string hash once and then caches it for further use
  //   static StringHash type_hash = StringHash::hash(get_type_name<TYPE>());
  //   return type_hash;
  // };

  // Used for both type names and object names
  class TypeId
  {
  public:
		constexpr TypeId() : TypeId(internal::s_null_data) {}

  private:
		constexpr TypeId(const internal::TypeIdData& data) : m_data(&data) {}

  public:
    template <typename TYPE>
    static constexpr TypeId get()
    {
      return {internal::TypeIdHolder<std::remove_const_t<TYPE>>::data};
    }

		constexpr std::string_view name() const { return m_data->m_name.data(); }
		constexpr size_t hash() const { return m_data->m_hash.value(); }

    explicit constexpr operator bool() const { return *this != TypeId{}; }
		constexpr bool operator==(const TypeId& rhs) const { return hash() == rhs.hash(); }
    constexpr bool operator!=(const TypeId& rhs) const { return hash() != rhs.hash(); }
		constexpr bool operator>(const TypeId& rhs) const { return hash() > rhs.hash(); }
    constexpr bool operator<(const TypeId& rhs) const { return hash() < rhs.hash(); }

  private:
		const internal::TypeIdData* m_data;
  };
}

namespace std {
	template <>
	struct hash <zv::TypeId>
	{
		size_t operator()(zv::TypeId type_id) const
		{
			return type_id.hash();
		}
	};
}
