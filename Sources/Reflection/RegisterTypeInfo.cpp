#include <Reflection/RegisterTypeInfo.h>


type_info_registration::ReflectionFunctions* g_functions = nullptr;

type_info_registration::ReflectionFunctions* type_info_registration::get_reflection_functions()
{
	return g_functions;
}

void type_info_registration::push_reflection_functions(type_info_registration::ReflectionFunctions* f) {
  f->next = g_functions;
  g_functions = f;
}