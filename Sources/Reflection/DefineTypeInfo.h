#pragma once

#include <string_view>

#include <Reflection/TypeInfoDatabase.h>
#include <Reflection/PropertyInfo.h>
#include <Serialize/Utils.h>


#define ZV_DEFINE_TYPE_INFO(type_name)\
namespace type_info_registration::type_name\
{\
	void register_func()\
	{\
		type_info_builder::TypeBuilder<::type_name> builder{};\
	}\
}\
template<> void type_info_builder::TypeBuilder<::type_name>::register_type()\

// namespace zv { class FunctionInfo; }
namespace zv { struct PropertyInfo; }

namespace type_info_builder
{
	// class FunctionBuilder
	// {
	// public:
	// 	FunctionBuilder(zv::FunctionInfo* function);
	// 	FunctionBuilder tag(std::string_view key, std::string_view value);
	// private: 
	// 	zv::FunctionInfo* m_ptr_function;
	// };

	class PropertyBuilder
	{
	public:
		PropertyBuilder(zv::PropertyInfo* property);
		// PropertyBuilder tag(std::string_view key, std::string_view value);
	private: 
		zv::PropertyInfo* m_ptr_property;
	};

  class TypeBuilderBase
  {
  public:
    explicit TypeBuilderBase(zv::TypeInfo* ptr_type_info) : m_ptr_type_info(ptr_type_info) {}

  protected:
		// PropertyBuilder add_function_info(zv::FunctionInfo*);
		PropertyBuilder add_property_info(const zv::PropertyInfo&);
    void set_save_load_binary(zv::SerializeFunction save, zv::DeserializeFunction load);

  private:
    zv::TypeInfo* m_ptr_type_info;
  };

  template <typename TYPE>
  class TypeBuilder : public TypeBuilderBase
  {
  private:
    using base_type = TypeBuilderBase;
  public:
    TypeBuilder()
      : base_type(&zv::internal::TypeInfoDatabase::get().get_type_info<TYPE>())
    {
			register_type(); 
		}

    // void tag(std::string_view key, std::string_view value);

    // template <typename F>
    // FunctionBuilder function(std::string_view name, F f)
    // {
    //   return add_function_info(zv::FunctionInfo::create(name, f));
    // }

    void save_load_binary(zv::SerializeFunction save, zv::DeserializeFunction load)
    {
      set_save_load_binary(save, load);
    }

		template <typename PTYPE, PTYPE TYPE::*property> PropertyBuilder property(const char* name)
		{
      auto* ptr_property_type = &zv::internal::TypeInfoDatabase::get().get_type_info<PTYPE>();
			return add_property_info(zv::PropertyInfo::create<TYPE, PTYPE, property>(name, ptr_property_type));
		}

		void register_type();
  };
}
