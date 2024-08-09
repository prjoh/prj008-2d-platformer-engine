#pragma once


namespace type_info_registration
{
  using FuncPtr = void(*)();

  struct ReflectionFunctions {
      ReflectionFunctions(FuncPtr p) : func(p) {}
      FuncPtr func;
      ReflectionFunctions* next = nullptr;
  };

	ReflectionFunctions* get_reflection_functions();
  void push_reflection_functions(ReflectionFunctions* f);
}

#define ZV_REGISTER_TYPE_INFO(type_name) \
namespace type_info_registration::type_name\
{\
	void register_func();\
\
	struct Registrator : public ReflectionFunctions \
	{\
		Registrator() : ReflectionFunctions(register_func) { push_reflection_functions(this); }\
	} g_registrator;\
}
