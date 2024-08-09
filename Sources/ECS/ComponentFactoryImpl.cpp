#include <ECS/ComponentFactoryImpl.h>


const std::unordered_map<std::type_index, zv::eComponentType> zv::ComponentFactoryImpl::c_component_type_lut = 
{
  {get_type_index<ColliderComponent>(), zv::eComponentType::Collider},
  {get_type_index<PlayerControllerComponent>(), zv::eComponentType::PlayerController},
};

const std::unordered_map<std::type_index, zv::eSingletonComponentType> zv::ComponentFactoryImpl::c_singleton_component_type_lut = 
{
  {get_type_index<SingletonCamera>(),             eSingletonComponentType::SingletonCamera},
  {get_type_index<SingletonInput>(),              eSingletonComponentType::SingletonInput},
  {get_type_index<SingletonPlayerCommand>(),      eSingletonComponentType::SingletonPlayerCommand},
  {get_type_index<SingletonPhysicsContactInfo>(), eSingletonComponentType::SingletonPhysicsContactInfo},
  {get_type_index<SingletonPhysicsWorld>(),       eSingletonComponentType::SingletonPhysicsWorld},
};
