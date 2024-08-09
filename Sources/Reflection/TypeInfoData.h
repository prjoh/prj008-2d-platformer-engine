#pragma once

#include <type_traits>
#include <Reflection/TypeId.h>

namespace zv::internal { class TypeInfoDatabase; }


namespace zv::internal
{
  // All data needed to construct TypeInfo
  struct TypeInfoData
  {
    TypeId m_type_id;
    bool m_is_fundamental;
    size_t m_size;

  private:
    friend class TypeInfoDatabase;

    template <typename TYPE>
    static constexpr TypeInfoData create()
    {
      TypeInfoData data;
      data.m_type_id = TypeId::get<TYPE>();
      data.m_is_fundamental = std::is_fundamental<TYPE>();
      if (data.m_is_fundamental)
      {
        data.m_size = sizeof(TYPE);
      }
      else
      {
        data.m_size = 0;
      }
      return data;
    }
  };
}