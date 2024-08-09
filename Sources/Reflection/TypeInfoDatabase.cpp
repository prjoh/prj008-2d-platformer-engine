#include <Reflection/TypeInfoDatabase.h>
#include <Reflection/TypeInfo.h>
#include <Reflection/RegisterTypeInfo.h>
#include <Serialize/PrimitiveTypeSerializer.h>
#include <Util/PrimitiveTypes.h>



#define REGISTER_PRIMITIVE_TYPE(TYPE) \
{\
  auto& info = get_type_info<TYPE>(); \
  info.set_serialize_func(PrimitiveTypeSerializer<TYPE>::serialize);\
  info.set_deserialize_func(PrimitiveTypeSerializer<TYPE>::deserialize);\
}\


zv::internal::TypeInfoDatabase::TypeInfoDatabase()
 : base_type(this)
{
  // Register primitive types
  // REGISTER_PRIMITIVE_TYPE(void);
  REGISTER_PRIMITIVE_TYPE(bool);
  REGISTER_PRIMITIVE_TYPE(char);
  REGISTER_PRIMITIVE_TYPE(float);
  REGISTER_PRIMITIVE_TYPE(double);
  REGISTER_PRIMITIVE_TYPE(uint8_t);
  REGISTER_PRIMITIVE_TYPE(uint16_t);
  REGISTER_PRIMITIVE_TYPE(uint32_t);
  REGISTER_PRIMITIVE_TYPE(uint64_t);
  REGISTER_PRIMITIVE_TYPE(int8_t);
  REGISTER_PRIMITIVE_TYPE(int16_t);
  REGISTER_PRIMITIVE_TYPE(int32_t);
  REGISTER_PRIMITIVE_TYPE(int64_t);

  // Register user defined types
  auto* f = type_info_registration::get_reflection_functions();
  while (f != nullptr) {
    f->func();
    f = f->next;
  }
}

zv::TypeInfo& zv::internal::TypeInfoDatabase::get_type_info(const TypeInfoData& type_info_data)
{
  const auto& key = type_info_data.m_type_id;
  m_types.try_emplace(key, zv::TypeInfo{ type_info_data });
  return m_types.at(key);
}

const zv::TypeInfo& zv::internal::TypeInfoDatabase::get_type_info(const TypeInfoData& type_info_data) const
{
  const auto& key = type_info_data.m_type_id;

  auto it = m_types.find(key);
  ZV_ASSERT(it != m_types.end());

  return it->second;
}
