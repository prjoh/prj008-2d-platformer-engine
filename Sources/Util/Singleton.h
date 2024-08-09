#pragma once

#include <Core/Error.h>
#include <Util/NonMovable.h>


namespace zv
{
  template<typename CLASS>
  class Singleton : private NonMovable {
  public:
    using base_type = Singleton<CLASS>;

  public:
		static CLASS& get (void) noexcept(true);
		static CLASS* get_ptr (void) noexcept(true);

  protected:
		explicit Singleton(CLASS* ptr_instance) noexcept(true);
		~Singleton() noexcept(true);

	protected:
		static CLASS* s_ptr_instance;
  };

  template <typename CLASS>
  CLASS* Singleton<CLASS>::s_ptr_instance = nullptr;

  template <typename CLASS>
  Singleton<CLASS>::Singleton(CLASS* ptr_instance) noexcept(true)
  {
    ZV_ASSERT_MSG(s_ptr_instance == nullptr, "Constructor on singleton type called more than once!");

    s_ptr_instance = ptr_instance;
  }

  template <typename CLASS>
  Singleton<CLASS>::~Singleton() noexcept(true)
  {
    ZV_ASSERT(s_ptr_instance != nullptr);
  }

  template <typename CLASS>
  CLASS& Singleton<CLASS>::get(void) noexcept(true)
  {
    ZV_ASSERT_MSG(s_ptr_instance != nullptr, "Constructor of singleton type hasn't been called!");

    return (*s_ptr_instance);
  }

  template <typename CLASS>
  CLASS* Singleton<CLASS>::get_ptr(void) noexcept(true)
  {
    ZV_ASSERT_MSG(s_ptr_instance != nullptr, "Constructor of singleton type hasn't been called!");

    return (s_ptr_instance);  
  }
}
