#pragma once

#include <map>

#include <Core/Error.h>
#include <Reflection/TypeInfoData.h>
#include <Util/Singleton.h>


namespace zv { class TypeId; }
namespace zv { class TypeInfo; }

namespace zv::internal
{
  class TypeInfoDatabase : public Singleton<TypeInfoDatabase>
  {
  public:
    TypeInfoDatabase();

  public:
    // TODO: How to make this private?
    template <typename TYPE> TypeInfo& get_type_info()
		{
			return get_type_info(TypeInfoData::create<TYPE>());
		}

    template <typename TYPE> const TypeInfo& get_type_info() const
		{
			return get_type_info(TypeInfoData::create<TYPE>());
		}

  private:
		TypeInfo& get_type_info(const TypeInfoData& type_info_data);
		const TypeInfo& get_type_info(const TypeInfoData& type_info_data) const;

  private:
  		std::map<zv::TypeId, zv::TypeInfo> m_types;
  };
}
