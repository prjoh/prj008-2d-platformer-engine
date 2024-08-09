#include <Reflection/TypeInfo.h>
#include <Reflection/TypeInfoData.h>


zv::TypeInfo::TypeInfo(const internal::TypeInfoData& type_info_data)
  : m_type_id(type_info_data.m_type_id)
  , m_is_fundamental(type_info_data.m_is_fundamental)
  , m_size(type_info_data.m_size)
{}
