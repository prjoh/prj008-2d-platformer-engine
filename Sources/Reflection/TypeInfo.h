#pragma once

#include <Reflection/TypeId.h>
#include <Reflection/PropertyInfo.h>
#include <Serialize/Utils.h>


namespace zv::internal { struct TypeInfoData; }
namespace zv::internal { struct TypeInfoDatabase; }
namespace type_info_builder { struct TypeBuilderBase; }

namespace zv
{
  // The basic type representation
  class TypeInfo
  {
    friend class zv::internal::TypeInfoDatabase;
    friend class type_info_builder::TypeBuilderBase;

  private:
    explicit TypeInfo(const internal::TypeInfoData& type_info_data);

  private:
    PropertyInfo* add_property_info(const PropertyInfo& property_info)
    {
      // TODO: Check if property already exists in vector!!
      m_properties.emplace_back(property_info);

      m_size += property_info.m_ptr_type_info->size();

      return &m_properties.back();
    }

    void set_serialize_func(SerializeFunction serialize) { m_func_serialize = serialize; }
    void set_deserialize_func(DeserializeFunction deserialize) { m_func_deserialize = deserialize; }

  public:
    const std::vector<PropertyInfo>& get_properties() const { return m_properties; }
    SerializeFunction func_serialize() const { return m_func_serialize; }
    DeserializeFunction func_deserialize() const { return m_func_deserialize; }

    constexpr size_t size() const { return m_size; }

  private:
    // Scoped C++ name of the type
    TypeId m_type_id;

    // Result of std::is_fundamental
    bool m_is_fundamental;

    // If fundamental type: Result of sizeof(type) operation
    // Else: size of properties
    size_t m_size;

    // Easily searchable array of fields in the type
		// Order is not guaranteed to match registration order
		std::vector<PropertyInfo> m_properties;

    // Pointers to the constructor and destructor functions
    // ConstructObjectFunc constructor;
    // DestructObjectFunc destructor;

    // Pointers to the serializer functions
    SerializeFunction m_func_serialize = nullptr;
		DeserializeFunction m_func_deserialize = nullptr;
  };
}
