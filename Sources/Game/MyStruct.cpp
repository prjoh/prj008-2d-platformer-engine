#include <Game/MyStruct.h>
#include <Reflection/DefineTypeInfo.h>


ZV_DEFINE_TYPE_INFO(zv::MyStruct)
{
  property<float, &zv::MyStruct::x>("x");
  property<bool, &zv::MyStruct::y>("y");
  property<u16, &zv::MyStruct::z>("z");
  property<zv::MyData, &zv::MyStruct::data>("data");
}

ZV_DEFINE_TYPE_INFO(zv::MyData)
{
  property<bool, &zv::MyData::p>("p");
  property<u64, &zv::MyData::q>("q");
}
