#include <Reflection/DefineTypeInfo.h>
#include <Reflection/PropertyInfo.h>
#include <Reflection/TypeInfo.h>


type_info_builder::PropertyBuilder::PropertyBuilder(zv::PropertyInfo* ptr_property) : m_ptr_property(ptr_property) {}

// type_info_builder::PropertyBuilder type_info_builder::PropertyBuilder::tag(std::string_view key, std::string_view value) 
// {
//   auto& tagMap = m_property->m_tagHolder.m_tagMap;
//   ZV_ASSERT_MSG(tagMap.find(key) == tagMap.end(), "Property Tag with the same name <{}> already registered!", key);
//   tagMap.emplace(key, value);
//   return *this;
// }

type_info_builder::PropertyBuilder type_info_builder::TypeBuilderBase::add_property_info(const zv::PropertyInfo& property)
{
  // const auto& properties = m_ptr_type_info->get_properties();
  // ZV_ASSERT_MSG(propertyMap.find(property_ptr->m_id.m_name) == propertyMap.end(), "Property <{}> is a duplicate!!", property_ptr->m_id.m_name);  // TODO: get name!
  
  // auto result = propertyMap.emplace (pProperty->getName(), pProperty);
  // m_classInfo.propertyList.emplace_back( result.first->second.get() );
  return {m_ptr_type_info->add_property_info(property)};
}

void type_info_builder::TypeBuilderBase::set_save_load_binary(zv::SerializeFunction save, zv::DeserializeFunction load)
{
  m_ptr_type_info->set_serialize_func(save);
  m_ptr_type_info->set_deserialize_func(load);
}
