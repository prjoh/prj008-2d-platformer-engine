#include <Core/Application.h>


#include <Util/PrimitiveTypes.h>
#include <Reflection/TypeInfoDatabase.h>
#include <Reflection/TypeInfo.h>
#include <Game/Reflection.h>
#include <Game/MyStruct.h>
#include <Serialize/Utils.h>

#include <Serialize/StreamBufferRead.h>
#include <Serialize/StreamBufferReadWrite.h>

#include <File/FileWriter.h>
#include <File/FileReader.h>

#include <Memory/Memory.h>


/*

ZV_DEFINE_TYPE_INFO(PositionComponentState)
{
  property<float, &PositionComponentState::x>("x");
  property<float, &PositionComponentState::y>("y");
  property<float, &PositionComponentState::z>("z");
}

ZV_DEFINE_TYPE_INFO(PositionComponent)
{
  property<PositionComponentState, &PositionComponent::m_state>("m_state");
}

struct PositionComponentState
{
  float x;
  float y;
  float z;
};

class PositionComponent
{
  bool has_position_changed;
  PositionComponentState m_state;
};


bool Game::load_scene(const SceneObject* ptr_scene);
bool Game::save_scene(SceneObject* out_ptr_scene);

class ZVObject
{
  TypeInfo* type_info;
}

class SceneObject : public ZVObject
{
  zv::Guid m_guid;
  std:string m_name;
  std::array<Entity*, ZV_MAX_SCENE_ENTITIES> m_entities;
  size_t m_entities_count;
};

class Entity : public ZVObject
{
  zv::Guid m_guid;
  std:string m_name;
  std::array<Component*, ZV_MAX_ENTITY_COMPONENTS> m_components;
  size_t m_components_count;
};

class Component : public ZVObject
{

};

class PositionComponent : public Component
{
  float x;
  float y;
  float z;
};

*/

void save_object_binary(zv::StreamBufferReadWrite& outbuf, s32 buffer_offset, const char* object, const zv::TypeInfo* ptr_type_info)
{
  for (const auto& property : ptr_type_info->get_properties())
  {
    if (zv::SerializeFunction save_func = property.m_ptr_type_info->func_serialize())
    {
      // This will either be one of the primitive type serializers or a user defined one
      save_func(outbuf, (const char*)object + property.m_offset, buffer_offset, 0);
      buffer_offset += property.m_ptr_type_info->size();
    }
    else
    {
      save_object_binary(outbuf, buffer_offset, (const char*)object + property.m_offset, property.m_ptr_type_info);
    }
  }
}

void load_object_binary(const zv::StreamBufferRead& inbuf, s32 buffer_offset, char* object, const zv::TypeInfo* ptr_type_info)
{
  for (const auto& property : ptr_type_info->get_properties())
  {
    if (zv::DeserializeFunction load_func = property.m_ptr_type_info->func_deserialize())
    {
      // This will either be one of the primitive type deserializers or a user defined one
      s32 out_size;  // TODO: This can be removed??
      load_func(inbuf, (char*)object + property.m_offset, &out_size, buffer_offset, 0);
      buffer_offset += property.m_ptr_type_info->size();
    }
    else
    {
      load_object_binary(inbuf, buffer_offset, (char*)object + property.m_offset, property.m_ptr_type_info);
    }
  }
}

int main(int argc, char* argv[])
{
  // MemAlloc(128);

  zv::internal::TypeInfoDatabase type_info_db{};
  // zv::internal::TypeInfoDatabase type_info_db2{};
  auto type_info_db3 = zv::internal::TypeInfoDatabase::get_ptr();

  ZV_ASSERT(&type_info_db == type_info_db3);

  zv::TypeInfo& type_info = type_info_db.get_type_info<zv::MyStruct>();

  auto file_path = std::string{ zv::FileUtils::get_application_directory() };
  file_path += "Game.data";

  zv::FileData file_data = zv::FileReader::read(file_path.c_str());

  ZV_ASSERT(file_data.m_size == 16);

  zv::StreamBufferRead r_buffer{file_data.m_ptr, file_data.m_size};

  zv::MyStruct my_struct_read{};

  load_object_binary(r_buffer, 0, (char*)&my_struct_read, &type_info);

  r_buffer.release();


  zv::MyStruct my_struct{};
  my_struct.x = 5.32f;
  my_struct.y = false;
  my_struct.z = 256;
  my_struct.data.p = true;
  my_struct.data.q = 512;

  ZV_ASSERT(my_struct.x == my_struct_read.x);
  ZV_ASSERT(my_struct.y == my_struct_read.y);
  ZV_ASSERT(my_struct.z == my_struct_read.z);
  ZV_ASSERT(my_struct.data.p == my_struct_read.data.p);
  ZV_ASSERT(my_struct.data.q == my_struct_read.data.q);

  size_t buffer_size = type_info.size();
  char* ptr_buffer = zv::mem_alloc(buffer_size);
  zv::StreamBufferReadWrite rw_buffer{ ptr_buffer, (s32)buffer_size };

  save_object_binary(rw_buffer, 0, (const char *)&my_struct, &type_info);

  zv::FileWriter::write(file_path.c_str(), ptr_buffer, buffer_size);

  rw_buffer.release();
  zv::mem_free(ptr_buffer);

  // zv::BufferReadWrite outbuf{};
  // save_object_binary(outbuf, (const char *)&my_struct, &type_info);
  
  // auto out_data_str = outbuf.data();
  
  // zv::FileWriter::write(file_path.c_str(), out_data_str.data(), out_data_str.size());

  return 0;

  zv::Application app;
  return app.run();
}
