#pragma once

#include <Reflection/TypeId.h>
#include <Reflection/TypeOffset.h>
#include <Reflection/TypeInfoDatabase.h>
#include <Reflection/Utils.h>
#include <Util/PrimitiveTypes.h>


namespace zv { struct TypeInfo; }

namespace zv
{
	struct PropteryAttribute
	{
		enum
		{
			TRANSIENT = 1
		};

		PropteryAttribute() : m_value(0)
		{
		}

		PropteryAttribute(u32 value) : m_value(value)
		{
		}

		union
		{
			struct
			{
				u32 transient : 1;
			};
			u32 m_value;
		};
	};

  // // All data needed to construct PropertyInfo
	// struct PropertyInfoData
  // {
  //   NameArray m_name;
    
  // };

	struct PropertyInfo
	{
		// PropertyInfo();
		// PropertyInfo(const PropertyInfoInfo& field_info);

		// Parent-relative name
    internal::NameArray m_name;
    StringHash m_hash;
		// TypeId m_id;

		// Field type
		TypeInfo* m_ptr_type_info;
		bool m_is_pointer;

		// Byte offset within parent
		u32 m_offset;

		// IContainerFactory* m_ContainerFactory;

		PropteryAttribute m_attributes;  // TODO
		// Serialisers m_Serialisers;
		u32 m_version;

    template <typename CLASS, typename TYPE, TYPE CLASS::*field>
		static PropertyInfo create(const char* name, TypeInfo* ptr_type_info)
		{
			PropertyInfo property_info;
      property_info.m_name = internal::create_name_array(name);
      property_info.m_hash = zv::StringHash{property_info.m_name.data()};
			// property_info.m_id = TypeId::get<TYPE>();
      property_info.m_ptr_type_info = ptr_type_info;
      property_info.m_is_pointer = internal::is_pointer<TYPE>::val;
			property_info.m_offset = offset_of(field);
      // property_info.m_attributes = ???;
			property_info.m_version = 1;
			return property_info;
		}
	};
}
