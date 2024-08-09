#pragma once

#include <Reflection/Utils.h>
#include <Util/StringHash.h>


namespace zv::internal
{
  struct TypeIdData
  {
    zv::StringHash m_hash;
    NameArray m_name;
  };

	static constexpr TypeIdData s_null_data{{}, {}};

  template <typename TYPE>
  static constexpr TypeIdData create_data()
  {
    constexpr std::string_view signature = __PRETTY_FUNCTION__;
    constexpr size_t suffix_length = 1;
    constexpr size_t prefix_length = 47;

    const auto type_string = std::string_view{&signature[prefix_length], signature.size() - prefix_length - suffix_length};

    auto name_array = create_name_array(type_string);
    return { zv::StringHash{name_array.data()}, name_array };
  }

  template <class T>
  struct TypeIdHolder
  {
    static constexpr TypeIdData data{ create_data<T>() };
  };
}
